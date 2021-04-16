import storage
import json
import requests
import socket


def connect_game(sid, callback):
   storage.sid = sid
   print('Connect Game: SID =', storage.sid)
   
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

