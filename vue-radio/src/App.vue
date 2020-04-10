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
                <v-list-item-title>By Genres</v-list-item-title>
            </v-list-item-content>
        </v-list-item>

        <v-list-item to="/countries">
            <v-list-item-action>
                <v-icon>mdi-contact-mail</v-icon>
            </v-list-item-action>
            <v-list-item-content>
                <v-list-item-title>By Country</v-list-item-title>
            </v-list-item-content>
        </v-list-item>

        <v-list-item :to="homeCountryPath" v-if="homeCountryName!=null">
            <v-list-item-action>
                <v-icon>mdi-contact-mail</v-icon>
            </v-list-item-action>
            <v-list-item-content>
                <v-list-item-title>My Country</v-list-item-title>
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
      <v-toolbar-title>Radio Player for ESP32</v-toolbar-title>
    </v-app-bar>

    <v-content>
        <router-view/>
    </v-content>
  </v-app>
</template>

<script>
import WebService from "@/services/WebService"

  export default {
    props: {
      source: String,
      homeCountryPath: null,
      homeCountryName: null
    },
    data: () => ({
      drawer: null,
    }),
    mounted() {
            const ws = new WebService()
            ws.getUserCountry().then(result => {
                this.homeCountryName = result.data.country_name
                this.homeCountryPath = '/countries/'+result.data.country_code.toLowerCase()
            }).catch(error => {
                console.error(error)
            })
        }

  }
</script>

