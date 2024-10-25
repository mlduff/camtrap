import datetime
from dataclasses import dataclass

from sqlalchemy.orm import Mapped
from sqlalchemy.orm import mapped_column
from sqlalchemy.types import DateTime

from server.data import db

@dataclass
class RfidTag(db.Model):

    __tablename__ = "rfid_tags"

    uid: Mapped[str] = mapped_column(db.String, primary_key=True)
    created_at: Mapped[DateTime] = mapped_column(db.DateTime, default=datetime.datetime.now)
