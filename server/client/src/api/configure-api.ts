import axios from "axios";

const DEVICE_IP = "192.168.4.1";

export async function configure(ssid: string, password: string, serverAddress: string) {
    await axios.post(
        `http://${DEVICE_IP}/network`,
        {
            ssid: ssid,
            password: password,
            server_address: serverAddress
        }
    );
}