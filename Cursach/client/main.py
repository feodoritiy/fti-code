from singlifier import *
from browser import *

import storage

from logic.register import *
from logic.login import *


def main():
    global singlifier # Global because store HTML of pages, used by Browser to load_page
    singlifier = PageSinglifier() # Constructor do nothing
    singlifier.run() # Generating html files in cache folder

    # All logic is here
    #browser = Browser('main-menu', {}) # Loading browser on 'index' page
    browser = Browser('index', {
        'function': {
            'register': register,
            'login': login,
        }
    }) # Loading browser on 'index' page

if __name__ == '__main__':
    main()
