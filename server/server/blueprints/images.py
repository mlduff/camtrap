import os

from flask import Blueprint
from flask import send_from_directory
from flask import current_app

blueprint = Blueprint("images", __name__)

@blueprint.route("/<filename>")
def get_image(filename: str):
    images_dir = current_app.config.get("IMAGES_DIR")
    return send_from_directory(os.path.join(os.getcwd(), images_dir), filename)
