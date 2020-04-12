
/**
 * Music player API implementation which uses the Browsers own Audio object
 */
import axios from 'axios'

export default class MusicPlayer {
    constructor(){
        if (MusicPlayer.isPlaying ===undefined){
            MusicPlayer.audio = null;
            MusicPlayer.isPlaying = false
        }
    }

    getName() {
        return "Playing locally"
    }

    async setup() {
        return await axios.post("/service/bluetooth");
    }

    async play(url){
        this.stop();
        try {
            MusicPlayer.audio = new Audio(url);
            MusicPlayer.audio.play();
            MusicPlayer.isPlaying = true
        } catch(error){
            console.error(error)
        }
        return MusicPlayer.isPlaying
    }

    async stop() {
        if (MusicPlayer.audio!=null) {
            MusicPlayer.audio.pause();
            MusicPlayer.audio = null;
        }
        MusicPlayer.isPlaying = false
    }

    async getInfo() {
        return {'isPlaying': MusicPlayer.isPlaying};
    }

    isPlaying(){
        return MusicPlayer.isPlaying;
    }


}
