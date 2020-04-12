<!-- 
 -    Left Navigation Menu
 -->
<template>
    <v-navigation-drawer
      v-model="drawer"
      clipped-left
      app
    >
      <v-list dense>

        <v-list-item to="/genres">
            <v-list-item-action>
                <v-icon>apps</v-icon>
            </v-list-item-action>
            <v-list-item-content>
                <v-list-item-title>Radios by Genre</v-list-item-title>
            </v-list-item-content>
        </v-list-item>

        <v-list-item to="/countries">
            <v-list-item-action>
                <v-icon>map</v-icon>
            </v-list-item-action>
            <v-list-item-content>
                <v-list-item-title>Radios by Country</v-list-item-title>
            </v-list-item-content>
        </v-list-item>

        <v-list-item :to="$store.state.homeCountry.homeCountryPath" v-if="$store.state.homeCountry!=null">
            <v-list-item-action>
                <v-img width="8" :src="$store.state.homeCountry.iconUrl"/>
            </v-list-item-action>
            <v-list-item-content>
                <v-list-item-title>Radios in {{ $store.state.homeCountry.homeCountryName }}</v-list-item-title>
            </v-list-item-content>
        </v-list-item>

        <v-list-item to="/about">
            <v-list-item-action>
                <v-icon>info</v-icon>
            </v-list-item-action>
            <v-list-item-content>
                <v-list-item-title>About</v-list-item-title>
            </v-list-item-content>
        </v-list-item>

        <v-list-item to="/setup">
            <v-list-item-action>
                <v-icon>settings</v-icon>
            </v-list-item-action>
            <v-list-item-content>
                <v-list-item-title>Setup</v-list-item-title>
            </v-list-item-content>
        </v-list-item>
      </v-list>
    </v-navigation-drawer>
</template>

<script>

  export default {

    computed: {
        drawer: {
            // getter
            get: function () {
                return this.$store.state.drawer
            },
            // setter
            set: function (newValue) {
                this.$store.commit('setDrawer', newValue );
            }
        }
    }

  }
</script>