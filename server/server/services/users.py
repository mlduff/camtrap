from sqlalchemy import select
from werkzeug.security import generate_password_hash, check_password_hash

from server.data import db
from server.data.models.user import User

def create_user(username: str, password: str):
    password_hash = generate_password_hash(password, method="scrypt")

    user = User(
        username=username,
        password=password_hash
    )

    db.session.add(user)
    db.session.commit()

    return user

def get_user(username: str):
    return db.session.execute(
        select(User)
        .where(User.username == username)
    ).scalar_one_or_none()

def login_user(username: str, password: str):
    user = get_user(username)

    if user and check_password_hash(user.password, password):
        return user
    
    raise Exception("Incorrect details.")
    


