import os
import uuid

from flask import Blueprint
from flask import request
from flask import current_app

import server.services.alarm_logs as alarm_logs_service
import server.services.devices as devices_service

blueprint = Blueprint("alarms", __name__)

@blueprint.route("/", methods=["POST"])
def create_alarm():
    images_dir = current_app.config.get("IMAGES_DIR")

    device = devices_service.get_device_by_ip(request.remote_addr)

    image_file = request.files["file"]

    filename = str(uuid.uuid4()) + "-" + image_file.filename
    image_file.save(os.path.join(os.getcwd(), images_dir, filename))

    alarm_logs_service.create_alarm_log(filename, device.id)

    return ""