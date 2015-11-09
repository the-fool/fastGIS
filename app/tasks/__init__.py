from celery import Celery

app = Celery('tasks', broker='redis//localhost')

from .tasks import mult
