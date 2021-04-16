import storage
import requests
import json
from flask import request


def on_game_connect(req):
   print('On connect: Post')
   count = req['connection_count']
   print('On connect: Count =', count)
   storage.connetion_count = count
   storage.browser.use('updateConnectionCount', count)
   return '{"status": "OK"}'

storage.add_response_handler('connect', on_game_connect)


def on_select_figure(figure_name, callback):
   pass
   
def on_unselect_figure(figure_name, callback):
   pass

def on_change_figure(old_figure_name, new_figure_name, callback):
   pass
   
   
def get_game_sid(callback):
   callback.Call(storage.sid)
   
def get_connection_count(callback):
   callback.Call(storage.connection_count)
