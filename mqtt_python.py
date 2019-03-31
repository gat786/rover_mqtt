import paho.mqtt.client as paho
import threading
import time

def on_connect(client, userdata, flags, rc):
    print("connected: ", str(rc))

def on_message(client, obj, msg):
    print(" recieved " , str(msg.qos) ," " , str(msg.payload,encoding="utf-8"))

def on_publish(client, obj, mid):
    print("mid: " + str(mid))

def on_subscribe(client, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))
    
def listen(client):
    client.subscribe("directions")
    client.loop_forever()

def publish(client,temp=None,humidity=None,obstacle=None):
    while True:
        if(temp!=None):
            client.publish("temp",payload=temp,qos=1)
        if(humidity!=None):
            client.publish("humidity",payload=humidity,qos=1)
        if(obstacle!=None):
            client.publish("obstacle",payload=obstacle,qos=1)
        print("published the data")
        time.sleep(1)

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
    t2 = threading.Thread(target=publish,args=(publisher,),kwargs={"temp":32})
    t1.start()
    time.sleep(1)
    t2.start()
