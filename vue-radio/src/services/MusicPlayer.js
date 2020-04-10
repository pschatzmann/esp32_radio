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
    
    setSource(selected){
        // stop any playing music
        this.stop();
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
        return this.source.play(url);
    }

    async stop() {
        return this.source.stop();
    }

    async getInfo() {
        return this.source.getInfo();
    }

}