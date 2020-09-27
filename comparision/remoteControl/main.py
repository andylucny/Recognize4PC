import re
from tcpserver import TcpServer
from boebot import BoeBot
import time, os

boebot = BoeBot()
tcp = TcpServer()
while True:
    try:
        command = tcp.command()
        if len(command) > 0:
            print('command',command)
# ------- to be designed by students ---------
            if command == 'l': 
                boebot.rotateLeft() 
            elif command == 'r': 
                boebot.rotateRight() 
            elif command == 'f': 
                boebot.goForward() 
            elif command == 'b': 
                boebot.goBackward() 
            elif command == 's': 
                boebot.stop() 
# -------------------------------------------- 
        time.sleep(0.1)
    except Exception as e:
        print('main',e)
        os._exit(1)
