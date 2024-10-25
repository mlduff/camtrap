export interface Device {
    id: number;
    name: string;
    ip_address: string;
    enabled: boolean;
    configure_mode: boolean;
}

export default Device;