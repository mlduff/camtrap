<script setup lang="ts">
import { getDevice } from '@/api/device-api';
import type { Device } from '@/types/device';

const route = useRoute("/devices/[id]");
const id = Number(route.params.id);

const device = ref<Device>(await getDevice(id));

async function updateDevice() {
    device.value = await getDevice(id);
}

</script>

<template>
    <Device
        :device="device"
        class="mb-4"
        @update="updateDevice"
    />
    <DeviceInteract :device="device"/>
</template>