import re
from Recognize4PC import Recognize4PC
import time, os

tcp = Recognize4PC()
while True:
    try:
        command = tcp.command()
        if len(command) > 0:
            if tcp.match(r'type (.*)',command):
                print(tcp.matched[0])
        time.sleep(0.1)
    except:
        os._exit(1)
   
    
