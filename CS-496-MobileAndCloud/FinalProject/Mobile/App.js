import React from 'react';
import { StyleSheet, Text, View } from 'react-native';
import {
   StackNavigator as StackNav
} from 'react-navigation';

import { welcome } from "./components/welcome";
import { Login } from './components/login/logic';
import { delivery } from './components/delivery/logic';
import { profile } from './components/profile/logic';
import { edit } from './components/edit/logic'


const RootStack = StackNav({
   Welcome: {
      screen: welcome,
   },
   Login: {
      screen: Login
   },
   Delivery: {
      screen: delivery
   },
   Profile: {
      screen: profile
   },
   Edit: {
      screen: edit
   }
},
   {
      initialRouteName: 'Welcome',
   });



export default class App extends React.Component {
   render() {
      return (
         <RootStack />
      )
   }
}
