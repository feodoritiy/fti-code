import storage 
import json
import requests

def get_shop(callback):
   if hasattr(storage, 'id'):
      # If logged in

      print(f'Shop ok: id = {storage.id}')
      print('Shop sending:', storage.id)
      
      res = storage.load('/shop', {
         'action': 'get-state',
         'id': storage.id,
      })
      
      print(res)
      
      if (res['status'] == 'OK'):
         callback.Call({
            'id': storage.id,
            'shop': res['shop'],
            'amount': res['amount'],
         })
      else:
         print('Shop: Error "Bad shop requests"')

   else:
      # Any case when user not logged in
      print('Shop Error: storage has no \'id\' property.')