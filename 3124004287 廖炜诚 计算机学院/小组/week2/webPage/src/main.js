import Vue from 'vue'
import App from './App.vue'
import router from './router'
import store from './store'

Vue.config.productionTip = false

new Vue({
  router,
  store,
  // 创建虚拟节点
  render: h => h(App)
  //调用mount函数，将虚拟节点渲染到页面上
}).$mount('#app')
