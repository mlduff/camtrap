import os

from flask import Blueprint
from flask import jsonify
from flask import current_app
from flask import request
from flask_login import login_required

import server.services.devices as devices_service
import server.services.alarm_logs as alarm_logs_service
import server.services.device_interactions as device_interactions_service
import server.services.rfid_tags as rfid_tags_service

blueprint = Blueprint("dashboard", __name__)

@blueprint.before_request
@login_required
def before_request():
    pass

@blueprint.route("/devices")
def devices_list():
    devices = devices_service.get_devices()
    return jsonify({
        "devices": devices
    })

@blueprint.route("/devices/<int:device_id>")
def device_get(device_id):
    device = devices_service.get_device_by_id(device_id)
    return jsonify(device)

@blueprint.route("/alarms")
def alarms_list():
    alarm_logs = alarm_logs_service.get_alarm_logs()
    return jsonify({
        "alarm_logs": alarm_logs
    })

@blueprint.route("/alarms/<int:alarm_log_id>", methods=["DELETE"])
def delete_alarm_log(alarm_log_id: int):
    images_dir = current_app.config.get("IMAGES_DIR")
    image_filename = alarm_logs_service.delete_alarm_log(alarm_log_id)
    image_path = os.path.join(os.getcwd(), images_dir, image_filename)

    try:
        os.remove(image_path)
    except FileNotFoundError:
        pass

    return "success"

@blueprint.route("/devices/<int:device_id>/picture")
def take_picture(device_id: int):
    device = devices_service.get_device_by_id(device_id)
    filename = device_interactions_service.take_picture(device, current_app.config.get("IMAGES_DIR"))
    return jsonify({
        "filename": filename
    })

@blueprint.route("/devices/<int:device_id>/enabled", methods=["POST"])
def set_device_enabled(device_id: int):
    enabled: bool = request.json["enabled"]

    device = devices_service.get_device_by_id(device_id)
    devices_service.update_device_enabled(device_id, enabled)
    device_interactions_service.set_enabled_status(device, enabled)

    return "success"

@blueprint.route("/devices/<int:device_id>/reset-network", methods=["POST"])
def reset_device_network(device_id: int):
    device = devices_service.get_device_by_id(device_id)
    device_interactions_service.reset_network(device)

    return "success"

@blueprint.route("/devices/<int:device_id>/configure-mode", methods=["POST"])
def set_device_configure_mode(device_id: int):
    configure_mode: bool = request.json["configure_mode"]

    devices_service.update_device_configure_mode(device_id, configure_mode)

    return "success"

@blueprint.route("/rfid-tags")
def get_rfid_tags():
    rfid_tags = rfid_tags_service.get_tags()

    return jsonify({
        "tags": rfid_tags
    })

@blueprint.route("/rfid-tags/<uid>", methods=["DELETE"])
def delete_rfid_tags(uid: str):
    rfid_tags_service.delete_tag(uid)

    return "success"