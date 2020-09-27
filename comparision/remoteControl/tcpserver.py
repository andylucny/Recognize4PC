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
        
    def get(self):
        if len(self.buffer) == 0:
            self.buffer = self.socket.recv(1024).decode()
        if len(self.buffer) == 0:
            return ''
        result = self.buffer[:1]
        self.buffer = self.buffer[1:]
        return result
     
    def put(self,data):
        self.socket.send((data).encode())
        
    def init(self):
        try:
            print('starting reception on port',self.name)
            while not self.stopped:
                data = self.get()
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
        except Exception as e:
            print('tcpserver',e)
            self.stop()
        while not self.stopped:
            try:
                sock.listen(1)
                client, address = sock.accept()
                ReceiverServiceAgent(client,self.name)
            except Exception as e:
                print('tcpserver',e)
        try:
            sock.close()
        except Exception as e:
            print('tcpserver',e)
  
    def senseSelectAct(self):
        pass

class TcpServer:

    def __init__(self, port=7171):
        self.name = 'text'
        ReceiverAgent(port,self.name)
        self.matched = []

    def command(self):
        text = Space.read(self.name,'')
        Space.write(self.name,'')
        text = text.lower().strip()
        return text
    