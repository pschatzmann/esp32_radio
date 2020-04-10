import Vue from 'vue'
import VueRouter from 'vue-router'
import Home from '../views/Home.vue'
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
    component: Home,
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
    component: Home,
    props: true, 
  },
]

const router = new VueRouter({
  routes
})

export default router
