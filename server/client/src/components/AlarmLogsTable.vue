<script setup lang="ts">
import { getAlarmLogs, deleteAlarmLog } from "@/api/alarm-logs-api";

const alarmLogs = ref(await getAlarmLogs());
const timer = ref();

async function deleteAndRefresh(alarmLogId: number) {
    await deleteAlarmLog(alarmLogId);
    await updateLogs();
}

async function updateLogs() {
    alarmLogs.value = await getAlarmLogs();
}

onMounted(() => {
    timer.value = setInterval(updateLogs, 1000);
});

onBeforeUnmount(() => {
    clearInterval(timer.value);
    timer.value = null;
})

</script>

<template>
    <div class="container">
        <v-card>
            <v-card-title>
                Alarm Logs
            </v-card-title>
            <v-card-text>
                <v-table>
                    <thead>
                        <tr>
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
                        </tr>
                    </thead>
                    <tbody>
                        <tr
                            v-for="alarmLog in alarmLogs"
                        >
                            <td>{{ alarmLog.id }}</td>
                            <td><a :href="`/devices/${alarmLog.device_id}`">{{ alarmLog.device.name }}</a></td>
                            <td><AlarmImage :filename="alarmLog.image_filename" class="image pa-2"/></td>
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
    </div>
</template>

<style scoped>


.container {
    width: fit-content;
}

.image {
    width: 256px;
}

.row {
    padding: 1em;
}

</style>