import React, { Component } from 'react';
import { StyleSheet, Text, TextInput, View, Button, AsyncStorage, DatePickerIOS } from 'react-native';
import { FloatingLabelInput } from './../../models/floatingLabelInput';
import SnackBar from 'react-native-snackbar-component'
import axios from 'axios';
import apiUrl from './../../constants/api';
import styles from './style'

let self;
export class delivery extends React.Component {
   static navigationOptions = {
      title: 'Delivery',
   };

   constructor() {
      super();
      this.state = {
         address: '',
         total: '',
         tip: '',
         toggleSnackBar: false,
         chosenDate: new Date(),
         name: ''
      };
      self = this;
      self.token;
      self.email;
      this.OnInit();
   }

   async OnInit() {
      try {
         self.token = await AsyncStorage.getItem("OauthToken");
         self.email = await AsyncStorage.getItem('email')
         let user = await axios.get(`${apiUrl}/user?email=${self.email}&token=${self.token}`);
         if (user.data.statusCode === 401)
            alert('Not Authorized')
         user = user.data[0]
         self.setState({ name: user.name })
      } catch (err) { console.log(err) }
   }

   toggleSnackBar() {
      self.setState({ toggleSnackBar: !self.state.toggleSnackBar })
   }

   async delivered() {
      let delivery = {
         address: self.state.address,
         total: self.state.total,
         tip: self.state.tip,
         time: new Date()
      }
      let { data } = await axios.post(`${apiUrl}/user/delivery?email=${self.email}&token=${self.token}`, delivery)
      if (data.ok === 1)
         self.setState({ toggleSnackBar: true })
   }

   updateAddr = (newText) => this.setState({ address: newText });
   updateTotal = (newText) => this.setState({ total: newText });
   updateTip = (newText) => this.setState({ tip: newText });

   render() {
      return (
         <View style={styles.container}>
            <Text> Let's add a pizza delivery {this.state.name}</Text>
            <FloatingLabelInput
               label="Address"
               value={this.state.address}
               onChangeText={this.updateAddr} />
            <FloatingLabelInput
               label="Total"
               value={this.state.total}
               onChangeText={this.updateTotal} />
            <FloatingLabelInput
               label="Tip Amount"
               value={this.state.tip}
               onChangeText={this.updateTip} />
            <DatePickerIOS
               date={this.state.chosenDate}
               onDateChange={newDate => this.setState({ chosenDate: newDate })}
            />
            <Button onPress={this.delivered} title='Submit' />
            <SnackBar visible={this.state.toggleSnackBar} textMessage="Added Successfully!" actionHandler={this.toggleSnackBar} actionText="Ok" />
         </View >
      );
   }
}