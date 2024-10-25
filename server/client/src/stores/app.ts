// Utilities
import { defineStore } from 'pinia'

export const useAppStore = defineStore('app', {
    state: () => {
        const loggedIn = ref<boolean>(false);

        return {
            loggedIn,
        };
    },
})
