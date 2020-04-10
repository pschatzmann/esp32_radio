import Vue from 'vue'
import VueRouter from 'vue-router'
import Radios from '../views/Radios.vue'
import Countries from '../views/Countries.vue'
import Genres from '../views/Genres.vue'

Vue.use(VueRouter)

  const routes = [
  {
    path: '/',
    name: 'Genres',
    component: Genres
  },
  {
    path: '/genres',
    name: 'Genres',
    component: Genres
  },
  {
    path: '/genres/:id',
    name: 'Genre',
    component: Radios,
    props: true, 
  },
  {
    path: '/countries',
    name: 'Countries',
    component: Countries
  },
  {
    path: '/countries/:id',
    name: 'Country',
    component: Radios,
    props: true, 
  },
  {
    path: '/home/:id',
    name: 'Radios',
    component: Radios,
    props: true, 
  },
]

const router = new VueRouter({
  routes
})

export default router
