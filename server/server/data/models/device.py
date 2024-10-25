import datetime
from dataclasses import dataclass

from sqlalchemy.orm import Mapped
from sqlalchemy.orm import mapped_column
from sqlalchemy.orm import relationship
from sqlalchemy.types import DateTime

from server.data import db

@dataclass
class Device(db.Model):

    __tablename__ = "devices"

    id: Mapped[int] = mapped_column(primary_key=True)
    name: Mapped[str] = mapped_column(db.String)
    ip_address: Mapped[str] = mapped_column(db.String, unique=True, nullable=True)
    last_heard_from: Mapped[DateTime] = mapped_column(db.DateTime, default=datetime.datetime.now)
    enabled: Mapped[bool] = mapped_column(db.Boolean, default=True)
    configure_mode: Mapped[bool] = mapped_column(db.Boolean, default=False)
    alarm_logs = relationship("AlarmLog", back_populates="device")
    