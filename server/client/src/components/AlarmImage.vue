<script setup lang="ts">

defineProps({
    filename: String
});

</script>

<template>
    <img :src="`/images/${filename}`"/>
</template>