import axios from 'axios'

export default class MusicPlayerESP32 {
    constructor(){
    }

    getName() {
        return "Streaming on ESP32"
    }

    async play(url){
        return await axios.post("/service/sound/play?file="+url)
    }

    async stop() {
        return await axios.post("/service/sound/stop");
    }

    async getInfo() {
        return await axios.get("/service/sound/status");
    }


}
