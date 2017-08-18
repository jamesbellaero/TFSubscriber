from serial import Serial
from xbee import XBee
import time
ser=Serial('COM11','9600')
ser.write(b'Hello world!\n')
xbee=XBee(ser)
# for i in range(0,256):
#     for j in range(0,256):
#         b1=bytes([i])
#         b2=bytes([j])
#         xbee.tx(dest_addr=b1+b2, data='Howdy wurld')
#         print("Testing "+str(b1+b2))
#         time.sleep(.01)
xbee.send('at',  command='DH')
response = xbee.wait_read_frame()
print(response)
#for frames
# xb =XBee(ser)
# xb.send(command='Hello world!')
# print xb.wait_read_frame()#waits on a command to come in
