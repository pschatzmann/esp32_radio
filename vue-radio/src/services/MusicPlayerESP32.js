import axios from 'axios'

export default class MusicPlayerESP32 {
    constructor(){
    }

    getName() {
        return "Streaming on ESP32"
    }

    async setup() {
    }

    async play(url){
        return await axios.post("/service/play", {"url": url})
    }

    async stop() {
        return await axios.post("/service/stop");
    }

    async getInfo() {
        return await axios.get("/service/status");
    }


}
