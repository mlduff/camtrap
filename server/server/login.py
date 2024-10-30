from flask_login import LoginManager

import server.services.users as user_service

def create_login_manager():
    login_manager = LoginManager()
    
    @login_manager.user_loader
    def load_user(user_id):
        return user_service.get_user(user_id)

    return login_manager