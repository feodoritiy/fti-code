import storage
import requests
import json
from flask import request
import threading


def handle():
   storage.add_response_handler('connect', on_game_connect)
   storage.add_response_handler('figure-select', on_select_figure)


def on_game_connect(req):
   print('On connect: thread is', threading.get_ident())
   
   print('On connect: Post')
   count = req['connection_count']
   print('On connect: Count =', count)
   storage.connetion_count = count
   
   storage.tasks.put(['updateConnectionCount', [count]])
   print('on_game_connect: storage.tasks renew', storage.tasks)

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
   
get_task_counter = 0
def get_tasks(callback):
   global get_task_counter
   get_task_counter += 1
   if not storage.tasks.empty():
      #print('getTasks: storage.tasks is', storage.tasks)
      tasks = []
      while not storage.tasks.empty():
         tasks.append(storage.tasks.get())
      print('getTasks: some tasks', tasks)
      callback.Call(tasks)
   else:
      pass
      #print('getTasks: queue is empty ', get_task_counter)
   

handle()