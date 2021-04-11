from json.decoder import JSONDecodeError
import sys
import requests
import json

# this is pointer to the module object itself
this = sys.modules[__name__]

# setting props
this.id = None


PROTOCOL = 'http'
HOST = '127.0.0.1'
PORT = '1234'
SERVER = f'{PROTOCOL}://{HOST}:{PORT}'

def load(path, data):
   res = requests.post(f'{SERVER}{path}', data)
   try:
      res = json.loads(res.text)
   except JSONDecodeError:
      print(f'''Error: parsing JSON on storage.load('{path}', '{json.dumps(data, indent=3)}').\nIncoming JSON:\n{res.text}''')
   return res
