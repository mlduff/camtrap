import datetime

from sqlalchemy import select
from sqlalchemy import update

from server.data import db
from server.data.models.device import Device

def create_device(name: str, ip_address: str):
    device = Device(
        name=name,
        ip_address=ip_address,
        last_heard_from=datetime.datetime.now(),
        enabled=True
    )

    db.session.add(device)
    db.session.commit()

    return device

def update_device(device_id: int, ip_address: str):
    db.session.execute(
        update(Device)
        .where(Device.id == device_id)
        .values(ip_address=ip_address)
    )

    db.session.commit()

def update_device_enabled(device_id: int, enabled: bool):
    db.session.execute(
        update(Device)
        .where(Device.id == device_id)
        .values(enabled=enabled)
    )

    db.session.commit()

def update_device_configure_mode(device_id: int, configure_mode: bool):
    db.session.execute(
        update(Device)
        .where(Device.id == device_id)
        .values(configure_mode=configure_mode)
    )

    db.session.commit()

def get_device_by_ip(ip_address: str):
    return db.session.execute(
        select(Device)
        .where(Device.ip_address == ip_address)
    ).scalar_one_or_none()

def get_device_by_id(device_id):
    return db.session.execute(
        select(Device)
        .where(Device.id == device_id)
    ).scalar_one_or_none()

def get_devices():
    return db.session.execute(
        select(Device)
    ).scalars().all()