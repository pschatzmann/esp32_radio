import Vue from 'vue'
import Vuex from 'vuex'
import WebService from "@/services/WebService"
import MusicPlayerESP32 from "@/services/MusicPlayerESP32"
import MusicPlayerWebAudio from "@/services/MusicPlayerWebAudio"

Vue.use(Vuex)

export default new Vuex.Store({
  state: {
    loading: true,
    countries: [],
    genres: [],
    homeCountry: null,
    title: "Radio Player",
    esp32: false,
    publicPath: process.env.BASE_URL,
    drawer: null,
    activeRadio: {id:null, active:false, url:null, error:false, name:''},
    radios: {},
    musicPlayer: null,
    supportedMusicPlayers: [new MusicPlayerWebAudio(), new MusicPlayerESP32()],
    blacklist: [],
    resourceAddress: "https://pschatzmann.github.io"

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
    },

    setMusicPlayer(state, idx) {
      if (state.musicPlayer) {
        state.musicPlayer.stop()
      }
      state.musicPlayer = state.supportedMusicPlayers[idx];
    },

    setBlacklist(state,blacklist) {
      state.blacklist = blacklist;
    },

    setLoading(state,loading) {
      state.loading = loading;
    },

  },
  actions: {

    setupGenres(context){
      if (context.state.genres.length==0) {
        context.commit('setLoading', true);

        const publicPath = context.state.publicPath;
        const ws = new WebService()
        ws.getGenres(publicPath).then(result => {
            result.data.forEach(c => {c.imageUrl = publicPath+c.imageUrl;});
            context.commit('setGenres', result.data);
            context.commit('setLoading', false);
          }, error => {
            console.error(error);
            context.commit('setLoading', false);
          });
      }
    },

    setupCountries(context){  
        if (context.state.countries.length==0){
          context.commit('setLoading', true);

          const ws = new WebService()
          const publicPath = context.state.publicPath;
          ws.getCountry(publicPath).then(result => {
              var countryNames = {}
              for (var rec of result.data){
                  countryNames[rec['alpha-2'].toLowerCase()] = rec.name;
              }
              ws.getCountryCodes().then(result1 => {
                var countryData = result1.data
                for (var c of countryData ){
                    c.iconUrl = publicPath+"flags/"+c.name.toLowerCase()+".png"
                    c.countryCode = c.name
                    c.counrtyName = countryNames[c.name.toLowerCase()]
                }
                context.commit('setCountries', countryData);
                context.commit('setLoading', false);

              }).catch(error => {
                console.error(error)
                context.commit('setLoading', false);
              })        
          }).catch(error => {
              console.error(error)
              context.commit('setLoading', false);
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
    },

    setupBlacklist(context){
      const publicPath = context.state.publicPath;
      const ws = new WebService()
      ws.getBlacklist(publicPath).then(result => {
          context.commit('setBlacklist', result.data);
      }, error => {
          console.error(error);
      });
    },

  },
  modules: {
  }
})
