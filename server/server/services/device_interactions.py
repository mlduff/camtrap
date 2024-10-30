import os
import uuid

import requests

from server.data.models.device import Device

def take_picture(device: Device, images_dir: str):
    r = requests.get(f"http://{device.ip_address}/picture")

    if r.status_code == 200:
        content_type = r.headers["Content-Type"]
        extension = content_type.split("/")[-1]

        filename = str(uuid.uuid4()) + f".{extension}"

        images_dir_path = os.path.join(os.getcwd(), images_dir)
        if not os.path.exists(images_dir_path):
            os.mkdir(images_dir_path)

        with open(os.path.join(images_dir_path, filename), "wb+") as f:
            f.write(r.content)
        return filename
    
    return None

def set_enabled_status(device: Device, enabled: bool):
    requests.post(
        f"http://{device.ip_address}/enabled",
        json={
            "enabled": enabled
        }
    )

def reset_network(device: Device):
    requests.post(
        f"http://{device.ip_address}/network",
        json={
            "ssid": None,
            "password": None,
            "server_address": None
        }
    )
