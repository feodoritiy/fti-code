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
      
      
def shop_select(slider_name, product_name, callback):
   res = storage.load('/shop', {
      'action': 'select',
      'id': storage.id,
      'slider': slider_name,
      'product': product_name,
   })
   
   if res['status'] == 'OK':
      callback.Call(res)
   else:
      print(f'Shop: Error "Bad product select request ({slider_name}, {product_name})"')
      

def shop_buy(slider_name, product_name, callback):
   res = storage.load('/shop', {
      'action': 'buy',
      'id': storage.id,
      'slider': slider_name,
      'product': product_name,
   })
   
   if res['status'] == 'OK':
      callback.Call(res)
   elif res['status'] == 'Deprecated':
      callback.Call(res)
      print(f'Shop: Deal deprecated because of small amount')
   else:
      print(f'Shop: Error "Bad product select request ({slider_name}, {product_name})"')
   