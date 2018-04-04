# -*- coding: utf-8 -*-
"""
Created on Wed Feb 28 18:23:48 2018

@author: lizi
"""

#import matplotlib.pyplot as pl
import numpy as np
import serial
import serial.tools.list_ports
import time


plist = list(serial.tools.list_ports.comports())

if len(plist) <= 0:
    print("The Serial port can't find!")
    exit(0)
else:
    plist_0 =list(plist[0])
    serialName = plist_0[0]
    print(serialName)
    ser = serial.Serial(port=serialName, baudrate=38400, bytesize=8, timeout=2)


c='b'
a=1
b=0
while(True):
    if(c=='q'):
        break
    elif (c=='a'):
     #   ser = serial.Serial(port=serialName, baudrate=38400, bytesize=8, timeout=2)
        Weight=[]
        mass=[]
        data=[]
        for i in range(5):
            Weight=[]
            c=input('Input The Mass of Weight: ')
            ser.write('1'.encode('ascii'))
            for j in range(300):
                Weight.append(float(ser.readline().decode('gb18030')))
            mass.append(sum(Weight)/300.0)
            data.append(float(c))
            
        mass=np.array(mass)    
        data=np.array(data)
        a=(sum(mass*data)-sum(mass)*sum(data)/5)/(sum(data**2)-(sum(data)**2)/5)
        b=sum(mass)/5.0-a*sum(data)/5.0
        print('Done!')
        
    while(True):
        c=input('Please Input "s" to Start:')
        if(c=='s'):
            time.sleep(2)
            break
        
    data=[]
    #ser = serial.Serial(port=serialName, baudrate=38400, bytesize=8, timeout=2)
    try:
        ser.write('2'.encode('ascii'))
        while(True):
            data.append(a*float(ser.readline().decode('gb18030').replace('000\r\n','') )+b)
            print(data[-1])

    except KeyboardInterrupt:
        ser.write('x'.encode('ascii'))
        ser.read_all()
        ser.close()
        #pl.plot(range(len(data)),data)
        with open(time.strftime('%H-%M-%S',time.localtime(time.time()))+'.txt','w') as fp:
            for i in data:
                fp.write(str(i)+'\n')
            
        c=input('''Continue with Adjust -- a 
                Countinue without Adjust --o
                Quit --q''')
        
    
