/**
 * Music player API implementation which controls the ESP32 with the help of Webservice calls
 */
import WebService from "@/services/WebService"

export default class MusicPlayerESP32 {
    constructor(){
        MusicPlayerESP32.isPlaying = false;
        this.service = new WebService()
    }

    getName() {
        return "Streaming on ESP32"
    }

    async play(url){
        MusicPlayerESP32.isPlaying = true;
        var response = await this.service.postStreaming(MusicPlayerESP32.isPlaying, url)
        return response.status == 200 ? {url : url, playing:true} :{url : url, playing:false} 
    }

    async stop() {
        MusicPlayerESP32.isPlaying = false;
        return await this.service.postStreaming(MusicPlayerESP32.isPlaying, null)
    }

    async getInfo() {
        return await this.service.getRadioInfo();
    }

    isPlaying(){
        return MusicPlayerESP32.isPlaying;
    }


}
