<!-- 
 -    Provides a Start and stop button to control the playing of the radio
 -->
<script>
export default {

}
</script>

<style>

</style> */
<template>
        <v-btn fab small :color="active? 'red':'green'" dark v-on:click="active=!active" v-if="this.$store.state.activeRadio.url!=null">
              <v-icon v-if="!active">play_arrow</v-icon>
              <v-icon v-if="active">stop</v-icon>
        </v-btn>

</template>

<script>
  import MusicPlayer from '@/services/MusicPlayer'

  export default {
    data: () => ({             
         player: new MusicPlayer(),
    }),

    computed: {
        active: {
            // getter
            get: function () {
                return this.$store.state.activeRadio.active
            },
            // setter
            set: function (newValue) {
                var activeRadio = this.$store.state.activeRadio;
                activeRadio.active = newValue

                if (newValue){
                    this.player.play(this.$store.state.activeRadio.url)
                } else {
                    this.player.stop();
                    this.$store.commit('setActiveRadio', activeRadio );
                }

            }
        }
    }
  }
</script>