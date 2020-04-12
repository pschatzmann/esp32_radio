/**
 * The music player provides API methods which forward the request to 
 * the corresponding selected music player implementation.
 */
import MusicPlayerESP32 from '@/services/MusicPlayerESP32'
import MusicPlayerWebAudio from '@/services/MusicPlayerWebAudio'


export default class MusicPlayer {
    constructor(){
        this.sourceESP = new MusicPlayerESP32();
        this.sourceWA = new MusicPlayerWebAudio();
        this.source = this.sourceWA;        
    }

    getSources() {
        return [this.sourceESP, this.sourceWA]
    }

    setSourceESP(isESP){
        if (isESP){
            this.setSource(this.sourceESP)
        } else {
            this.setSource(this.MusicPlayerWebAudio)
        }
    }
  
    setSource(selected){
        // stop any playing music
        this.stop();
        this.selected.setup();
        this.source = selected
    }

    getSource(){
        return this.source
    }

    getName() {
        return this.source.getName();
    }

    async play(url){
        this.stop();
        return await this.source.play(url);
    }

    async stop() {
        return await this.source.stop();
    }

    async getInfo() {
        return await this.source.getInfo();
    }

    isPlaying(){
        return this.source.isPlaying();
    }


}