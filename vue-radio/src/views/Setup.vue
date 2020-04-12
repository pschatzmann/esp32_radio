<template>
    <v-container fluid>
        <v-layout justify-space-around fill-height>
            <v-flex xs11>
                <v-card hover>
                    <v-card-title>
                        <h2>ESP32 Setup</h2>
                    </v-card-title>

                    <v-text-field label="Available Heap" readonly=true v-model="ws.heap" />
                    <v-text-field label="SSID" readonly=true v-model="ws.ssid" />
                    <v-text-field label="Bluetooth Name" readonly=true v-model="ws.bluetooth_name" />
                    <v-switch label="Streaming" readonly=true v-model="ws.streaming" />
                    <v-switch label="Bluetooth" readonly=true v-model="ws.bluetooth" />


                </v-card>
            </v-flex>

        </v-layout>
    </v-container>
</template>

<script>
import WebService from "@/services/WebService"
export default {
    
        data: () => ({      
            ws: {       
                heap: null,
                ssid: 'not defined',
                streaming: false,
                bluetooth: false,
                bluetooth_name: 'not defined'
            },
            iswebserviceok: true
        }),

        mounted() {
            console.log("Info mounted");
            const ws = new WebService();
            ws.getInfo().then(result => {
                console.log(result);
                this.ws = result.data
            }).catch(error => {
                console.error(error);
            })
        }
    }
</script>
