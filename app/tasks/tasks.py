from . import app

@app.task
def mult(a, b):
    return a * b
