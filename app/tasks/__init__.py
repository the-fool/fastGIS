from celery import Celery

app = Celery('tasks', broker='redis://localhost:6379', 
             backend='redis://localhost')

from .tasks import mult, rtest
