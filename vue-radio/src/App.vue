<!--
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
      <div class="radioTitle">
          {{ getRadioTitle() }}
      </div>
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

  export default {
    props: {
      source: String,
    },

    methods: {
        toggleDrawer(){
            var newValue = !this.$store.state.drawer
            this.$store.commit('setDrawer', newValue );
        },

        getRadioTitle(){
            var result = this.$store.state.activeRadio.name
            if (result.length>50){
                result = result.substring(0,50)+"..."
            }
            return result
        }
    },

    mounted() {
      this.$store.commit('setMusicPlayer', 0);
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

<style>
    .radioTitle {
        font-size: 11px;
        font-style: italic;
        padding-right: 14px;
    }
</style>