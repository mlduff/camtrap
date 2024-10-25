import axios from "axios";

import { Device } from "@/types/device";

export async function getDevices() {
    const response = await axios.get<{ devices: Device[] }>("/dashboard/devices");
    return response.data.devices;
}

export async function getDevice(deviceId: number) {
    const response = await axios.get<Device>(`/dashboard/devices/${deviceId}`);
    return response.data;
}

export async function takePicture(deviceId: number) {
    const response = await axios.get<{ filename: string | null }>(`/dashboard/devices/${deviceId}/picture`);
    return response.data.filename;
}

export async function setDeviceEnabled(deviceId: number, enabled: boolean) {
    await axios.post(
        `/dashboard/devices/${deviceId}/enabled`,
        {
            enabled: enabled,
        }
    );
}

export async function setDeviceConfigureMode(deviceId: number, configureMode: boolean) {
    await axios.post(
        `/dashboard/devices/${deviceId}/configure-mode`,
        {
            configure_mode: configureMode,
        }
    );
}

export async function resetDeviceNetwork(deviceId: number) {
    await axios.post(
        `/dashboard/devices/${deviceId}/reset-network`
    );
}