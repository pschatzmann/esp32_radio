<template>
    <v-container fluid>
            <v-row>
                <v-col  v-for="item in this.radios" :key="item.stationuuid" >
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
                                        :src="require('@/assets/radio.svg')"
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

    export default {
        data: () => ({
            radios: [],
            hover: false,
        }),

        methods: {
            play: function (url, id) {
                // stop current stream
                var current = this.$store.state.activeRadio
                current.active = false;
                this.$store.commit('setActiveRadio', current );

                // set new radio
                var result = {};
                result.id = id;
                result.url = url;
                var player = this.$store.state.musicPlayer;
                if (this.isPlaying(id)) {
                    player.stop();
                    result.active = false;
                    this.$store.commit('setActiveRadio', result );
                } else {
                    player.play(url).then(playing => {
                        result.active = playing;
                        this.$store.commit('setActiveRadio', result );
                    }, error => {
                        console.error(error)
                    }).catch(e => {
                        console.log(e);
                    });
                }
            },

            getRadios(field, value){
                var temp = this.$store.state.radios[field+value]
                if (temp!=null){
                    this.radios = temp;
                    this.$store.commit('setLoading', false);

                } else {
                    this.$store.commit('setLoading', true);
                    const ws = new WebService()
                    ws.getRadios(field, value).then(result => {
                        this.radios = result.data
                            .filter(rec => rec.lastcheckok==1 && !this.$store.state.blacklist.includes(rec.stationuuid))
                            .sort((c1, c2) => c2.clickcount - c1.clickcount)

                        this.$store.commit('setRadios', {id:field+value, value:this.radios});
                        this.$store.commit('setLoading', false);

                    }).catch(error => {
                        console.error(error)
                        this.$store.commit('setLoading', false);
                    })
                }
            },

            isPlaying(id){
                return this.$store.state.activeRadio.active && this.$store.state.activeRadio.id==id
            }
        },

        mounted() {
            this.$store.commit('setLoading', true);
            var searchTerm = this.$router.currentRoute.params['id']=== undefined ? "blues": this.$router.currentRoute.params.id;
            var field = this.$router.currentRoute.name == 'Genre' ? 'tag' : 'countrycode'
            this.getRadios(field, searchTerm);
        },
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
            background-color: black;
        }
    }

</style>