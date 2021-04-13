import os
import os.path as path
import re


class PageSinglifierLibs():
    def __init__(self, js_libs, css_libs, html_libs):
        self.js = js_libs
        self.css = css_libs
        self.html = html_libs
        
        self.js_str = ''
        for key, val in self.js.items():
            self.js_str += f'\n/* === Lib: {key} === */\n{val}'
        self.css_str = ''
        for key, val in self.css.items():
            self.css_str += f'\n/* === Lib: {key} === */\n{val}'
        self.html_str = ''
        for key, val in self.html.items():
            self.html_str += f'\n<!-- === Lib: {key} === -->\n{val}'
        

class PageSinglifier():
    
    def __init__(self):
        self.pages = dict()
        self.dirname = path.abspath(path.dirname(__file__))
        
    def _take_libs(self):
        dirname = self.dirname
        
        libs_folder = path.join(dirname, 'libs')
        
        js_libs_folder = path.join(libs_folder, 'js')
        css_libs_folder = path.join(libs_folder, 'css')
        html_libs_folder = path.join(libs_folder, 'html')
        
        js_libs = {}
        css_libs = {}
        html_libs = {}
        
        for filename in os.listdir(js_libs_folder):
            with open(path.join(js_libs_folder, filename), 'r+') as file:
                js_libs[filename[:-3]] = file.read()
        for filename in os.listdir(css_libs_folder):
            with open(path.join(css_libs_folder, filename), 'r+') as file:
                css_libs[filename[:-4]] = file.read()
        for filename in os.listdir(html_libs_folder):
            with open(path.join(html_libs_folder, filename), 'r+') as file:
                html_libs[filename[:-5]] = file.read()
                
        return PageSinglifierLibs(js_libs, css_libs, html_libs)


    def run(self):
        dirname = self.dirname
        
        cache_folder = path.join(dirname, 'cache')
        pages_folder = path.join(dirname, 'pages')
        
        images_folder = path.join(dirname, 'images')
        images_figure_folder = path.join(images_folder, 'figure')
        images_field_folder = path.join(images_folder, 'field')
        
        libs = self._take_libs()
        
        for page_folder_name in os.listdir(pages_folder):
            page_folder_file = path.join(pages_folder, page_folder_name, page_folder_name)
            
            html_file_path = page_folder_file + '.html'
            css_file_path = page_folder_file + '.css'
            js_file_path = page_folder_file + '.js'
            
            with open(html_file_path, 'r') as html_file:
                basis_html = html_file.read()
            with open(css_file_path, 'r') as css_file:
                css = css_file.read()
            with open(js_file_path, 'r') as js_file:
                js = js_file.read() 
                
            basis_html = basis_html.replace('/* [>css<] */', libs.css_str + css)
            basis_html = basis_html.replace('/* [>js<] */', libs.js_str + js)
            basis_html = basis_html.replace('<!-- [>html<] -->', libs.html_str)
            
            # images            
            for imagename in os.listdir(images_figure_folder):
                imagepath = path.join(images_figure_folder, imagename)
                with open(imagepath, 'r') as imagefile:
                    image = imagefile.read()
                    basis_html = basis_html.replace(f'<img src="[figure/{imagename}]"', f'<img src="{image}"')
            for imagename in os.listdir(images_field_folder):
                imagepath = path.join(images_field_folder, imagename)
                with open(imagepath, 'r') as imagefile:
                    image = imagefile.read().strip()
                    basis_html = basis_html.replace(f'<img src="[field/{imagename}]"', f'<img src="{image}"')
                
            # saving results
            result_html = basis_html
            
            cache_file = path.join(cache_folder, page_folder_name) + '.html'
            with open(cache_file, 'w+') as file:
                file.write(result_html)
                print(f'Cache file updated:', cache_file, f'({page_folder_name}.html)')
                
            self.pages[page_folder_name] = result_html
            