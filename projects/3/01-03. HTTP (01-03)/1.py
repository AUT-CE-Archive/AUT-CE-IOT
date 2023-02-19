import uvicorn
from fastapi import FastAPI

app = FastAPI()

# curl http://0.0.0.0:8000/helloworld
@app.get("/helloworld")
def read_root():
    return "Hello World!"


if __name__ == "__main__":
    uvicorn.run(
        app = "1:app",
        host = "0.0.0.0",
        port = 8000,
        reload = True,
    )