<template>
    <v-container fluid>
            <v-row>
                <v-col cols="20" sm="1" md="3"  v-for="item in $store.state.countries" :key="item.stationuuid" >
                    <v-hover  v-slot:default="{ hover }" close-delay="200">
                        <v-card outlined tiled class="mx-auto" max-width="200px" :elevation="hover ? 16 : 2" @click.native="doSelect(item.name)">

                            <v-img
                                :src="item.iconUrl"
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
            }
        }
  }

</script>

<style scoped>
    .v-card {
        cursor: pointer;
    }

</style>