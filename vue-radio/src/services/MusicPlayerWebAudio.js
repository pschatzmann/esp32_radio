export default class MusicPlayer {
    constructor(){
        this.audioCtx = new (window.AudioContext || window.webkitAudioContext);
        this.source = this.audioCtx.createBufferSource();
        this.isPlaying = false
    }

    getName() {
        return "Playing locally"
    }

    async play(url){
        var response = await window.fetch(url)
        var audioBuffer = await this.audioCtx.decodeAudioData(response.arrayBuffer)
        this.source.buffer = audioBuffer;
        this.source.connect(this.audioCtx.destination);
        this.source.start();
        this.isPlaying = true
    }

    async stop() {
        this.source.stop();
        this.isPlaying = false
    }

    async getInfo() {
        return {'isPlaying': this.isPlaying};
    }


}
