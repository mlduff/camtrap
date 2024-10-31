<script lang="ts" setup>
import { login } from '@/api/auth-api';
import { useAppStore } from '@/stores/app';

const appStore = useAppStore();
const router = useRouter();

const username = ref<string>("");
const password = ref<string>("");

async function submitLogin() {
    try {
        const user = await login(
            username.value,
            password.value,
        );

        appStore.user = user;
        router.push({ path: "/" });
    } catch {
        appStore.user = null;
    }
}

</script>

<template>
    <div class="container">
        <v-card>
            <v-card-title>
                Login
            </v-card-title>
            <v-card-text>
                <v-form>
                    <v-text-field
                        label="Username"
                        v-model="username"
                    />
                    <v-text-field
                        label="Password"
                        v-model="password"
                    />
                </v-form>
            </v-card-text>
            <v-card-actions>
                <v-btn
                    @click="submitLogin"
                    color="primary"
                >
                    Login
                </v-btn>
            </v-card-actions>
        </v-card>
    </div>
</template>

<style scoped>

.container {
    width: 50%;
}

</style>