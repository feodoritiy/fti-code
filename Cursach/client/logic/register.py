import storage 
import json
import requests

def register(login: str, password: str, callback):
   print('Register sending:', login, password)
   
   res = storage.load(f'/register', {
      'login': login,
      'password': password,
   })
   
   if (res['status'] == 'OK'):
      storage.id = res['id']
   
   callback.Call(res['status'])
   