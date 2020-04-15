/**
 * The music player provides API methods which forward the request to 
 * the corresponding selected music player implementation.
 * 
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

    async setup() {
        return this.source.setup()
    }

    isPlaying(){
        return this.source.isPlaying();
    }


}