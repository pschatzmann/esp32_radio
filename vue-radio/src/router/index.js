import Vue from 'vue'
import VueRouter from 'vue-router'
import About from '../views/About'
import store from '@/store/index';

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

router.beforeResolve((to, from, next) => {
  // If this isn't an initial page load.
  if (to.name) {
      // Start the route progress bar.
      //store.commit('setLoading', true);
  }
  next()
})


export default router
