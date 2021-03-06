from agentspace import Agent,Space
import socket
import sys
import re
import time

class ReceiverServiceAgent(Agent):

    def __init__(self,socket,name):
        self.socket = socket
        self.name = name
        self.buffer = ''
        super().__init__()
        
    def getline(self):
        while self.buffer.find('\n')==-1:
            self.buffer += self.socket.recv(1024).decode()
        result = re.sub('[\r\n].*','',self.buffer)
        self.buffer = self.buffer[self.buffer.find('\n')+1:]
        return result
     
    def putline(self,line):
        self.socket.send((line+'\r\n').encode())
        
    def init(self):
        try:
            print('starting reception on port',self.name)
            while not self.stopped:
                data = self.getline()
                if len(data) > 0:
                    Space.write(self.name,data)
        except Exception as e:
            print(e)
            self.stop()

    def senseSelectAct(self):
        pass
    
class ReceiverAgent(Agent):

    def __init__(self,port,name):
        self.port = port
        self.name = name
        super().__init__()
        
    def init(self):
        print('server starting on port',self.port)
        try:
            sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            sock.bind(('0.0.0.0',self.port))
        except:
            self.stop()
        while not self.stopped:
            try:
                sock.listen(1)
                client, address = sock.accept()
                ReceiverServiceAgent(client,self.name)
            except:
                pass
        try:
            sock.close()
        except:
            pass
  
    def senseSelectAct(self):
        pass

class Recognize4PC:

    def __init__(self, port=7171):
        self.name = 'text'
        ReceiverAgent(port,self.name)
        self.matched = []
        self.text = ''

    def command(self):
        self.text = Space.read(self.name,'')
        Space.write(self.name,'')
        self.text = self.text.lower().strip()
        return self.text
    
    def match(self,pattern,text=''):
        search = re.search(pattern,text if text != '' else self.text)
        if search is None:
            self.matched = []
            return False
        else:
            self.matched = search.groups()
            return True

    def matched(self):
        return self.matched
