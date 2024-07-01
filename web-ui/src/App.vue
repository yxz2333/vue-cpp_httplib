<template>
  <div>

    <Header />

    <el-main>

      <el-row :gutter='20'>

        <el-col :span="18">

          <!-- 遍历json所有数据组 -->
          <TransitionGroup name="card-fade">
            <el-space wrap style="margin:0 10px 10px 0" v-for="(innerArray, index) in backendRes" :key="index">

              <!-- 遍历数据组内的数据 -->

              <el-card v-if="backendRes" @click="deleteOption(innerArray[0][1])"
                :class="{ delete01: deleting_set.has(innerArray[0][1]) }">

                <TransitionGroup name="slide" tag="div" appear>
                  <div v-for="(array, idx) in innerArray" :key="idx">

                    <!-- 遍历数据数组中的每个元素 -->
                    <div v-if="array[0] != 'id' && array[1] != ''">
                      {{ array[0] }} : {{ ifNumber(array[1]) }} {{ array[2] }} <!-- array[2]是可选的单位 -->
                    </div>

                  </div>
                </TransitionGroup>

              </el-card>

            </el-space>
          </TransitionGroup>

        </el-col>

        <el-col :span="6">
          <Transition name="card-fade">
            <el-alert v-if="is_import_warning" title="错误" type="error" effect="dark" description="请输入全部必须的数据" show-icon
              style="position:fixed; z-index:100;max-width:400px;" @click="is_import_warning = !is_import_warning"
              :closable="false" />
          </Transition>


          <el-card class="UI">

            <el-form style="max-width:400px; margin: 10px" :model="dict">

              <el-form-item label="名称" prop='name' :rules="[{ required: true, message: '请输入名称' }]">
                <el-input v-model="dict.name" placeholder="输入名称" />
              </el-form-item>

              <el-form-item label="价格" prop='price' :rules="[{ required: true, message: '请输入价格单位' }]">
                <el-tooltip content="输入价格（如：100，即 100元 / { 价格单位 }）" placement="bottom">
                  <el-input-number v-model="dict.price" />
                </el-tooltip>
              </el-form-item>
              <el-form-item label="价格单位" prop='priceUnit' :rules="[{ required: true, message: '请输入价格单位' }]">
                <el-input v-model="dict.priceUnit" placeholder="输入价格单位（如：元/个）" />
              </el-form-item>

              <el-form-item label="存货量" prop='stock' :rules="[{ required: true, message: '请输入存货量' }]">
                <el-tooltip content="输入存货量（如：100，即 100 { 存货量单位 }）" placement="bottom">
                  <el-input-number v-model="dict.stock" />
                </el-tooltip>
              </el-form-item>
              <el-form-item label="存货量单位" prop='stockUnit' :rules="[{ required: true, message: '请输入存货量单位' }]">
                <el-input v-model="dict.stockUnit" placeholder="输入存货量单位（如：个）" />
              </el-form-item>

              <el-form-item label="类型" prop='type' :rules="[{ required: true, message: '请选择类型' }]">
                <el-select v-model="dict.type" placeholder="选择物品类型">
                  <el-option label="水果" :value='1' />
                  <el-option label="蔬菜" :value='2' />
                  <el-option label="肉" :value='3' />
                  <el-option label="零食" :value='4' />
                  <el-option label="饮料" :value='5' />
                  <el-option label="药品" :value='6' />
                  <el-option label="办公用品" :value='7' />
                  <el-option label="日用品" :value='8' />
                  <el-option label="电子产品" :value='9' />
                </el-select>
              </el-form-item>

              <el-form-item label="味道" v-if="dict.type >= 1 && dict.type <= 5" prop='type'
                :rules="[{ required: true, message: '请选择食物味道' }]">
                <el-select v-model="dict.flavor" placeholder="选择食物味道">
                  <el-option label="酸" :value='1' />
                  <el-option label="甜" :value='2' />
                  <el-option label="苦" :value='3' />
                  <el-option label="辣" :value='4' />
                  <el-option label="咸" :value='5' />
                </el-select>
              </el-form-item>

              <el-form-item label="用量" v-if="dict.type === 6" prop='dose'
                :rules="[{ required: true, message: '请输入药品用量' }]">
                <el-tooltip content="输入用量（如：2，即一天两次）" placement="bottom">
                  <el-input-number v-model="dict.dose" />
                </el-tooltip>
              </el-form-item>

              <el-form-item label="功率" v-if="dict.type === 9" prop='power'
                :rules="[{ required: true, message: '请输入功率' }]">
                <el-tooltip content="输入功率（如：100，即100W）" placement="bottom">
                  <el-input-number v-model="dict.power" />
                </el-tooltip>
              </el-form-item>

              <el-form-item label="商品描述">
                <el-input v-model="dict.detail" type="textarea" placeholder="输入描述" />
              </el-form-item>

              <el-form-item>
                <el-button type="success" :icon="Check" @click="importDict">导入</el-button>
                <el-button type="info" :icon="Setting" @click="clearDict">重置</el-button>
              </el-form-item>

              <el-divider>
                🤗
              </el-divider>

              <el-form-item label="查询数据：">
                <el-select v-model="query_type" placeholder="选择查询数据的类别">
                  <el-option label="全部" :value='-1' />
                  <el-option label="食品" :value='1' />
                  <el-option label="药品" :value='2' />
                  <el-option label="日用品" :value='3' />
                  <el-option label="电子产品" :value='4' />
                </el-select>
              </el-form-item>

              <el-form-item label="批量删除：">
                <el-button type="danger" :icon="Delete" v-if="!is_deleting" @click="is_deleting = !is_deleting" round />
                <el-button type="danger" v-if="is_deleting" @click="is_deleting = !is_deleting; confirmDelete()"
                  round>确认</el-button>
                <el-button type="primary" v-if="is_deleting" @click="is_deleting = !is_deleting" round>取消</el-button>
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
import { ref, reactive, watch } from 'vue'
import Header from './components/Header.vue'

