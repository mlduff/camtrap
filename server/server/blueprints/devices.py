from flask import Blueprint
from flask import request
from flask import jsonify

import server.services.devices as devices_service
import server.services.device_interactions as device_interactions_service
import server.services.rfid_tags as rfid_tags_service

blueprint = Blueprint("devices", __name__)

@blueprint.route("/connect", methods=["POST"])
def connect():
    device_id = request.data
    if device_id and device_id.isdigit():
        device_id = int(device_id)
        existing_device = devices_service.get_device_by_id(device_id)
        if existing_device:
            devices_service.update_device(device_id, request.remote_addr)
            return str(device_id)
    
    existing_device = devices_service.get_device_by_ip(request.remote_addr)
    if existing_device:
        devices_service.update_device(existing_device.id, None)

    device = devices_service.create_device("default", request.remote_addr)
    return jsonify({
        "device_id": device.id,
        "enabled": device.enabled
    })

@blueprint.route("/rfid", methods=["POST"])
def rfid():
    rfid_tag_uid = request.data.decode("utf-8")
    device = devices_service.get_device_by_ip(request.remote_addr)
    if device.configure_mode:
        rfid_tags_service.add_tag(rfid_tag_uid)
        return "success"
    else:
        exists = rfid_tags_service.tag_exists(rfid_tag_uid)
        if exists:
            devices_service.update_device_enabled(device.id, not device.enabled)
            device_interactions_service.set_enabled_status(device, not device.enabled)
            return "success"
        else:
            return "failure"
     