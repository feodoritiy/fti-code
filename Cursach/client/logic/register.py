import storage 
import json
import requests

PROTOCOL = 'http'
HOST = '127.0.0.1'
PORT = '1234'
SERVER = f'{PROTOCOL}://{HOST}:{PORT}'

def register(login: str, password: str, callback):
   print('Register sending:', login, password)
   res = requests.post(f'{SERVER}/register', {
      'login': login,
      'password': password,
   })
   
   res = json.loads(res.text)
   
   if (res['status'] == 'OK'):
      storage.id = res['id']
   
   callback.Call(res['status'])
   