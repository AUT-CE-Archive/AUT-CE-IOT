import random
import uvicorn
from fastapi import FastAPI, Request


class CoffeeMachine(object):

    def __init__(self) -> None:
        self.water = random.randint(0, 100)
        self.milk = random.randint(0, 100 - self.water)
        self.coffee = random.randint(0, 100 - self.water - self.milk)
        self.coffee_names = ["latte", "cappuccino", "espresso"]
        self.scheduled_coffee_name = "cappuccino"
        self.scheduled_coffee_time = f"{random.randint(0, 23)}:{random.randint(0, 59)}:{random.randint(0, 59)}"

    def get_resources(self):
        return {"water": self.water, "milk": self.milk, "coffee": self.coffee}

    def get_coffee_names(self):
        return self.coffee_names

    def get_scheduled_coffee_name(self):
        return self.scheduled_coffee_name

    def get_scheduled_coffee_time(self):
        return self.scheduled_coffee_time

    def set_resources(self, water: int, milk: int, coffee: int):
        self.water = water
        self.milk = milk
        self.coffee = coffee

    def set_coffee_names(self, coffee_names: list):
        self.coffee_names = coffee_names

    def set_scheduled_coffee_name(self, scheduled_coffee_name: str):
        self.scheduled_coffee_name = scheduled_coffee_name
    
    def set_scheduled_coffee_time(self, scheduled_coffee_time: str):
        self.scheduled_coffee_time = scheduled_coffee_time



app = FastAPI()
coffemachine = CoffeeMachine()



# curl -X GET http://0.0.0.0:8000/machineresources
@app.get("/machineresources")
async def get_machineresources():
    return coffemachine.get_resources()

# curl -X GET http://0.0.0.0:8000/coffeenames
@app.get("/coffeenames")
async def get_coffeenames():
    return {"cofee_names": coffemachine.get_coffee_names()}

# curl -X GET http://0.0.0.0:8000/scheduled_coffee_name
@app.get("/scheduled_coffee_name")
async def get_scheduled_coffee_name():
    return {"scheduled_coffee_name": coffemachine.get_scheduled_coffee_name()}

# curl -X GET http://0.0.0.0:8000/scheduled_coffee_time
@app.get("/scheduled_coffee_time")
async def get_scheduled_coffee_time():
    return {"scheduled_coffee_time": coffemachine.get_scheduled_coffee_time()}



# curl -X PUT -d '{"milk": 50, "water": 30, "coffee": 20}' http://0.0.0.0:8000/machineresources
@app.put("/machineresources")
async def put_machineresources(request: Request):
    resources = await request.json()
    coffemachine.set_resources(resources["water"], resources["milk"], resources["coffee"])
    return "Resources Updated"

# curl -X PUT -d '{"cofee_names": ["americano", "mocha", "macchiato"]}' http://0.0.0.0:8000/coffeenames
@app.put("/coffeenames")
async def put_coffeenames(request: Request):
    coffee_names = await request.json()
    coffemachine.set_coffee_names(coffee_names["cofee_names"])
    return "Coffee Names Updated"

# curl -X PUT -d '{"scheduled_coffee_name": "americano"}' http://0.0.0.0:8000/scheduled_coffee_name
@app.put("/scheduled_coffee_name")
async def put_scheduled_coffee_name(request: Request):
    scheduled_coffee_name = await request.json()
    coffemachine.set_scheduled_coffee_name(scheduled_coffee_name["scheduled_coffee_name"])
    return "Scheduled Coffee Name Updated"

# curl -X PUT -d '{"scheduled_coffee_time": "6:12:20"}' http://0.0.0.0:8000/scheduled_coffee_time
@app.put("/scheduled_coffee_time")
async def put_scheduled_coffee_time(request: Request):
    scheduled_coffee_time = await request.json()
    coffemachine.set_scheduled_coffee_time(scheduled_coffee_time["scheduled_coffee_time"])
    return "Scheduled Coffee Time Updated"



if __name__ == "__main__":
    uvicorn.run(
        app = "2:app",
        host = "0.0.0.0",
        port = 8000,
        reload = True,
    )