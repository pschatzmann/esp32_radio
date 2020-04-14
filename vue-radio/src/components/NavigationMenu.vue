<!-- 
 -  Left Navigation Menu
 
    Copyright 2020 Phil Schatzmann

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
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

        <!-- Only available if started from  ESP32 -->
        <v-list-item to="/setup" v-if="$store.state.esp32" > <!--  -->
            <v-list-item-action>
                <v-icon>settings</v-icon>
            </v-list-item-action>
            <v-list-item-content>
                <v-list-item-title>Setup</v-list-item-title>
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