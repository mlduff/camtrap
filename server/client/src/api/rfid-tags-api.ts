import { RfidTag } from "@/types/rfid-tag";
import axios from "axios";

export async function getRfidTags() {
    const response = await axios.get<{ tags: RfidTag[] }>("/dashboard/rfid-tags");
    return response.data.tags;
}

export async function deleteRfidTags(uid: string) {
    await axios.delete(`/dashboard/rfid-tags/${uid}`);
}