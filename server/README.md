# Server
The server is responsible for keeping a record of all the alarm logs, and is also able to provide remote management of the alarm devices.

## Setup
1. Create a Python virtual environment by running the following in the root `server` folder.
```
python -m venv .venv
```
2. Active the virtual environment (command will vary on Windows vs UNIX)
3. Run the following command to install the required dependencies
```
pip install -r requirements.txt
```
4. From within the `client` folder:
    1. Run `npm install`
    2. Run `npm run build`.

## Execution
To start the development server, run the following from the top-level `server` directory:
```
flask --app server run --host=0.0.0.0
```