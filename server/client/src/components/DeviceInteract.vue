<script setup lang="ts">
import { takePicture } from '@/api/device-api';
import AlarmImage from './AlarmImage.vue';
import { Device } from '@/types/device';

const props = defineProps({
    device:  {
        type: Object as PropType<Device>,
        required: true,
    },
});

const pictureFilename = ref<string | null>(null);

async function takeAndDisplayPicture() {
    const filename = await takePicture(props.device.id);
    pictureFilename.value = filename;
}

</script>

<template>
    
    <v-card>
        <v-card-title>Picture</v-card-title>
        <v-card-text>
            <div v-if="pictureFilename != null">
                <AlarmImage :filename="pictureFilename" class="image"/>
            </div>
            <div v-else="" class="image no-image" >
                No picture to display
            </div>
        </v-card-text>
        <v-card-actions>
            <v-btn
                color="primary"
                @click="takeAndDisplayPicture"
            >
                Take Picture 
            </v-btn>
        </v-card-actions>
    </v-card>

</template>

<style scoped>

.image {
    max-width: 512px;
}

.no-image {
    display: flex;
    justify-content: center;
    align-items: center;

    width: 512px;
    height: 384px;
}

</style>