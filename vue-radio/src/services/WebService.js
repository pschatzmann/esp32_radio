/* eslint-disable */
import axios from 'axios'


export default class WebService {

    // We retrieve the info from the ESP32
    async getInfo() {
        console.log("getInfo")
        return await axios.get("/service/info")
    }

    // loads html from Wordpress
    async getWordpressPost() {
        return await axios.get( "https://pschatzmann.ch/wp-json/wp/v2/posts/1323")
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
    

}
