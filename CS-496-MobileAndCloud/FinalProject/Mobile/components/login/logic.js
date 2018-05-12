import React from 'react';
import { StyleSheet, TouchableOpacity, Text, View, AsyncStorage, Button } from 'react-native';
import Expo from 'expo';
import axios from 'axios';
import SnackBar from 'react-native-snackbar-component'

import { OauthID, OauthPass } from './../../constants/oauth'
import apiUrl from './../../constants/api'
import styles from './style'



export class Login extends React.Component {
   static navigationOptions = {
      title: 'Login',
   };
   constructor(props) {
      super(props)
      this.state = {
         toggle: false,
         snackMessage: "",
      }
      this.onInit()

   }

   async onInit() {
      try {
         let token = await AsyncStorage.getItem("OauthToken");
         let email = await AsyncStorage.getItem('email')
         let user = await axios.get(`${apiUrl}/user?email=${email}&token=${token}`);
         user = user.data[0]
         this.setState({ name: user.name })
      } catch (err) { console.log(err) }
   }


   async login() {
      const { type, accessToken } = await Expo.Google.logInAsync({
         iosClientId: OauthID,
         scopes: ['profile', 'email'],
      });

      if (type === 'success') {
         await AsyncStorage.setItem('OauthToken', accessToken);
         this.attemptToCreateProfile(accessToken)
      } else
         alert("Oh nose, hull breach")
   }

   async attemptToCreateProfile(accessToken) {
      let result = await axios.post(`${apiUrl}/user/check?token=${accessToken}`)

      await AsyncStorage.setItem('email', result.data[0].email)
      this.setState({ name: result.data[0].name })
      if (result.data.length == 1)
         this.setState({ snackMessage: `Welcome Back ${result.data[0].name}`, toggle: true })
   }

   async logout() {
      let f = await AsyncStorage.removeItem('OauthToken');
      let g = await AsyncStorage.removeItem('email')
      if (!f && !g)
         this.setState({ toggle: !this.state.toggle, snackMessage: "Successfully Logged Out!", name: '' })
   }

   get button() {
      return (
         <View>
            <Text> Use oAuth to Login </Text>
            <TouchableOpacity onPress={() => this.login()} style={{ width: '50%', borderRadius: 4, padding: 24, backgroundColor: '#3b5998' }}>
               <View >
                  <Text style={{ color: 'white' }}> Login To Google</Text>
               </View>
            </TouchableOpacity>

            <TouchableOpacity onPress={() => this.logout()} style={{ width: '50%', borderRadius: 4, padding: 24, backgroundColor: '#3b5998' }}>
               <View >
                  <Text style={{ color: 'white' }}> Logout </Text>
               </View>
            </TouchableOpacity>

         </View>
      )
   }

   render() {
      return (
         <View style={styles.container}>
            <Text> Hello {this.state.name}</Text>
            {this.button}
            <SnackBar
               visible={this.state.toggle}
               textMessage={this.state.snackMessage}
               actionHandler={() => this.setState({ toggle: !this.state.toggle })}
               actionText="Ok" />
         </View>
      )
   }
}