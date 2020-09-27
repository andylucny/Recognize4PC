import os
import io

class BoeBot:
    
    def __init__(self,line='/dev/ttyUSB0'):
        '''Creates a BoeBot object that you can call to control the robot.
        '''
        self.tty = os.open(line,os.O_NOCTTY | os.O_RDWR | os.O_NONBLOCK)
    
    def write(self,command):
        ''' write comand to line
        '''
        
        os.write(self.tty,bytes(command,'ascii'))

    def read(self):
        ''' read response
        '''
        try:
            return os.read(self.tty,16).decode('ascii')
        except:
            return ''

    def rotateLeft(self):
        self.write('pl\r\n')

    def rotateRight(self):
        self.write('pr\r\n')
        
    def goForward(self):
        self.write('pf\r\n')
        
    def goBackward(self):
        self.write('pb\r\n')
        
    def stop(self):
        self.write('pz\r\n')

# Test    
if __name__ == "__main__":

    import time
    robot = BoeBot()
    print('right')
    robot.rotateRight()
    time.sleep(2)
    print('left')
    robot.rotateLeft()
    time.sleep(2)
    print('forward')
    robot.goForward()
    time.sleep(2)
    print('backward')
    robot.goBackward()
    time.sleep(2)
    print('stop')
    robot.stop()
