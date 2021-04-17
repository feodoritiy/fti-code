import sys
import threading

from singlifier import *
from browser import *

import storage
import builtins

from logic.register import *
from logic.login import *
from logic.shop import *
from logic.create_game import *
from logic.connect_game import *
from logic.game import *


def main():
    print('Main: main thread is', threading.get_ident())
    
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
            
            'getGameSid': get_game_sid,
            'getUserId': get_user_id,
            'getConnectionCount': get_connection_count,
            'getConnectionsState': get_connections_state,
            'getTasks': get_tasks,
            'getSkin': get_skin,
            'getField': get_field_skin,
            
            'sendFigureSelect': send_figure_select,
            'sendFigureUnselect': send_figure_unselect,
            'sendFigureChange': send_figure_change,
            'sendReady': send_ready,
            'sendUnready': send_unready,
            'sendDisconnect': send_disconnect,
            'sendStep': send_step,
        }
    }) # Loading browser on 'index' page
    # [data] NO CODE SHOULD BE HERE, BROWSER BLOCK CODE EXECUTION


if __name__ == '__main__':
    main()