from cefpython3 import cefpython as cef
import base64
import platform
import sys
import os.path as path
import threading

import storage
import builtins

class Browser():
    def __init__(self, start_page_name: str, js_bindings: dict):
        storage.browser = self # adding to global object
        builtins.browser = self
        
        self.thread_id = threading.get_ident()
        
        self._check_versions()
        sys.excepthook = cef.ExceptHook  # To shutdown all CEF processes on error
        
        settings = {
            # "product_version": "MyProduct/10.00",
            # "user_agent": "MyAgent/20.00 MyProduct/10.00",
            "debug": False,
            #"log_severity": cef.LOGSEVERITY_INFO,
        }
        cef.Initialize(settings=settings)

        start_page = self._html_to_data_uri(self.read(f'./cache/{start_page_name}.html'))
        self.browser = cef.CreateBrowserSync(window_title="Versus X", url=start_page)
        self.browser.SetClientHandler(LifespanHandler())
        
        self._bind_to_js(js_bindings)
        
        cef.MessageLoop()
        cef.Shutdown()
    

    def read(self, relpath):
        with open(path.join(path.dirname(__file__), relpath), 'r') as file:
           return file.read()
   
    def load_page(self, page_name):
        html = self.read(f'./cache/{page_name}.html')
        data_uri = self._html_to_data_uri(html)
        self.browser.LoadUrl(data_uri)
        
    def use(self, js_function_name, *args):
        print(f'Browser: .use(\'{js_function_name}\', {args}) from thread', threading.get_ident())
        self.browser.ExecuteFunction(js_function_name, *args)
    def exec(self, js_code):
        print(f'Browser: .exec(\'{js_code}\') from thread', threading.get_ident())
        self.browser.ExecuteJavascript(js_code)
        

    def _check_versions(self):
        ver = cef.GetVersion()
        print("[main.py] CEF Python {ver}".format(ver=ver["version"]))
        print("[main.py] Chromium {ver}".format(ver=ver["chrome_version"]))
        print("[main.py] CEF {ver}".format(ver=ver["cef_version"]))
        print("[main.py] Python {ver} {arch}".format(
            ver=platform.python_version(),
            arch=platform.architecture()[0]))
        assert cef.__version__ >= "57.0", "CEF Python v57.0+ required to run this"
        
    def _html_to_data_uri(self, html):
        html = html.encode("utf-8", "replace")
        b64 = base64.b64encode(html).decode("utf-8", "replace")
        ret = "data:text/html;base64,{data}".format(data=b64)
        return ret
    
    
    def _bind_to_js(self, data_to_bind):
        if not 'function' in data_to_bind:
            data_to_bind['function'] = {}
        data_to_bind['function']['loadPage'] = self.load_page
        
        bindings = cef.JavascriptBindings(bindToFrames=False, bindToPopups=False)
        
        if 'function' in data_to_bind:
            for [key, val] in data_to_bind['function'].items():
               bindings.SetFunction(key, val)
        if 'property' in data_to_bind:
            for [key, val] in data_to_bind['property'].items():
                bindings.SetProperty(key, val)
        if 'object' in data_to_bind:
            for [key, val] in data_to_bind['object'].items():
                bindings.SetObject(key, val)
                
        self.browser.SetJavascriptBindings(bindings)
        

class LifespanHandler(object):
    def OnBeforeClose(self, browser):
        print(f'Broswer ID: {browser.GetIdentifier()}')
        print('Browser will close and will exit')
        storage.connection_process.terminate()