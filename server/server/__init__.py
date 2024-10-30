import os
import json

from flask import Flask
import click

from server.data import db
from server.blueprints.devices import blueprint as devices_blueprint
from server.blueprints.auth import blueprint as auth_blueprint
from server.blueprints.alarms import blueprint as alarms_blueprint
from server.blueprints.images import blueprint as images_blueprint
from server.blueprints.dashboard import blueprint as dashboard_blueprint
from server.blueprints.static import blueprint as static_blueprint
from server.login import create_login_manager
import server.services.users as user_service

def create_app():
    app = Flask(__name__)

    app.config.from_file("config.json", load=json.load)
    app.config["CLIENT_STATIC_DIR"] = os.path.join("client", "dist")
    app.secret_key = app.config["SECRET_KEY"]

    db.init_app(app)

    login_manager = create_login_manager()
    login_manager.init_app(app)

    app.register_blueprint(devices_blueprint, url_prefix="/devices")
    app.register_blueprint(auth_blueprint, url_prefix="/auth")
    app.register_blueprint(alarms_blueprint, url_prefix="/alarms")
    app.register_blueprint(images_blueprint, url_prefix="/images")
    app.register_blueprint(dashboard_blueprint, url_prefix="/dashboard")
    app.register_blueprint(static_blueprint)

    @app.cli.command("init")
    def init():
        with app.app_context():
            db.create_all()
        user_service.create_user("admin", "admin")
        click.echo("Initialized data.")

    @app.cli.command("destroy")
    def destroy():
        with app.app_context():
            db.drop_all()
        click.echo("Destroyed data.")

    return app