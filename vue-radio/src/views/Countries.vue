<template>
    <v-container fluid>
            <v-row>
                <v-col cols="20" sm="1" md="3"  v-for="item in this.countryData" :key="item.stationuuid" >
                    <v-hover  v-slot:default="{ hover }" close-delay="200">
                        <v-card outlined tiled class="mx-auto" max-width="200px" :elevation="hover ? 16 : 2" @click.native="doSelect(item.name)">

                            <v-img
                                :src="item.iconUrl"
                                class="white--text align-end"
                                height="200px"
                                width="200px">

                            </v-img>
                            <v-card-text> 
                                {{ item.name }} - {{ countryNames[item.name.toLowerCase()] }} ({{ item.stationcount}})
                            </v-card-text>
                                                

                        </v-card>
                    </v-hover>
                </v-col>
            </v-row>
    </v-container>
</template>

<script>

import WebService from "@/services/WebService"

export default {
        data: () => ({             
             countryData: [],
             countryNames: {}
        }),
        methods: {
            doSelect: function (search) {
                this.$router.push({ path: '/countries/'+search.toLowerCase() })
            }
        },

        mounted() {
            const ws = new WebService()
            ws.getCountry().then(result => {
                for (var rec of result.data){
                    this.countryNames[rec.cca2.toLowerCase()] = rec.name.common;
                }
                console.log(this.countryNames)
            }).catch(error => {
                console.error(error)
            })
            
            ws.getCountryCodes().then(result => {
                this.countryData = result.data
                for (var idx in this.countryData ){
                    this.countryData[idx].iconUrl = "https://raw.githubusercontent.com/hjnilsson/country-flags/master/png250px/"+this.countryData[idx].name.toLowerCase()+".png"
                }

                console.log(this.countryData)
            }).catch(error => {
                console.error(error)
            })
        },
        components: {
        }
  }

</script>

<style scoped>
    img:hover {
        cursor: pointer;
    }

</style>