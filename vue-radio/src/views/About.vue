<template>
    <v-container fluid>
        <v-card>
            <v-container fluid>
            I wanted to have a nice looking Radio Player that is working together with an ESP32 Micro Controller. <p/>
            Here is the result: The GUI was written with Vue.js. I am using <a href="https://github.com/segler-alex/radiobrowser-api-rust">radiobrowser-api-rust</a>
            to find the Radio Stations - so many thanks to Alex Segler for providing this project.<p/>
            The  Micro Controller is managed by a Webservice and can provide two output modes: you can stream the Radios direcly or
            you can activate Bluetooth and stream the Radios from your GUI device via Bluetooth. 
            <p/>
            Of cause you can also enjoy this player without an ESP32...
            </v-container>
        </v-card>
    </v-container>
</template>

<script>
export default {
    data: () => ({
    }),
    
}
