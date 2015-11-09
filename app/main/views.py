from . import main

from ..tasks import rtest

@main.route('/')
def index():
    return "I work"

@main.route('/celtest')
def celtest():
    result = rtest.delay()
    return result.state
