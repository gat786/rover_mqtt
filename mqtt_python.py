import paho.mqtt.client as paho
import threading
import time
import serial
import serial.tools.list_ports as ports 


ser = ''

for usb in ports.comports():
    if usb.serial_number == '55730303037351D05242':
        ser = serial.Serial(usb.device)

def on_connect(client, userdata, flags, rc):
    print("connected: ", str(client.client_id))

def on_message(client, obj, msg):
    message = str(msg.payload,encoding="utf-8")
    print(" recieved " , str(msg.qos) ," " , message)
    if(message=="forward"):
        ser.write(b'1')
    elif(message=="backward"):
        ser.write(b'2')

def on_publish(client, obj, mid):
    print("mid: " + str(mid))

def on_subscribe(client, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))
    
def listen(client):
    client.subscribe("directions")
    client.loop_forever()

def danger_publish(message):
    client.publish("obstacle",payload=message)

danger_yes = "yes \n"
danger_no = "no \n"

def read_serial(port,mclient):
    while True:
        try:
            if port.inWaiting()>0:
                if port.readline().decode('utf-8')==danger_yes:
                    danger_publish("YES") 
                    time.sleep(0.3)
                print(port.readline())
            else:
                danger_publish("No")
                time.sleep(0.3)
        except OSError:
            print('error occured')

def publish(client,temp=None,humidity=None,obstacle=None):
    import random
    while True:
        if(temp!=None):
            client.publish("temp",payload=temp,qos=1)
        if(humidity!=None):
            client.publish("humidity",payload=humidity,qos=1)
        if(obstacle!=None):
            client.publish("obstacle",payload=obstacle,qos=1)
        print("published the data")


def registerFunstions(client):
    client.on_connect = on_connect
    client.on_message = on_message
    client.on_subscribe = on_subscribe
    client.on_publish = on_publish
    
    
if __name__ == '__main__':
    client = paho.Client("rover")
    registerFunstions(client)
    client.connect("127.0.0.1",1883)
    
    publisher = paho.Client("publisher")
    registerFunstions(publisher)
    publisher.connect("127.0.0.1",1883)
    
    t1  = threading.Thread(target=listen,args=(client,))
    t2 = threading.Thread(target=read_serial,args=(ser,publisher,))
    t1.start()
    time.sleep(1)
    t2.start()
