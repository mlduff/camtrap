<template>
    <v-app>
        <v-layout class="rounded rounded-md">
            <v-app-bar title="FuzzTrap"></v-app-bar>

            <v-navigation-drawer>
                <v-list>
                    <v-list-item title="Devices" to="/devices"></v-list-item>
                    <v-list-item title="Alarms" to="/alarms"></v-list-item>
                    <v-list-item title="RFID Tags" to="/rfids"></v-list-item>
                </v-list>
            </v-navigation-drawer>

            <v-main class="d-flex align-start justify-start">
                <div>
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

</script>

<style>

.container {
    padding: 16px;
    min-height: 300px;
}

</style>
