import storage
import json
import requests

PROTOCOL = 'http'
HOST = '127.0.0.1'
PORT = '1234'
SERVER = f'{PROTOCOL}://{HOST}:{PORT}'

def login(login: str, password: str, callback):
   print('Login sending:', login, password)
   res = requests.post(f'{SERVER}/login', {
      'login': login,
      'password': password,
   })
   
   res = json.loads(res.text)
   print(res)
   
   if (res['status'] == 'OK'):
      storage.id = res['id']
   
   callback.Call(res['status'])
   