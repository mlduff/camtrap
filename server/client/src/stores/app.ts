// Utilities
import User from '@/types/user';
import { defineStore } from 'pinia'

export const useAppStore = defineStore('app', {
    state: () => {
        const user = ref<User |null>(null);

        return {
            user
        };
    },
    getters: {
        loggedIn(state) {
            return state.user != null;
        },
    },
    persist: {
        storage: localStorage
    }
})
