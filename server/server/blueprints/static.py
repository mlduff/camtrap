import os

from flask import Blueprint
from flask import send_from_directory
from flask import current_app

blueprint = Blueprint("static", __name__)

@blueprint.route("/", defaults={"path": ""})
@blueprint.route("/<path:path>")
def serve_index(path):
    client_static_dir = current_app.config.get("CLIENT_STATIC_DIR")
    dir_path = os.path.join(os.getcwd(), client_static_dir)
    if path and os.path.exists(os.path.join(dir_path, path)):
        return send_from_directory(dir_path, path)
    return send_from_directory(dir_path, "index.html")