<script setup lang="ts">
import { deleteRfidTags, getRfidTags } from '@/api/rfid-tags-api';

const rfidTags = ref(await getRfidTags());

async function deleteAndRefresh(uid: string) {
    await deleteRfidTags(uid);
    rfidTags.value = await getRfidTags();
}

</script>

<template>
    <div class="container">
        <v-card>
            <v-card-title>
                Configured RFID Tags
            </v-card-title>
            <v-card-text>
                <v-table>
                    <thead>
                        <th>
                            UID
                        </th>
                        <th></th>
                    </thead>
                    <tbody>
                        <tr
                            v-for="rfidTag in rfidTags"
                        >
                            <td>{{ rfidTag.uid }}</td>
                            <td>
                                <v-btn
                                    color="red"
                                    @click="deleteAndRefresh(rfidTag.uid)"
                                >
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

<style>

.container {
    width: 100%;
}

th {
    margin-left: 0;
}

</style>