import re
from Recognize4PC import Recognize4PC
from boebot import BoeBot
from speak import speak
import time, os

boebot = BoeBot()
tcp = Recognize4PC()
while True:
    try:
        command = tcp.command()
        if len(command) > 1:
            print(command)
# ------- to be designed by students ---------
            if tcp.match(r'left'):
                boebot.rotateLeft()
            elif tcp.match(r'right'):
                boebot.rotateRight()
            elif tcp.match(r'forward'):
                boebot.goForward()
            elif tcp.match(r'backward'):
                boebot.goBackward()
            elif tcp.match(r'stop'):
                boebot.stop()
            elif tcp.match(r'say (.*)',command):
                speak(tcp.matched[0])
# -------------------------------------------- 
        time.sleep(0.1)
    except Exception as e:
        print('main',e)
        os._exit(1)
