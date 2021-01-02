from modules.view import View
from modules.model import Model

view = View(10) # create view - 10 is field size
model = Model(view) # add logic

view.render()