import {
  Check,
  Delete,
  Setting,
} from '@element-plus/icons-vue'

new Cursor()

const ifNumber = (a) => { // 设置小数点
  if (typeof a === 'number') return parseFloat(Number(a)).toFixed(2)
  else return a
}


// 前端发送的数据
const dict = reactive({
  name: '',
  type: '',
  price: 0,
  priceUnit: '',
  stock: 0,
  stockUnit: '',
  flavor: '',
  power: '',
  dose: '',
  detail: '',
})

// 后端返回的数据
const backendRes = ref()


///// 状态变量 /////
const is_deleting = ref(false)               // 是否是正在删除的状态
const deleting_set = reactive(new Set())     // 将要删除的变量 

const is_import_warning = ref(false)
const query_type = ref('')                   // 显示的数据类型
///////////////////


///// 监听变量 /////
watch(query_type, () => {
  queryData()
})
watch(is_deleting, (pre, old) => {
  if (pre == false)
    deleting_set.clear()
})
///////////////////


const queryData = () => { // 从后端查询数据
  axios
    .post('http://localhost:8080/api/ShowData', query_type)
    .then(response => {
      backendRes.value = response.data
      console.log(backendRes.value)
    })
    .catch(error => {
      console.error(error)
    })
}



const importDict = () => { // 导入数据到后端
  if (dict.name == '' || dict.type == '' || dict.price == '' || dict.priceUnit == '' || dict.stock == '' || dict.stockUnit == '') {
    is_import_warning.value = true
    return
  }
  if (dict.type >= 1 && dict.type <= 5) {
    if (dict.flavor == '') {
      is_import_warning.value = true
      return
    }
  }
  else if (dict.type == 6) {
    if (dict.dose == '') {
      is_import_warning.value = true
      return
    }
  }
  else if (dict.type == 9) {
    if (dict.power == '') {
      is_import_warning.value = true
      return
    }
  }

  axios
    .post('http://localhost:8080/api/ImportData', dict)
    .then(() => {
      queryData()
    })
    .catch(error => {
      console.error(error)
    })

}

const clearDict = () => { // 重置当前输入
  for (let key in dict) {
    dict[key] = ''
    if (key == 'price' || key == 'stock') {
      dict[key] = 0
    }
  }
}

const deleteOption = (id) => {
  if (is_deleting.value) {
    if (!deleting_set.has(id))
      deleting_set.add(id)
    else
      deleting_set.delete(id)
  }
}

const confirmDelete = () => {
  const d_tmp = { // 要删除的数的id，传给后端
    'id': []
  }
  for (let i of deleting_set) {
    d_tmp['id'].push(i);
  }
  axios.post('http://localhost:8080/api/DeleteData', d_tmp)
    .then(() => {
      queryData()
    }).catch(error => {
      console.error(error)
    })
}
</script>

<style scoped>
.delete01 {
  border: 5px dashed red;
}
</style>
