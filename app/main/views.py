from . import main

from ..tasks import rtest

result = None

@main.route('/')
def index():
    return "I work"

@main.route('/celtest')
def celtest():
    global result 
    result = rtest.delay()
    return result.state

@main.route('/celtest2')
def celtest2():
    global result
    if result is not None:
        return result.state
    else:
        return "nothing"
