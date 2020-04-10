<template>
    <v-container fluid>
            <v-row>
                <v-col cols="20" sm="1" md="3"  v-for="item in this.genres" :key="item.name" >
                    <v-hover  v-slot:default="{ hover }" close-delay="200">
                        <v-card outlined tiled class="mx-auto" max-width="200px" :elevation="hover ? 16 : 2" @click.native="doSelect(item.name)">

                            <v-img
                                :src="item.imageUrl"
                                class="white--text align-end"
                                height="200px"
                                width="200px">

                            </v-img>
                            <v-card-text> 
                                {{ item.name }}
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
             genres: [{"name":"African", "imageUrl":"https://i.pinimg.com/originals/33/61/70/336170387ceaf2d3e5316e6630d6fbab.jpg"},
                        {"name":"Blues","imageUrl":"https://www.hotelaurora.org/sites/default/files/styles/large/public/events/images/blues4.jpg?itok=dBF52e-E"},
                        {"name":"Caribbean","imageUrl":"http://www.littleharbourestates.com/wp-content/uploads/2016/02/caribbean-music.jpg"},
                        {"name":"Country","imageUrl":"https://www.traveldailymedia.com/assets/2019/12/country-music.jpg"},
                        {"name":"Electronic","imageUrl":"http://morozoffent.com/wp-content/uploads/2018/01/Music-Trends-morozoffent.jpg"},
                        {"name":"Folk","imageUrl":"https://www.ebu.ch/files/live/sites/ebu/files/Groups/Radio/euroradio-folk.jpg"},
                        {"name":"Hip hop","imageUrl":"https://image.shutterstock.com/image-vector/hip-hop-music-illustration-graffiti-600w-757742746.jpg"},
                        {"name":"Jazz","imageUrl":"https://www.udiscovermusic.com/wp-content/uploads/2019/04/best-jazz-songs.jpg"},
                        {"name":"Latin","imageUrl":"https://bestradio.fm/uploads/posts/2013-11/1385730994_latino-online_dance_music.jpg"},
                        {"name":"Pop","imageUrl":"https://kehillah.org/wp-content/uploads/2019/01/288-2884897_pop-music-royalty-free-clip-art-pop-music-logo-png-300x224.jpg"},
                        {"name":"Soul","imageUrl":"https://media.gettyimages.com/vectors/soul-sista-grunge-vector-id165069456?s=2048x2048"},
                        {"name":"Rock","imageUrl":"https://previews.123rf.com/images/paseven/paseven1711/paseven171100076/89699839-banni%C3%A8re-de-vecteur-ou-embl%C3%A8me-avec-des-mots-musique-rock-guitare-%C3%A9lectrique-avec-des-ailes-sur-le-fond-d-.jpg"},
                        {"name":"Classical","imageUrl":"https://www.albawaba.com/sites/default/files/styles/de2e_standard/public/im/Classical-Music-Wallpaper.jpg?itok=VXi1I9f8"}]
        }),
        
        methods: {
            doSelect: function (search) {
                this.$router.push({ path: '/genres/'+search.toLowerCase() })
            }

        },

        components: {
        }
  }

</script>

<style scoped>
    .v-card {
        cursor: pointer;
    }

</style>