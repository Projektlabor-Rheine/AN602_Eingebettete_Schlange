
import CACConnection
import time
from time import sleep
import serial
import traceback

ser = serial.Serial("/dev/ttyS0", 115200)

# Starts the connection to the cac
def main():
    global con
    # Creates the cac-connection
    con = CACConnection.CACConnection("ws://85.214.207.75/ws/pi")
    print("AAAA")
    # Registers the key-packet-handler with the packet-id 0
    con.registerPacket(0, handleKeyupdate)
    print("BBB")
    # Starts the cac-connection to the server
    con.connect()


# Waits for a key-update packet
def handleKeyupdate(pkt: CACConnection.Packet):
    # Defines all keys that are required inside the packet
    keys = ["w", "a", "s", "d", "up", "down", "left", "right"]

    try:
        # Maps them to their respective values or throws an exception
        keys = dict(map(lambda k: [k, pkt.get_if_type_else_exception(k, bool)], keys))

        '''
        Keys will now contain a dictionary with "<Keyname>": <True/False>
        Access it by keys["<keyname>"]
        Eg: keys["w"] would now return either True or False
        '''
        sendKeys(keys)
    except Exception as ex:
        traceback.print_exception(type(ex), ex, ex.__traceback__)
        # This will execute if the packet did'nt contain all key's or one key wasn't valid

        pass


global totaltime
totaltime = [0,0]
time_dif = 0
lastkey = 0
global blocked
blocked = False

def forward():
    print("only w")
    ser.write(bytes("M,255,1,255,1,", 'utf-8'))
def backward():
    print("only s")
    ser.write(bytes("M,255,0,255,0,", 'utf-8'))
def left():
    print("only a")
    ser.write(bytes("M,128,0,128,1,", 'utf-8'))
def right():
    print("only d")
    ser.write(bytes("M,128,1,128,0,", 'utf-8'))
def forward_left():
    print("w and a")
    ser.write(bytes("M,128,1,255,1,", 'utf-8'))
def forward_right():
    print("w and d")
    ser.write(bytes("M,255,1,128,1,", 'utf-8'))
def backward_left():
    print("s and a")
    ser.write(bytes("M,128,0,255,0,", 'utf-8'))
def backward_right():
    print("s and d")
    ser.write(bytes("M,255,0,128,0,", 'utf-8'))
def stop_it_get_me_some_help():
    print("Stop")
    ser.write(bytes("M,0,0,0,0,", 'utf-8'))

def sendKeys(keys):
    global blocked, lastkey
    print(keys)
    #print(blocked)
    #print("Bla")
    #print(not blocked)
    if (keys['w'] and not (keys['a'] or keys['d'] or blocked)):
        forward()
        lastkey = 1
    elif(keys['a'] and not (keys['w'] or keys['s'] or blocked)):
        left()
        lastkey = 2
    elif(keys['s'] and not (keys['a'] or keys['d'] or blocked)):
        backward()
        lastkey = 3
    elif(keys['d'] and not (keys['w'] or keys['s'] or blocked)):
        right()
        lastkey = 4
    elif((keys['w'] and keys['a'])and not blocked):
        forward_left()
        lastkey = 5
    elif((keys['s'] and keys['a']) and not blocked):
        backward_left()
        lastkey = 6
    elif((keys['s'] and keys['d']) and not blocked):
        backward_right()
        lastkey = 7
    elif((keys['w'] and keys['d']) and not blocked):
        forward_right()
        lastkey = 8
    else:
        stop_it_get_me_some_help()
    sleep(0.005)
    if(keys['up']):
        print("Servo hoch")
        ser.write(bytes("S,0,-5,",'utf-8'))
    elif(keys['down']):
        print("Servo unten")
        ser.write(bytes("S,0,5,",'utf-8'))
    elif(keys['left']):
        print("Servo links")
        ser.write(bytes("S,1,5,",'utf-8'))
    elif(keys['right']):
        print("Servo rechts")
        ser.write(bytes("S,1,-5,",'utf-8'))

    
    sleep(0.001)
    #received_data = ser.read()
    #sleep(0.001)
    #data_left = ser.inWaiting()
    #received_data += ser.read(data_left)
    #print(received_data)
main()
while True:
    totaltime[1] = totaltime[0]
    totaltime[0] = time.time()
    time_dif = totaltime[0] - totaltime[1]
    while (ser.inWaiting() >= 0):
        line = ser.readline().decode('ascii').split("\r\n")[0] #.rstrip()
        print("line:{}".format(line))
        print("ser:{}".format(ser.read(10)))
        if(line == 'H' or line == 'V'):
            print("Nein,Nein, Nein")
            con.sendLineDetectionPacketQD(True)
            if(lastkey == 1):   #forward
                backward()
            elif(lastkey == 2): #backward
                forward()
            elif(lastkey == 3): #left
                right()
            elif(lastkey == 4): #right
                left()
            elif(lastkey == 5): #forward_left
                backward_right()
            elif(lastkey == 6): #backward_left
                forward_right()
            elif(lastkey == 7): #backward_right
                forward_left()
            elif(lastkey == 8): #forward_right
                backward_left()
            sleep(time_dif)
            stop_it_get_me_some_help()
        elif(line == 'S'):
            stop_it_get_me_some_help()
            blocked = True

    
    #sleep(0.001)
##    while(ser.inWaiting() > 0):
##        received_data = ser.read()
##        sleep(0.06)
##        data_left = ser.inWaiting()
##        received_data += ser.read(data_left)
##        print(received_data)

