import time
import uvicorn
from fastapi import FastAPI, Request
import paho.mqtt.client as mqtt
from fastapi.middleware.cors import CORSMiddleware

client = mqtt.Client()
app = FastAPI()
HOST = 'bb88c124.us-east-1.emqx.cloud'
PORT = 15465
KEEPALIVE = 60
topic = "python/mqtt"
USERNAME = 'keivanipchihagh'
PASSWORD = '123456789'

origins = ["*"]

app.add_middleware(
    CORSMiddleware,
    allow_origins=origins,
    allow_credentials=True,
    allow_methods=["*"],
    allow_headers=["*"],
)

# ----------------------------------- MQTT ----------------------------------- #

# Callback for connection
def on_connect(client, userdata, flags, rc):
    if rc == 0:
        print("Connected to MQTT Broker!")
    else:
        print("Failed to connect, return code %d\n", rc)

# ----------------------------------- API ----------------------------------- #

@app.post("/update")
async def set_temperature(request: Request):
    body = await request.json()

    # Connect
    client.on_connect = on_connect
    client.username_pw_set(USERNAME, PASSWORD)
    client.connect(HOST, PORT, KEEPALIVE)

    # Publish
    result = client.publish(topic = "room", payload = str(body))
    print("Sucess" if result[0] == 0 else "Failed")
    

if __name__ == "__main__":
    uvicorn.run(
        app = "server:app",
        host = "0.0.0.0",
        port = 8000,
        reload = True,
    )