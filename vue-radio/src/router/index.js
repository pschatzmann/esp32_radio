/**
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
*/
import Vue from 'vue'
import VueRouter from 'vue-router'

Vue.use(VueRouter)

  const routes = [
  {
    path: '/',
    name: 'Genres',
    component:  () => import('../views/Genres'),
  },
  {
    path: '/genres',
    name: 'Genres',
    component:  () => import('../views/Genres'),
  },
  {
    path: '/genres/:id',
    name: 'Genre',
    component:  () => import('../views/Radios'),
    props: true, 
  },
  {
    path: '/countries',
    name: 'Countries',
    component:  () => import('../views/Countries'),
  },
  {
    path: '/countries/:id',
    name: 'Country',
    component:  () => import('../views/Radios'),
    props: true, 
  },
  {
    path: '/home/:id',
    name: 'Radios',
    component:  () => import('../views/Radios'),
    props: true, 
  },
  {
    path: '/about',
    name: 'About',
    component:  () => import('../views/About'),
  },
  {
    path: '/setup',
    name: 'Setup',
    component: () => import('../views/Setup'),
  },

]

const router = new VueRouter({
  routes
})

export default router
