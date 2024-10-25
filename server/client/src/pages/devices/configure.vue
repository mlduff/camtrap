<script lang="ts" setup>
import { configure } from '@/api/configure-api';

// https://stackoverflow.com/questions/41024296/how-to-show-my-ip-address-on-flask
// Could default the server_address field

const ssid = ref<string>("");
const password = ref<string>("");
const serverAddress = ref<string>("");

async function submit() {
    await configure(
        ssid.value,
        password.value,
        serverAddress.value
    );
}

</script>

<template>

    <v-card>
        <v-card-title>
            Configure Device
        </v-card-title>
        <v-card-text>
            <p>
                Configure a device so it can connect to the server. Before submitting the form, ensure you are on the device network (consult packaging for details).
            </p>
            <v-form>
                <v-text-field
                    label="SSID (Network Name)"
                    v-model="ssid"
                />
                <v-text-field
                    label="Password"
                    v-model="password"
                />
                <v-text-field
                    label="Server Address"
                    v-model="serverAddress"
                />
            </v-form>
        </v-card-text>
        <v-card-actions>
            <v-btn
                @click="submit"
                color="primary"
            >
                Submit
            </v-btn>
        </v-card-actions>
    </v-card>

</template>