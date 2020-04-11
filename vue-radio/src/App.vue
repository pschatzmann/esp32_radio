<template>
  <v-app id="inspire">
    <navigation-menu/>
    <v-app-bar
      app
      color="indigo"
      dark
    >
      <v-app-bar-nav-icon @click.stop="toggleDrawer()" />
      <v-toolbar-title>{{ $store.state.title }}</v-toolbar-title>
    </v-app-bar>

    <v-content>
        <router-view/>
    </v-content>
  </v-app>
</template>

<script>
  import NavigationMenu from '@/components/NavigationMenu'

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
      this.$store.dispatch('setupTitle')
      this.$store.dispatch('setupGenres')
      this.$store.dispatch('setupCountries')
      this.$store.dispatch('setupHomeCountry')
    },
    
    components: {
      'navigation-menu': NavigationMenu
    }
  }

</script>

