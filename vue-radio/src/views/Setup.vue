<template>
    <v-container fluid>
        <v-layout justify-space-around fill-height>
            <v-flex xs11>
                <v-card hover>
                    <v-card-title>
                        <h2>ESP32 Setup</h2>
                    </v-card-title>
                    <v-card-text >
                        <v-text-field label="Available Heap" readonly=true v-model="ws.heap" />
                        <v-text-field label="SSID" readonly=true v-model="ws.ssid" />
                        <v-text-field label="Bluetooth Name" readonly=true v-model="ws.bluetooth_name" />
                        <v-text-field label="Music Player" readonly=true :value="$store.state.musicPlayer.getName()" /> 
                        <v-switch label="Streaming" @change="changeStreaming()" :error-messages="errors.streaming"  v-model="ws.streaming" />
                        <v-switch label="Bluetooth" @change="changeBT()"  :error-messages="errors.bluetooth" v-model="ws.bluetooth" />
                    </v-card-text>
                </v-card>
            </v-flex>

        </v-layout>
    </v-container>
</template>

<script>
import WebService from '@/services/WebService'

export default {
    
        data: () => ({      
            ws: {       
                heap: null,
                ssid: 'not defined',
                streaming: false,
                bluetooth: false,
                bluetooth_name: 'not defined'
            },
            errors: {
                streaming: null,
                bluetooth: null,
            },

        }),

        methods: {
            changeStreaming() {
                new WebService().postStreaming(this.ws.streaming ).then(result => {
                    console.log(result);
                    this.ws = result.data
                    this.errors.streaming = ""
                    // when we are streaming we use the ESP player implementation
                    this.$store.state.musicPlayer.setSourceESP(this.ws.streaming)
                }).catch(error => {
                    this.ws.streaming = !this.ws.streaming;
                    this.$store.state.musicPlayer.setSourceESP(this.ws.streaming)
                    this.errors.streaming = "Streaming Service failed"
                    console.error(error);
                })
            },
            
            changeBT() {
                this.$store.state.musicPlayer.setSourceESP(false)
                new WebService().postBluetooth(this.ws.bluetooth ).then(result => {
                    console.log(result);
                    this.ws = result.data
                    this.errors.bluetooth = ""
                }).catch(error => {
                    this.ws.bluetooth = !this.ws.bluetooth;
                    console.error(error);
                    this.errors.bluetooth = "Bluetooth Service failed"
                })
            },
            
        },

        mounted() {
            console.log("Info mounted");
            this.$store.commit('setLoading', true);
            new WebService().getInfo().then(result => {
                console.log(result);
                this.ws = result.data
                this.$store.commit('setLoading', false);

            }).catch(error => {
                this.$store.commit('setLoading', false);
                console.error(error);
            })
        },
    }
</script>

