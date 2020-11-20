from base64 import encode
from tkinter import *
import requests
from requests.exceptions import InvalidSchema

root = Tk()

try:
   weather = requests.get('http://localhost:3000/raw', headers={'Content-type': 'text/json; charset=UTF-8'}).json()
except InvalidSchema:
   print('Can\'t connect to server. Exit')
   exit()

temp = str(weather['temp']).split('.')[0]

top = Frame(root, background="#ffbd37").pack(side=TOP, fill=X)
middle = Frame(root, background="white").pack(side=TOP, fill=BOTH)
bottom = Frame(root, background="#ffbd37").pack(side=BOTTOM, fill=X)

Label(top, 
   text="Симферополь", 
   bg="#ffbd37", 
   fg="#333333",
   font=('sans-serif', 10, 'bold')).pack(fill=X)
Label(top, 
   text=weather['descr'], 
   bg="#ffbd37", 
   fg="#333333",
   font=('sans-serif', 8)).pack(fill=X)
Label(middle, 
   text=(temp + '°C'), 
   padx=50, 
   pady=50,
   fg="#333333",
   font=('sans-serif', 50, 'bold')).pack(fill=X)
Label(bottom, bg="#ffbd37").pack(fill=X)

root.mainloop()