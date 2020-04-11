/* eslint-disable */
import axios from 'axios'


export default class WebService {

    // We retrieve the info from the ESP32
    async getInfo() {
        console.log("getInfo")
        return await axios.get("/service/info")
    }

    async getGenres(publicPath) {
        console.log("getGenres")
        return await axios.get(publicPath+"genres/genres.json")
    }

    async getCountryCodes() {
        return await axios.get( "https://de1.api.radio-browser.info/json/countrycodes?hidebroken=true")
    }

    async getCountry() {
        return await axios.get( "https://raw.githubusercontent.com/mledoze/countries/master/dist/countries.json")
    }
    
    async getUserCountry() {
        return await axios.get("https://api.ipdata.co/?api-key=test")
    }

    async getRadios(field, value) {
        var url = "https://de1.api.radio-browser.info/json/stations/search?"+field+"="+value+"&codec=MP3"
        return await axios.get(url);
    }

    async check(url, row){
        var ok = await axios.options(url)
        if (ok.status=200)
            return row
        throw new Error(ok.statusText)

    }
    

}
