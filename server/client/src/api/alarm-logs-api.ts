import AlarmLog from "@/types/alarm-log";
import axios from "axios";

export async function getAlarmLogs() {
    const response = await axios.get<{ alarm_logs: AlarmLog[]}>("/dashboard/alarms");
    return response.data.alarm_logs;
}

export async function deleteAlarmLog(alarmLogId: number) {
    await axios.delete(`/dashboard/alarms/${alarmLogId}`);
}