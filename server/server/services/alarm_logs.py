from sqlalchemy import select

from server.data import db
from server.data.models.alarm_log import AlarmLog

def create_alarm_log(image_filename, device_id):
    alarm_log = AlarmLog(
        image_filename=image_filename,
        device_id=device_id
    )

    db.session.add(alarm_log)
    db.session.commit()

    return alarm_log

def get_alarm_logs():
    return db.session.execute(
        select(AlarmLog)
    ).scalars().all()

def get_alarm_log(alarm_log_id: int):
    return db.session.execute(
        select(AlarmLog)
        .where(AlarmLog.id == alarm_log_id)
    ).scalar_one_or_none()

def delete_alarm_log(alarm_log_id: int):
    alarm_log = get_alarm_log(alarm_log_id)

    db.session.delete(alarm_log)
    db.session.commit()

    return alarm_log.image_filename