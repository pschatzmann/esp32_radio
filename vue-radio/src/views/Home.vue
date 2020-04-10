<template>
    <v-container fluid>
            <v-row>
                <v-col cols="20" sm="1" md="3"  v-for="item in this.radios" :key="item.stationuuid" >
                    <v-hover  v-slot:default="{ hover }" close-delay="200">
                        <v-card outlined tiled class="mx-auto" max-width="200px" :elevation="hover ? 16 : 2">

                            <v-img
                                :src="item.favicon"
                                class="white--text align-end"
                                height="200px"
                                width="200px">

                                <template v-slot:placeholder>
                                    <v-row
                                    class="fill-height ma-0"
                                    align="center"
                                    justify="center"
                                    >
                                    <v-img
                                        src="http://icons.iconarchive.com/icons/webalys/kameleon.pics/128/Radio-4-icon.png"
                                        class="white--text align-end"
                                        height="200px"
                                        width="200px"/>

                                    </v-row>
                                </template>

                            </v-img>
                            <v-card-text v-text="item.name">
                            </v-card-text>
                            
                            <v-card-actions>
                                <v-btn icon color="blue" @click="play(item.url_resolved)">
                                      <v-icon>mdi-play</v-icon>
                                </v-btn>

                                <!--
                                <v-btn icon color="red">
                                      <v-icon>mdi-heart</v-icon>
                                </v-btn>
                                -->

                            </v-card-actions>
                            

                        </v-card>
                    </v-hover>
                </v-col>
            </v-row>
    </v-container>
</template>

<script>
    import WebService from "@/services/WebService"
    import MusicPlayer from '@/services/MusicPlayer'

    export default {
        data: () => ({
            radios: [],
            hover: false,
            player: new MusicPlayer()
        }),

        methods: {
            play: function (url) {
                this.player.play(url)
            }
        },

        mounted() {
            var searchTerm = this.$router.currentRoute.params['id']=== undefined ? "blues": this.$router.currentRoute.params.id;
            var field = this.$router.currentRoute.name == 'Genre' ? 'tag' : 'countrycode'
            const ws = new WebService()
            ws.getRadios(field, searchTerm).then(result => {
                this.radios = result.data
                console.log('mount finised '+this.radios.length)
            }).catch(error => {
                console.error(error)
            })
        }
    }

</script>
