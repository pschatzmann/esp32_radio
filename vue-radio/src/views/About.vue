<!--
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
-->

<template>
    <v-container fluid>
        <v-card>
            <v-container fluid>
            I wanted to have a nice looking Radio Player that is working together with an <a href="https://en.wikipedia.org/wiki/ESP32" target="_blank" >ESP32 Micro Controller</a>.<p/>
            Here is the result: The GUI was written with Vue.js and I am using <a href="https://github.com/segler-alex/radiobrowser-api-rust" target="_blank" >radiobrowser-api-rust</a>
            to find the Radio Stations - so many thanks to Alex Segler for providing this project.<p/>
            The  Micro Controller is managed by a Webservice and can provide two output modes: you can stream the Radios direcly or
            you can activate Bluetooth and stream the Radios from your GUI device via Bluetooth. 
            <p/>
            Of cause you can also enjoy this player without an ESP32...
            <p/>
            <a href="https://pschatzmann.ch" target="_blank" >Phil Schatzmann</a>
            </v-container>
        </v-card>
    </v-container>
</template>

<script>
export default {
    data: () => ({
    }),
    
    mounted() {
        this.$store.commit('setLoading', false);
    }

    
}
