import Device from "./device";

export default interface AlarmLog {
    id: number;
    image_filename: string;
    device_id: number;
    device: Device;
}