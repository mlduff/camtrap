<script setup lang="ts">
import { resetDeviceNetwork, setDeviceConfigureMode, setDeviceEnabled } from '@/api/device-api';
import { Device } from '@/types/device';

const props = defineProps({
    device:  {
        type: Object as PropType<Device>,
        required: true,
    },
});

const emit = defineEmits(["update"]);

async function setEnabled(enabled: boolean) {
    await setDeviceEnabled(props.device.id, enabled);
    emit("update");
}

async function setConfigureMode(configureMode: boolean) {
    await setDeviceConfigureMode(props.device.id, configureMode);
    emit("update");
}

async function resetNetwork() {
    await resetDeviceNetwork(props.device.id);
}

</script>

<template>
    
    <v-card>
        <v-card-title>{{ device.name }} (#{{ device.id }})</v-card-title>
        <v-card-text>
            <div>
                IP Address: {{ device.ip_address}}
            </div>
        </v-card-text>
        <v-card-actions>
            <v-btn
                v-if="device.enabled"
                @click="setEnabled(false)"
                color="red"
            >
                Disable Device
            </v-btn>
            <v-btn
                v-else
                @click="setEnabled(true)"
                color="success"
            >
                Enable Device
            </v-btn>

            <v-btn
                v-if="device.configure_mode"
                @click="setConfigureMode(false)"
                color="red"
            >
                Disable Configure Mode
            </v-btn>
            <v-btn
                v-else
                @click="setConfigureMode(true)"
                color="success"
            >
                Enable Configure Mode
            </v-btn>

            <v-btn
                @click="resetNetwork"
                color="orange"
            >
                Reset Network
            </v-btn>
        </v-card-actions>
    </v-card>

</template>