<template>
  <div>
    <input v-model="inputStr" placeholder="输入" @keyup.enter="callBackend">
    <p v-if="backendRes">{{ backendRes }} </p>
  </div>
</template>

<script setup>
import axios from 'axios'
import { ref } from 'vue'

const inputStr = ref("input")
const backendRes = ref("output")

const callBackend = () => {
  axios
    .post('http://localhost:8080/api/uppercase', inputStr.value)
    .then(response => {
      backendRes.value = response.data
    })
    .catch(error => {
      console.error(error)
    })
}
</script>

<style scoped></style>
