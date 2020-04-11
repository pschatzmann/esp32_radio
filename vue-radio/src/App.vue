<template>
  <v-app id="inspire">
    <v-navigation-drawer
      v-model="drawer"
      clipped-left
      app
    >
      <v-list dense>

        <v-list-item to="/genres">
            <v-list-item-action>
                <v-icon>mdi-contact-mail</v-icon>
            </v-list-item-action>
            <v-list-item-content>
                <v-list-item-title>Radios by Genres</v-list-item-title>
            </v-list-item-content>
        </v-list-item>

        <v-list-item to="/countries">
            <v-list-item-action>
                <v-icon>mdi-contact-mail</v-icon>
            </v-list-item-action>
            <v-list-item-content>
                <v-list-item-title>Radios by Country</v-list-item-title>
            </v-list-item-content>
        </v-list-item>

        <v-list-item :to="$store.state.homeCountry.homeCountryPath" v-if="$store.state.homeCountry!=null">
            <v-list-item-action>
                <v-icon>mdi-contact-mail</v-icon>
            </v-list-item-action>
            <v-list-item-content>
                <v-list-item-title>Radios in {{ $store.state.homeCountry.homeCountryName }}</v-list-item-title>
            </v-list-item-content>
        </v-list-item>

        <v-list-item to="/about">
            <v-list-item-action>
                <v-icon>mdi-contact-mail</v-icon>
            </v-list-item-action>
            <v-list-item-content>
                <v-list-item-title>About</v-list-item-title>
            </v-list-item-content>
        </v-list-item>

      </v-list>
    </v-navigation-drawer>

    <v-app-bar
      app
      color="indigo"
      dark
    >
      <v-app-bar-nav-icon @click.stop="drawer = !drawer" />
      <v-toolbar-title>{{ $store.state.title }}</v-toolbar-title>
    </v-app-bar>

    <v-content>
        <router-view/>
    </v-content>
  </v-app>
</template>

<script>

  export default {
    props: {
      source: String,
    },
    data: () => ({
      drawer: null,
    }),
    mounted() {
          this.$store.dispatch('setupTitle')
          this.$store.dispatch('setupGenres')
          this.$store.dispatch('setupCountries')
          this.$store.dispatch('setupHomeCountry')
        }

  }
</script>

