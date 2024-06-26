import { createApp } from 'vue'
import App from './App.vue'
import './css/style.css'
import './api/Cursor/MouseCursor.css'
import ElementPlus from 'element-plus'
import 'element-plus/dist/index.css'
import router from './router.js'


const app = createApp(App)

app.use(router)
app.use(ElementPlus)
app.mount('#app')
