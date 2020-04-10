module.exports = {
  "transpileDependencies": [
    "vuetify"
  ],
  publicPath: process.env.NODE_ENV === 'production'
  ? '/esp32_vue_example/vue-demo/dist/'
  : '/',
  crossorigin:"anonymous"

}