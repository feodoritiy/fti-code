from flask import Flask
from flask.globals import request
import openpyxl
import os.path
import datetime


app = Flask(__name__)

#BUFFER_SIZE = 1000
BUFFER_SIZE = 0
buffer = []


@app.route('/', methods=['POST', 'GET'])
def index():
   global buffer
   
   if request.method == 'POST':
      
      buffer += [request.json]
      print('req.body:', buffer[-1])
      if (len(buffer) > BUFFER_SIZE):
         saveExcel()
         buffer = []
         
      return 'OK'
      
   elif request.method == 'GET':
      return 'Это GET запрос'


def saveExcel():
   global buffer
   
   STORAGE_FILE = './Python/data.xlsx'
   
   book = None
   # create or open book
   if not os.path.exists(STORAGE_FILE):
      book = openpyxl.Workbook()
      # headers
      book.active['A1'] = 'N'
      book.active['B1'] = 'User ID'
      book.active['C1'] = 'Datetime'
      book.active['D1'] = 'Item'
      book.active['E1'] = 'Prise'
      book.save(STORAGE_FILE)
   else:
      book = openpyxl.open(STORAGE_FILE)   
   sheet = book.active
   
   max_row = len(sheet['A'])
   nowtime = datetime.datetime.utcnow()
   
   row = max_row + 1
   for dataset in buffer:
      id = dataset['user_id']
      check = dataset['check']
      
      for item in check:
         sheet[row][0].value = row - 1
         sheet[row][1].value = id
         sheet[row][2].value = nowtime
         sheet[row][3].value = item['name']
         sheet[row][4].value = item['price']
         row += 1
   
   book.save(STORAGE_FILE)
   book.close()

saveExcel()   

if __name__ == '__main__':
   app.run()