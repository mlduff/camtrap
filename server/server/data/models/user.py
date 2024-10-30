from dataclasses import dataclass

from sqlalchemy.orm import Mapped
from sqlalchemy.orm import mapped_column

from server.data import db

@dataclass
class User(db.Model):

    __tablename__ = "users"

    username: Mapped[str] = mapped_column(db.String, primary_key=True)
    password: Mapped[str] = mapped_column(db.String)

    @property
    def is_active(self):
        return True
    
    @property
    def is_authenticated(self):
        return True
    
    @property
    def is_anonymous(self):
        return False
    
    def get_id(self):
        return self.username