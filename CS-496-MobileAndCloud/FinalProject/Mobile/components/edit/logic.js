import React from 'react';
import { StyleSheet, DatePickerIOS, Text, View, Button, AsyncStorage } from 'react-native';
import { FloatingLabelInput } from './../../models/floatingLabelInput';
import SnackBar from 'react-native-snackbar-component'
import axios from 'axios';
import styles from './style'

var self;
export class edit extends React.Component {
   static navigationOptions = {
      headerTitle: 'Edit Delivery'
   }

   constructor(props) {
      super(props)
      let delivery = this.props.navigation.state.params
      this.state = {
         address: delivery.address,
         total: delivery.total,
         tip: delivery.tip,
         toggleSnackBar: false,
         time: new Date(delivery.time),
         deliveryId: delivery.id,
         name: '',
      };
      this.OnInit();
      self = this;
   }

   async OnInit() {
      let token = await AsyncStorage.getItem("OauthToken");
      let email = await AsyncStorage.getItem('email')
      let user = await axios.get(apiUrl + `/user?email=${email}&token=${token}`);
      if (user.data.statusCode === 401)
         alert('Not Authorized')
      user = user.data[0]
      this.setState({ name: user.name, email: email, token: token })
      return user;
   }

   toggleSnackBar() {
      self.setState({ toggleSnackBar: !self.state.toggleSnackBar })
      self.props.navigation.popToTop()
   }

   async update() {
      let delivery = {
         deliveryId: this.state.deliveryId,
         tip: this.state.tip,
         address: this.state.address,
         time: this.state.time,
         total: this.state.total
      }
      let { data } = await axios.patch(`${apiUrl}/user/delivery?email=${this.state.email}&token=${this.state.token}`, delivery)
      if (data.ok === 1)
         this.setState({ toggleSnackBar: true })
   }

   updateAddr = (newText) => this.setState({ address: newText });
   updateTotal = (newText) => this.setState({ total: newText });
   updateTip = (newText) => this.setState({ tip: newText });

   render() {
      return (
         <View style={styles.container}>
            <Text> {this.state.name} delivery on {new Date(this.state.time).toLocaleTimeString()}</Text>
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
               date={this.state.time}
               onDateChange={newDate => this.setState({ time: newDate })}
            />
            <Button onPress={() => this.update()} title='Update Delivery' />
            <SnackBar visible={this.state.toggleSnackBar}
               textMessage="Updated Successfully!"
               actionHandler={this.toggleSnackBar}
               actionText="Ok"
               position='bottom' />
         </View >
      )
   }
}