from celery import Celery

app = Celery('tasks', broker='redis://localhost')

@app.task
def mult(a, b):
    return a * b
