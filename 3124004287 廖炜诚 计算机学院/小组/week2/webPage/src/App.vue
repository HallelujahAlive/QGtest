<template>
  <div id="app">
<!--    我在这里定义了一个类：module,意思就是模块，代表一整个登录或者注册框，通过定义类，方便在CSS中定义.module的样式（外观）-->
    <div class="module">
<!--      在这里我有定义了一个类：头部，也就是登录/注册框顶部的按钮，可以切换登录或者注册模式-->
      <div class="header">
<!--        这里我想要实现用户一点击头部的登录按钮，登录字体的底色和底部边框都会变成淡蓝色，这种样式是参考飞书的按钮，我觉得比较简约，也很好看-->
<!--        但是这里我实在不知道CSS样式应该怎么设计代码应该怎么写，所以我就求助了万能的ai，让他按照我的设计想法生成了CSS代码-->

        <!--这里我用到了':class="{类名：表达式}"'，如果表达式的值为false，那么该类会被删除，也就是说只要我没有点击登录模式，那么<style>激活(active)类就会被删除，登录按钮就不会变色，让页面更好看-->
        <button @click="displayLogin = true" :class="{ active: displayLogin }">登录</button>
        <button @click="displayLogin = false" :class="{ active: !displayLogin }">注册</button>
      </div>
<!--      我为输入文本框定义了类名：form-module，也是方便CSS定义样式-->
      <div class="form-module">
        <form v-if="displayLogin" @submit.prevent="successfulLogin">
          <input v-model="loginEmail" type="email" placeholder="邮箱" required>
          <input v-model="loginPassword" type="password" placeholder="密码" required>
          <button type="submit">登录</button>
          <div v-if="!isLoginSuccessful" class="error">邮箱和密码为必填项</div>
        </form>
        <form v-else @submit.prevent="successfulRegister">
          <input v-model="registerEmail" type="email" placeholder="邮箱" required>
          <input v-model="registerPhone" type="tel" placeholder="手机号" required>
          <input v-model="registerPassword" type="password" placeholder="密码" required>
          <input v-model="confirmPassword" type="password" placeholder="确认密码" required>
          <button type="submit">注册</button>
          <div v-if="!isRegisterSuccessful" class="error">所有字段均为必填项，且密码需一致</div>
        </form>
      </div>
    </div>
  </div>
</template>

<script>
export default {
  data () {
    return {
      displayLogin:true,
      loginEmail:'',
      loginPassword:'',
      registerEmail:'',
      registerPhoneNumber:'',
      registerPassword:'',
      confirmPassword:'',
      isLoginSuccessful:true,
      isRegisterSuccessful:true,
    };
  },
  methods:{
    successfulLogin(){
      if (this.loginEmail && this.loginPassword){
        this.isLoginSuccessful = true;
        console.log('登录成功');
      } else {
        this.isLoginSuccessful = false;
      }
    },
    successfulRegister(){
      if (this.registerEmail && this.registerPhoneNumber && this.registerPassword && this.confirmPassword
      && this.registerPassword === this.confirmPassword){
        this.isRegisterSuccessful = true;
        console.log('注册成功');
      } else {
        this.isRegisterSuccessful = false;
      }
    }
  }
};
</script>
<style scoped>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #2c3e50;
  margin-top: 60px;
  font-size: 18px;
  background-image: url("E:\\2025Vue\\vue-demo\\test\\src\\assets\\油菜花田2.JPG");
  background-size: cover;
  background-position: center;
  background-repeat: no-repeat;
  min-height: 100vh;
}
body {
  margin: 0;
  padding: 0;
  background-image: url("E:\\2025Vue\\vue-demo\\test\\src\\assets\\油菜花田2.JPG");
  background-size: cover;
  background-position: center;
  background-repeat: no-repeat;
  min-height: 100vh;
}

.module {
  width: 300px;
  margin: 0 auto;
  border: 1px solid #ccc;
  border-radius: 5px;
  padding: 30px;
  box-shadow: 0 0 10px rgba(0, 0, 0, 0.1);
  background-color: rgba(255, 255, 255, 0.8);
  position:absolute;
  top: 50%;
  left: 50%;
  transform: translate(-50%, -50%);
}

.header {
  display: flex;
  justify-content: space-around;
  margin-bottom: 20px;
}

.header button {
  background: none;
  border: none;
  cursor: pointer;
  font-size: 16px;
  padding: 5px 10px;
}

.header button.active {
  color: #007BFF;
  border-bottom: 2px solid #007BFF;
  background-color: transparent;
}

.form-module input {
    width: 98%; 
    padding: 10px;
    margin-bottom: 15px;
    border: 1px solid #ccc;
    border-radius: 3px;
    box-sizing: border-box;
}

.form-module button {
  width: 100%;
  padding: 10px;
  background-color: #2c3e50;
  color: white;
  border: none;
  border-radius: 3px;
  cursor: pointer;
}

.error {
  color: red;
  margin-top: 10px;
}
</style>