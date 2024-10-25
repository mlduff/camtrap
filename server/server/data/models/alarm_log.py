import datetime
from dataclasses import dataclass

from sqlalchemy.orm import Mapped
from sqlalchemy.orm import mapped_column
from sqlalchemy.orm import relationship
from sqlalchemy import ForeignKey
from sqlalchemy.types import DateTime

from server.data import db
from server.data.models.device import Device

@dataclass
class AlarmLog(db.Model):

    __tablename__ = "alarm_logs"

    id: Mapped[int] = mapped_column(primary_key=True)
    image_filename: Mapped[str] = mapped_column(db.String, nullable=True)
    timestamp: Mapped[DateTime] = mapped_column(db.DateTime, default=datetime.datetime.now)
    device_id: Mapped[int] = mapped_column(ForeignKey("devices.id"))
    device: Mapped["Device"] = relationship(back_populates="alarm_logs")


    