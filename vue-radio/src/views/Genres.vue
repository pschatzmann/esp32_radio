<template>
    <v-container fluid>
            <v-row>
                <v-col  v-for="item in $store.state.genres" :key="item.name" >
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
    methods: {
        doSelect: function (search) {
            this.$router.push({ path: '/genres/'+search.toLowerCase() })
        }
    }
  }

</script>

<style scoped>
    .v-card {
        cursor: pointer;
    }

</style>