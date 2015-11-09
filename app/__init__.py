from flask import Flask

def create_app():
    app = Flask(__name__)
    
    from .main import main as main_blueprint
    app.register_blueprint(main_blueprint)
    
    app.debug = True
    return app

apple = create_app()
