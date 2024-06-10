<template>
  <div>
    <input v-model="inputStr" placeholder="输入" @keyup.enter="callBackend">
    <p v-if="backendRes">{{ backendRes[1]["name"] }} </p>
  </div>
</template>

<script setup>
import axios from 'axios'
import { ref } from 'vue'

const inputStr = ref("")
const backendRes = ref("")

const callBackend = () => {
  axios
    .get('http://localhost:8080/api/ShowAllData')
    .then(response => {
      backendRes.value = response.data
      console.log(response)
    })
    .catch(error => {
      console.error(error)
    })
}
</script>

<style scoped></style>
