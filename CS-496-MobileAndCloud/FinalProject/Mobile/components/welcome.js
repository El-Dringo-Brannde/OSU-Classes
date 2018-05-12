import React from 'react';
import { StyleSheet, NavigatorIOS, Button, Text, View } from 'react-native';


export class welcome extends React.Component {
   static navigationOptions = {
      title: 'Welcome'
   };
   render() {
      return (
         <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>
            <Text>Hello! Welcome to my final project for CS 496 :)</Text>
            <Text> Here we can track theoretical pizzas if you were a delivery driver </Text>
            <Button
               title="Profile Page"
               onPress={() => this.props.navigation.navigate('Profile')} />

            <Button
               title="Login/Logout Page"
               onPress={() => this.props.navigation.navigate('Login')} />

            <Button
               title="Add A Delivery"
               onPress={() => this.props.navigation.navigate('Delivery')} />

         </View>
      )
   }
}