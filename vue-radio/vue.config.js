module.exports = {
  "transpileDependencies": [
    "vuetify"
  ],
  publicPath: process.env.NODE_ENV === 'production'
  ? '/esp32_radio/vue-radio/dist/'
  : '/',
  crossorigin:"anonymous"

}