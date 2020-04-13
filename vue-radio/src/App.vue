<template>
  <v-app id="inspire">
    <navigation-menu/>
    <v-app-bar
      app
      color="darkblue"
      dark
    >
      <v-app-bar-nav-icon @click.stop="toggleDrawer()" />
      <v-toolbar-title>{{ $store.state.title }}</v-toolbar-title>

      <v-progress-linear 
        :active='$store.state.loading'
        absolute
        bottom
        indeterminate
        color="amber"
      ></v-progress-linear>


      <v-spacer/>
      <start-stop-control/>
    </v-app-bar>

    <v-content>
        <router-view/>
    </v-content>
  </v-app>
</template>

<script>
  import NavigationMenu from '@/components/NavigationMenu'
  import StartStopControl from '@/components/StartStop'
  import MusicPlayer from '@/services/MusicPlayer'

  export default {
    props: {
      source: String,
    },

    methods: {
        toggleDrawer(){
            var newValue = !this.$store.state.drawer
            this.$store.commit('setDrawer', newValue );
        }
    },

    mounted() {
      this.$store.commit('setMusicPlayer', new MusicPlayer());
      this.$store.dispatch('setupBlacklist')
      this.$store.dispatch('setupTitle')
      this.$store.dispatch('setupHomeCountry')
    },

    
    components: {
      'navigation-menu': NavigationMenu,
      'start-stop-control': StartStopControl
    }
  }

</script>

