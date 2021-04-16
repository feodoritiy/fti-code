import storage
import requests
import json
from flask import request


def handle():
   storage.add_response_handler('connect', on_game_connect)
   storage.add_response_handler('figure-select', on_select_figure)


def on_game_connect(req):
   print('On connect: Post')
   count = req['connection_count']
   print('On connect: Count =', count)
   storage.connetion_count = count
   storage.browser.use('updateConnectionCount', count)
   return '{"status": "OK"}'



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


def send_figure_select(figure_type):
   storage.gameload('figure-select', {
      'figure': figure_type,
   })
   
def send_figure_change(old_figure_type, new_figure_type):
   pass
   
   
handle()