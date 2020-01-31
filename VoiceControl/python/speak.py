import os
import sys
from agentspace import Agent,Space

def speak(text):
    os.environ["ESPEAK_DATA_PATH"] = "." 
    Space.write('speaking',True)
    os.system('espeak "'+text+'"')
    Space.write('speaking',False)

if __name__ == "__main__":  
    text = sys.argv[1] if len(sys.argv) > 1 else "eee"
    speak(text)
    