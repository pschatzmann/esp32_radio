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
    publicPath: process.env.BASE_URL,
  },
  mutations: {
    setCountries(state, countries) {
        state.countries = countries;
    },

    setGenres(state, genres) {
      state.genres = genres;
    },

    setHome(state, homeCountry) {
    state.homeCountry = homeCountry;
    },

    setTitle(state, title) {
    state.title = title;
    }

  },
  actions: {

    setupGenres(context){
      if (context.state.genres.length==0) {
        const ws = new WebService()
        const publicPath = process.env.BASE_URL
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
                const publicPath = process.env.BASE_URL
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
            home.homeCountryName = result.data.country_name
            home.homeCountryPath = '/home/'+result.data.country_code.toLowerCase()
            context.commit('setHome', home);

        }).catch(error => {
            console.error(error)
        })
      }
    },

    setupTitle(context){
      const ws = new WebService()
      ws.getInfo().then(result => {
        context.commit('setTitle', 'ESP32 Radio Player');
        console.log(result)
      });
    }

  },
  modules: {
  }
})
