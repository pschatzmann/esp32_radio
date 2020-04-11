import Vue from 'vue'
import Vuex from 'vuex'
import WebService from "@/services/WebService"

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    countries: [],
    genres: [],
    homeCountry: null,
    title: "Radio Player",
    esp32: false,
    publicPath: process.env.BASE_URL,
    drawer: null,
    activeRadio: {id:null, active:false, url:null},
    radios: {}
  },
  mutations: {
    setDrawer(state, drawer){
      state.drawer = drawer;
    },

    setCountries(state, countries) {
      state.countries = countries;
    },

    setGenres(state, genres) {
      state.genres = genres;
    },

    setHome(state, homeCountry) {
      state.homeCountry = homeCountry;
    },

    setActiveRadio(state, activeRadio) {
      state.activeRadio = activeRadio;
    },

    setRadios(state, upd) {
      state.radios[upd.id] = upd.value;
    },

    setESP32Title(state) {
      state.title = 'ESP32 Radio Player';
      state.esp32 = true;
    }

  },
  actions: {

    setupGenres(context){
      if (context.state.genres.length==0) {
        const ws = new WebService()
        const publicPath = context.state.publicPath;
        ws.getGenres(publicPath).then(result => {
            result.data.forEach(c => {c.imageUrl = publicPath+c.imageUrl;});
            context.commit('setGenres', result.data);
        }, error => {
            console.error(error);
        });
      }
    },

    setupCountries(context){  
        if (context.state.countries.length==0){
          const ws = new WebService()
          ws.getCountry().then(result => {
              var countryNames = {}
              for (var rec of result.data){
                  countryNames[rec.cca2.toLowerCase()] = rec.name.common;
              }
              ws.getCountryCodes().then(result1 => {
                var countryData = result1.data
                const publicPath = context.state.publicPath;
                for (var c of countryData ){
                    c.iconUrl = publicPath+"flags/"+c.name.toLowerCase()+".png"
                    c.countryCode = c.name
                    c.counrtyName = countryNames[c.name.toLowerCase()]
                }
                context.commit('setCountries', countryData);
              }).catch(error => {
                console.error(error)
              })        
          }).catch(error => {
              console.error(error)
          })
        }
    },

    setupHomeCountry(context){
      if (context.state.homeCountry == null){
        const ws = new WebService()
        ws.getUserCountry().then(result => {
            var home = {}
            const publicPath = context.state.publicPath;
            const countryCode = result.data.country_code.toLowerCase()
            home.homeCountryName = result.data.country_name
            home.homeCountryPath = '/home/'+countryCode
            home.iconUrl = publicPath+"flags/"+countryCode+".png"

            context.commit('setHome', home);

            ws.getRadios('countrycode', countryCode).then(result => {
                const radios = result.data
                const id = 'countrycode'+ countryCode
                context.commit('setRadios', {id:id, value:radios});

            }).catch(error => {
                console.error(error)
            })

        }).catch(error => {
            console.error(error)
        })
      }
    },

    setupTitle(context){
      const ws = new WebService()
      ws.getInfo().then(result => {
        context.commit('setESP32Title');
        console.log(result)
      });
    }

  },
  modules: {
  }
})
