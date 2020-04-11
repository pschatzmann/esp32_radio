import axios from 'axios'

export default class MusicPlayerESP32 {
    constructor(){
        MusicPlayerESP32.isPlaying = false;
    }

    getName() {
        return "Streaming on ESP32"
    }

    async setup() {
    }

    async play(url){
        MusicPlayerESP32.isPlaying = false;
        return await axios.post("/service/play", {"url": url})
    }

    async stop() {
        MusicPlayerESP32.isPlaying = false;
        return await axios.post("/service/stop");
    }

    async getInfo() {
        return await axios.get("/service/status");
    }

    isPlaying(){
        return MusicPlayerESP32.isPlaying;
    }


}
