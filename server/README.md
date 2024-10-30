# Server
The server is responsible for keeping a record of all the alarm logs, and is also able to provide remote management of the alarm devices.

# Setup
1. Create a Python virtual environment by running the following in the root `server` folder.
```
python -m venv .venv
```
2. Active the virtual environment (command will vary on Windows vs UNIX)
3. Run the following command to install the required dependencies
```
pip install -r requirements.txt
```
4. From within the `client` sub folder:
    1. Run `npm install`
    2. Run `npm run build`.
5. Check `config.json` and ensure that `SQLALCHEMY_DATABASE_URI` contains the correct specification to allow it to connect to a PostgreSQL database.
6. From the top-level `server` directory, run `flask --app server init` to initialize the server.

# Execution
To start the development server, run the following from the top-level `server` directory:
```
flask --app server run --host=0.0.0.0
```

# Use
- The default login details are username: `admin`, password: `admin`