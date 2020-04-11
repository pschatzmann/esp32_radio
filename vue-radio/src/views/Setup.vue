<template>
    <v-container fluid>
        <v-layout justify-space-around fill-height>
            <v-flex xs11>
                <v-card hover>
                    <v-card-title>
                        <h2>ESP32 Setup</h2>
                    </v-card-title>

                    <v-text-field label="Available Heap" readonly=true v-model="heap" />
                    <v-text-field label="SSID" readonly=true v-model="ssid" />

                </v-card>
            </v-flex>

        </v-layout>
    </v-container>
</template>

<script>
import WebService from "@/services/WebService"
export default {
    
        data: () => ({             
            heap: undefined,
            ssid: 'not defined',
            iswebserviceok: true
        }),

        mounted() {
            console.log("Info mounted");
            const ws = new WebService();
            ws.getInfo().then(result => {
                console.log(result);
                this.heap = result.data.heap;
                this.ssid = result.data.ssid;
            }).catch(error => {
                console.error(error);
            })
        }
    }
</script>
