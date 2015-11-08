from . import main

@main.route('/')
def index():
    return "I work"
