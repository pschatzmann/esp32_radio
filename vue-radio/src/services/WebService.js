/**
    Copyright 2020 Phil Schatzmann

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

import axios from 'axios'

export default class WebService {


    async getGenres(publicPath) {
        console.log("getGenres")
        return await axios.get(publicPath+"data/genres.json")
    }

    async getCountry(publicPath) {
        return await axios.get( publicPath+"data/countries.json")
    }

    async getBlacklist(publicPath) {
        return await axios.get( publicPath+"data/blacklist.json")
    }

    async getCountryCodes() {
        return await axios.get( "https://de1.api.radio-browser.info/json/countrycodes?hidebroken=true")
    }
    
    async getRadios(field, value) {
        var url = "https://de1.api.radio-browser.info/json/stations/search?"+field+"="+value+"&codec=MP3"
        return await axios.get(url);
    }

    async getUserCountry() {
        return await axios.get("https://api.ipdata.co/?api-key=62f04882eac5c1c2469a3dee1d5c98187ba19c0a189783d372e36122")
    }

    // We retrieve the info from the ESP32
    async getInfo() {
        console.log("getInfo")
        return await axios.get("/service/info")
    }
    
    async postBluetooth(active) {
        var action = active ? "start" : "stop"
        return await axios.post('/service/bluetooth/'+action)
    }

    async postStreaming(active, url) {
        var action = active ? "start" : "stop"
        return await axios.post('/service/streaming'+action, {'url': url})
    }

    async getRadioInfo() {
        return await axios.get("/service/status");
    }

}
