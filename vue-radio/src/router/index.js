import Vue from 'vue'
import VueRouter from 'vue-router'
import Radios from '../views/Radios'
import Countries from '../views/Countries'
import Genres from '../views/Genres'
import About from '../views/About'
import Setup from '../views/Setup'

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
  {
    path: '/about',
    name: 'About',
    component: About,
  },
  {
    path: '/setup',
    name: 'Setup',
    component: Setup,
  },

]

const router = new VueRouter({
  routes
})

export default router
