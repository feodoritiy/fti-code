import storage
import json
import requests

def login(login: str, password: str, callback):
   print('Login sending:', login, password)
   
   res = storage.load('/login', {
      'login': login,
      'password': password,
   })
   
   print(res)
   
   if (res['status'] == 'OK'):
      storage.id = res['id']
   
   callback.Call(res['status'])
   