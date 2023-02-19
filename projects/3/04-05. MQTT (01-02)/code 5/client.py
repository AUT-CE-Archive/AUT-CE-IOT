import ast
from datetime import datetime
import paho.mqtt.client as mqtt


client = mqtt.Client()
HOST = 'bb88c124.us-east-1.emqx.cloud'
PORT = 15465
KEEPALIVE = 60
topic = "python/mqtt"
USERNAME = 'keivanipchihagh'
PASSWORD = '123456789'

# Callback for connection
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print("Failed to connect, return code %d\n", rc)

# Callback for receiving messages
def on_message_receive(client, userdata, msg):
    update = ast.literal_eval(msg.payload.decode("utf-8"))
    print(f"{datetime.now()}) Received Update from Broker! Temperature: {update['temperature']}, Brightness: {update['brightness']}")


if __name__ == "__main__":

    # Register callbacks
    client.on_connect = on_connect
    client.on_message = on_message_receive

    # Establish connection with authentication
    client.username_pw_set(USERNAME, PASSWORD)
    client.connect(HOST, PORT, KEEPALIVE)

    # Subscribe to topics
    client.subscribe("room")

    # Hang client
    client.loop_forever()