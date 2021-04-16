import storage
import json
import requests
import socket


def create_game(callback):
   res = storage.load('/create-game', {
      'id': storage.id,
   })
   
   if res['status'] == 'OK':
      print('Create Game: respond OK')
      print('Create Game: SID =', res['sid'])
      storage.sid = res['sid']
      storage.run_server()
      res = storage.load('/game', {
         'action': 'connect',
         'id': storage.id,
         'sid': storage.sid,
         'host': f'{storage.host}:{storage.port}',
      })
      
      if res['status'] == 'OK':
         storage.connection_count = res['connection_count']
   
   callback.Call(res)
