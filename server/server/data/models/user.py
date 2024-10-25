from dataclasses import dataclass

from sqlalchemy.orm import Mapped
from sqlalchemy.orm import mapped_column

from server.data import db

@dataclass
class User(db.Model):

    __tablename__ = "users"

    username: Mapped[str] = mapped_column(db.String, primary_key=True)
    password: Mapped[str] = mapped_column(db.String)