<template>
  <div>
    <Header />

    <el-main>
      <el-row :gutter='20'>

        <el-col :span="18">

          <Transition name="card-fade">

            <!-- 遍历json所有数据组 -->
            <el-space wrap :size="20">

              <div v-for="(innerArray, index) in backendRes" :key="index">

                <!-- 遍历数据组内的数据 -->
                <el-card v-if="backendRes">

                  <TransitionGroup name="slide" tag="div" appear>
                    <div v-for="(array, idx) in innerArray" :key="idx">
                      <!-- 遍历数据数组中的每个元素 -->
                      {{ array[0] }} : {{ ifNumber(array[1]) }} {{ array[2] }} <!-- array[2]是可选的单位 -->
                    </div>
                  </TransitionGroup>

                </el-card>
              </div>

            </el-space>

          </Transition>

        </el-col>

        <el-col :span="6">

          <el-card class="UI">
            <el-form style="max-width:600px" :model="dict">
              <el-form-item label="名称">
                <el-input v-model="dict.name" />
              </el-form-item>

              <el-form-item label="类型">
                <el-select v-model="dict.type">
                  <el-option label="水果" value='0' />
                  <el-option label="蔬菜" value='1' />
                  <el-option label="肉" value='2' />
                  <el-option label="零食" value='3' />
                  <el-option label="饮料" value='4' />
                  <el-option label="药品" value='5' />
                  <el-option label="办公用品" value='6' />
                  <el-option label="日用品" value='7' />
                  <el-option label="电子产品" value='8' />
                </el-select>
              </el-form-item>



              <el-form-item>
                <el-button type="primary" plain @click="callBackend">查看全部数据</el-button>
              </el-form-item>

            </el-form>
          </el-card>

        </el-col>

      </el-row>
    </el-main>
  </div>
</template>

<script setup>
import { Cursor } from './api/Cursor/MouseCursor'
import axios from 'axios'
import { ref, reactive } from 'vue'
import Header from './components/Header.vue'

new Cursor({ 'input': 'md-editor-catalog-link' })


const ifNumber = (a) => { // 设置小数点
  if (typeof a === 'number') return parseFloat(Number(a)).toFixed(2)
  else return a
}

const backendRes = ref("")

const callBackend = () => {
  axios
    .get('http://localhost:8080/api/ShowAllData')
    .then(response => {
      backendRes.value = response.data
      console.log(response.data)
    })
    .catch(error => {
      console.error(error)
    })
}

const dict = reactive({
  name: "",
  type: 0,
  price: 0,
  priceUnit: "",
  stock: 0,
  stockUnit: "",
  flavor: 0,
  power: 0,
  dose: 0,
  detail: "",
})
</script>

<style scoped></style>
