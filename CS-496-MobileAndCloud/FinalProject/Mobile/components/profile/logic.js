import React from 'react';
import {
   StyleSheet,
   TouchableOpacity,
   TouchableHighlight,
   Text,
   View,
   Button,
   ListView,
   AsyncStorage,
   Alert
} from 'react-native';
import axios from 'axios';
import apiUrl from "./../../constants/api";
import { SwipeListView } from 'react-native-swipe-list-view';
import styles from './style';
import { NavigationActions, nav } from 'react-navigation';

let self;

export class profile extends React.Component {
   static navigationOptions = {
      title: 'Profile',
      headerRight: (<Button
         title="Delete"
         style={{ color: 'red' }}
         onPress={async () => {
            Alert.alert('Are you sure?', 'Do you really want to erase your profile?', [
               {
                  text: 'No', onPress: () => { }
               },
               {
                  text: 'Yes', onPress: async () => {
                     let email = await AsyncStorage.getItem('email')
                     let token = await AsyncStorage.getItem('OauthToken')

                     let result = await axios.delete(`${apiUrl}/user?token=${token}&email=${email}`)
                     if (result.data.ok == 1) {
                        await AsyncStorage.removeItem('email')
                        await AsyncStorage.removeItem('OauthToken')
                     }
                     Alert.alert('Profile Deleted', 'Click Ok and go back to the welcome page', [
                        {
                           text: 'ok', onPress: () => { }
                        }
                     ])
                  }
               }
            ])


         }} />)
   };

   constructor(props) {
      super(props);
      this.ds = new ListView.DataSource({ rowHasChanged: (r1, r2) => r1 !== r2 });
      this.state = {
         listType: 'FlatList',
         listViewData: [],
      };
      self = this;
      self.email;
      self.token;
      self.OnInit();
   }

   async OnInit() {
      try {
         let token = self.token = await AsyncStorage.getItem("OauthToken");
         let email = self.email = await AsyncStorage.getItem('email')
         self.user = await axios.get(apiUrl + `/user?email=${email}&token=${token}`);
         if (self.user.data.statusCode === 401)
            alert('Not Authorized')
         self.user = self.user.data[0]
         self.user.deliveries.map((deliv, idx) => deliv.key = idx)
         this.setState({ name: self.user.name, email: self.user.email, listViewData: self.user.deliveries })
      } catch (err) { console.log(err) }
   }

   closeRow(rowMap, rowKey) {
      if (rowMap[rowKey])
         rowMap[rowKey].closeRow();
   }

   editRow(delivery) {
      this.props.navigation.navigate('Edit')
   }

   async removeDelivery(rowMap, rowKey, delivery) {
      this.closeRow(rowMap, rowKey);
      const newData = [...this.state.listViewData];
      const prevIndex = this.state.listViewData.findIndex(item => item.key === rowKey);
      newData.splice(prevIndex, 1);
      let { data } = await axios.delete(`${apiUrl}/user/delivery?email=${self.email}&token=${self.token}&deliveryId=${delivery.id}`)
      if (data.ok === 1)
         this.setState({ listViewData: newData });
      else
         alert("Oh nose, an error occured")
   }

   deleteRow(rowMap, rowKey, delivery) {
      Alert.alert('Are you sure?', 'Do you really want to delete this delivery?', [
         {
            text: 'No', onPress: () => { self.closeRow(rowMap, rowKey) }
         },
         {
            text: 'Yes', onPress: () => self.removeDelivery(rowMap, rowKey, delivery)
         }
      ])
   }


   onRowDidOpen = (rowKey, rowMap) => {
      setTimeout(() => {
         this.closeRow(rowMap, rowKey);
      }, 2000);
   }

   render() {
      return (
         <View >
            <Text> Welcome: {self.state.name} Email: {self.state.email}</Text>
            <SwipeListView
               useFlatList
               data={this.state.listViewData}
               renderItem={(data, rowMap) => (
                  <TouchableHighlight
                     onPress={_ => console.log(data)}
                     style={styles.rowFront}
                     underlayColor={'white'}>
                     <View>
                        <Text>Addr: {data.item.address}, Total: {data.item.total}, Tip: {data.item.tip}</Text>
                     </View>
                  </TouchableHighlight>
               )}
               renderHiddenItem={(data, rowMap) => (
                  <View style={styles.rowBack}>
                     <TouchableOpacity
                        style={[styles.backRightBtn, styles.backRightBtnLeft]}
                        foo={{ data: data.item }}
                        onPress={() => this.props.navigation.navigate('Edit', data.item)}>
                        <Text style={styles.backTextWhite}>Edit</Text>
                     </TouchableOpacity>
                     <TouchableOpacity
                        style={[styles.backRightBtn, styles.backRightBtnRight]}
                        onPress={_ => this.deleteRow(rowMap, data.item.key, data.item)}>
                        <Text style={styles.backTextWhite}>Delete</Text>
                     </TouchableOpacity>
                  </View>
               )}
               rightOpenValue={-150}
               onRowDidOpen={this.onRowDidOpen}
            />
         </View>
      )
   }
}
