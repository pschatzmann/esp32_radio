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
    <div>
        <v-btn fab small :color="active? 'red':'green'" dark 
            v-on:click="active=!active" 
            v-if="$store.state.activeRadio.url!=null && !$store.state.activeRadio.error">
              <v-icon v-if="!active">play_arrow</v-icon>
              <v-icon v-if="active">stop</v-icon>
        </v-btn>

        <v-tooltip left v-if="$store.state.activeRadio.error">
            <template v-slot:activator="{ on }">
                <v-icon color="red" v-on="on">
                    block
                </v-icon>
            </template>
            <span>The Stream is temporarily not available</span>
        </v-tooltip>


    </div>
</template>

<script>

  export default {
    data: () => ({      
        show: false,
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
                    this.$store.state.musicPlayer.play(this.$store.state.activeRadio.url)
                } else {
                    this.$store.state.musicPlayer.stop();
                    this.$store.commit('setActiveRadio', activeRadio );
                }

            }
        }
    }
  }
</script>