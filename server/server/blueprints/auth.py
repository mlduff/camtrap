from flask import Blueprint
from flask import request
from flask import jsonify
from flask_login import login_required
from flask_login import logout_user
from flask_login import login_user

import server.services.users as user_service

blueprint = Blueprint("auth", __name__)

@blueprint.route("/register", methods=["POST"])
def register():
    username: str = request.json["username"]
    password: str = request.json["password"]

    user = user_service.create_user(username, password)
    login_user(user)

    return user.username

@blueprint.route("/login", methods=["POST"])
def login():
    username: str = request.json["username"]
    password: str = request.json["password"]

    user = user_service.login_user(username, password)
    login_user(user)
    
    return user.username
    
@blueprint.route("/logout", methods=["POST"])
@login_required
def logout():
    logout_user()
    return "success"