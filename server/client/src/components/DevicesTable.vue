<script setup lang="ts">
import { getDevices } from '@/api/device-api';
import router from '@/router';

const devices = await getDevices();

</script>

<template>
    <div class="container">
        <v-card>
            <v-card-title>
                Devices
            </v-card-title>
            <v-card-text>
                <v-table>
                    <thead>
                        <th>
                            ID
                        </th>
                        <th>
                            Name
                        </th>
                        <th>
                            IP Address
                        </th>
                        <th></th>
                    </thead>
                    <tbody>
                        <tr
                            v-for="device in devices"
                        >
                            <td>{{ device.id }}</td>
                            <td>{{ device.name }}</td>
                            <td>{{ device.ip_address }}</td>
                            <td>
                                <v-btn
                                    color="primary"
                                    @click="router.push(`/devices/${device.id}`)"
                                >
                                    View
                                </v-btn>
                            </td>
                        </tr>
                    </tbody>
                </v-table>
            </v-card-text>
        </v-card>
    </div>
</template>

<style>

.container {
    width: 100%;
}

th {
    margin-left: 0;
}

</style>