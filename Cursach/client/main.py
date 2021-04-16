import sys

from singlifier import *
from browser import *

import storage

from logic.register import *
from logic.login import *
from logic.shop import *
from logic.create_game import *
from logic.connect_game import *
from logic.game import *


def main():
    global singlifier # Global because store HTML of pages, used by Browser to load_page
    singlifier = PageSinglifier() # Constructor do nothing
    singlifier.run() # Generating html files in cache folder

    # All logic is here
    browser = Browser('index', {
        'function': {
            'register': register,
            'login': login,
            'getShop': get_shop,
            'shopSelect': shop_select,
            'shopBuy': shop_buy,
            'createGame': create_game,
            'connectGame': connect_game,
            # game
            'onSelectFigure': on_select_figure,
            'onUnselectFigure': on_unselect_figure,
            'onChangeFigure': on_change_figure,
            'getGameSid': get_game_sid,
            'getConnectionCount': get_connection_count,
        }
    }) # Loading browser on 'index' page
    # [data] NO CODE SHOULD BE HERE, BROWSER BLOCK CODE EXECUTION


if __name__ == '__main__':
    main()