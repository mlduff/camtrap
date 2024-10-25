from sqlalchemy import select
from sqlalchemy import delete

from server.data import db
from server.data.models.rfid_tag import RfidTag

def add_tag(uid: str):
    if not tag_exists(uid):
        rfid_tag = RfidTag(uid=uid)

        db.session.add(rfid_tag)
        db.session.commit()

        return rfid_tag
    return None

def delete_tag(uid: str):
    db.session.execute(
        delete(RfidTag)
        .where(RfidTag.uid == uid)
    )
    db.session.commit()

def tag_exists(uid: str) -> bool:
    return get_tag(uid) is not None

def get_tag(uid: str) -> bool:
    return db.session.execute(
        select(RfidTag)
        .where(RfidTag.uid == uid)
    ).scalar_one_or_none()

def get_tags():
    return db.session.execute(
        select(RfidTag)
    ).scalars().all()