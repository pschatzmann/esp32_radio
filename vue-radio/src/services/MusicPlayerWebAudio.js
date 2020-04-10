

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

    async play(url){
        this.stop();
        MusicPlayer.audio = new Audio(url);
        MusicPlayer.audio.play();
        MusicPlayer.isPlaying = true
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


}
