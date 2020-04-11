<template>
    <v-container fluid>
            <v-row>
                <v-col cols="20" sm="1" md="3"  v-for="item in this.radios" :key="item.stationuuid" >
                    <v-hover  v-slot:default="{ hover }" close-delay="200">
                        <v-card outlined tiled class="mx-auto" v-bind:class="{ pulsate: isPlaying(item.stationuuid) }" max-width="200px" :elevation="hover ? 16 : 2" @click.native="play(item.url_resolved, item.stationuuid)">

                            <v-img 
                                :src="item.favicon"
                                height="200px"
                                width="200px">

                                <template v-slot:placeholder>
                                    <v-row
                                    class="fill-height ma-0"
                                    align="center"
                                    justify="center"
                                    >
                                    <v-img
                                        :src=defaultImage
                                        height="200px"
                                        width="200px"/>

                                    </v-row>
                                </template>

                            </v-img>
                            <v-card-text v-text="item.name">
                            </v-card-text>
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
            player: new MusicPlayer(),
            defaultImage: "http://icons.iconarchive.com/icons/webalys/kameleon.pics/128/Radio-4-icon.png"
        }),

        methods: {
            play: function (url, id) {
                var result = {};
                result.id = id;
                result.url = url;
                if (this.isPlaying(id)) {
                    this.player.stop();
                    result.active = false;
                    this.$store.commit('setActiveRadio', result );
                } else {
                    this.player.play(url).then(r => {
                        result.active = this.player.isPlaying();
                        this.$store.commit('setActiveRadio', result );
                        console.log(r)
                    }, error => {
                        console.error(error)
                    }).catch(e => {
                        console.log(e);
                    });
                }
            },

            isPlaying(id){
                return this.$store.state.activeRadio.active && this.$store.state.activeRadio.id==id
            }
        },

        mounted() {
            var searchTerm = this.$router.currentRoute.params['id']=== undefined ? "blues": this.$router.currentRoute.params.id;
            var field = this.$router.currentRoute.name == 'Genre' ? 'tag' : 'countrycode'
            const ws = new WebService()
            ws.getRadios(field, searchTerm).then(result => {
                this.radios = result.data
            }).catch(error => {
                console.error(error)
            })
        }
    }

</script>

<style scoped>
    .v-card {
        cursor: pointer;
    }

    .pulsate {
        animation: pulse 1s infinite;
    }

    @keyframes pulse {
        0% {
            background-color: lightgrey;
        }
        100% {
            background-color: white;
        }
    }

</style>