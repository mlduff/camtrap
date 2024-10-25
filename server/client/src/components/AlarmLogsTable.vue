<script setup lang="ts">
import { getAlarmLogs, deleteAlarmLog } from "@/api/alarm-logs-api";

const alarmLogs = ref(await getAlarmLogs());

async function deleteAndRefresh(alarmLogId: number) {
    await deleteAlarmLog(alarmLogId);
    alarmLogs.value = await getAlarmLogs();
}

</script>

<template>
    <v-card>
        <v-card-title>
            Alarm Logs
        </v-card-title>
        <v-card-text>
            <v-table>
                <thead>
                    <th>
                        ID
                    </th>
                    <th>
                        Device
                    </th>
                    <th>
                        Image
                    </th>
                    <th></th>
                </thead>
                <tbody>
                    <tr
                        v-for="alarmLog in alarmLogs"
                        class="pa-2"
                    >
                        <td>{{ alarmLog.id }}</td>
                        <td>{{ alarmLog.device_id }}</td>
                        <td><AlarmImage :filename="alarmLog.image_filename" class="image"/></td>
                        <td>
                            <v-btn
                                color="red"
                                @click="deleteAndRefresh(alarmLog.id)"
                            >
                                <v-icon>mdi-delete</v-icon>
                                Delete
                            </v-btn>
                        </td>
                    </tr>
                </tbody>
            </v-table>
        </v-card-text>
    </v-card>
</template>

<style scoped>

.image {
    width: 256px;
}

</style>