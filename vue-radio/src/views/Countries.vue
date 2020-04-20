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
            <v-row>
                <v-col  v-for="item in $store.state.countries" :key="item.stationuuid" >
                    <v-hover  v-slot:default="{ hover }" close-delay="200">
                        <v-card outlined tiled class="mx-auto" max-width="200px" :elevation="hover ? 16 : 2" @click.native="doSelect(item.name)">

                            <v-img
                                :src="getUrl(item.iconUrl)"
                                class="white--text align-end"
                                height="200px"
                                width="200px">

                            </v-img>
                            <v-card-text> 
                                {{ item.countryCode }} - {{ item.counrtyName }} ({{ item.stationcount}})
                            </v-card-text>
                                                
                        </v-card>
                    </v-hover>
                </v-col>
            </v-row>
    </v-container>
</template>

<script>

export default {
    data: () => ({             
    }),

    methods: {
        doSelect: function (search) {
            this.$router.push({ path: '/countries/'+search.toLowerCase() })
        },

        getUrl(path){
            var result = path
            if (this.$store.state.esp32) {
                // the esp32 cant handle too many concurrent requests, therfore we send it directly
                // to the final server address
                result = this.$store.state.resourceAddress + path
            }
            return result;
        }
    },

    mounted() {
        this.$store.dispatch('setupCountries')
    }
}

</script>

<style>
    .v-card {
        cursor: pointer;
    }

</style>