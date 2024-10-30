<template>
    <v-app>
        <v-layout class="rounded rounded-md">
            <v-app-bar title="FuzzTrap">
                <div v-if="appStore.loggedIn" class="login-status">
                    Logged in as {{ appStore.user?.username }}
                </div>
            </v-app-bar>

            <v-navigation-drawer>
                <v-list>
                    <v-list-item title="Devices" to="/devices"></v-list-item>
                    <v-list-item title="Alarms" to="/alarms"></v-list-item>
                    <v-list-item title="RFID Tags" to="/rfids"></v-list-item>
                </v-list>
            </v-navigation-drawer>

            <v-main class="d-flex align-start justify-start">
                <div class="width-100">
                    <Suspense>
                        <div class="container">
                            <router-view />
                        </div>
                    </Suspense>
                </div>
            </v-main>
        </v-layout>
    </v-app>
</template>

<script lang="ts" setup>
import { useAppStore } from '@/stores/app';

const appStore = useAppStore();
</script>

<style>

.width-100 {
    width: 100%;
}

.container {
    padding: 16px;
    min-height: 300px;
}

.login-status {
    padding-right: 1em;
}

</style>
