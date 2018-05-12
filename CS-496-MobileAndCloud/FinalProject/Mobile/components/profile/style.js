import { StyleSheet } from 'react-native';
export default styles = StyleSheet.create({
   container: {
      backgroundColor: 'white',
      flex: 1
   },
   standalone: {
      marginTop: 30,
      marginBottom: 30,
   },
   standaloneRowFront: {
      alignItems: 'center',
      backgroundColor: '#CCC',
      justifyContent: 'center',
      height: 50,
   },
   standaloneRowBack: {
      alignItems: 'center',
      backgroundColor: '#8BC645',
      flex: 1,
      flexDirection: 'row',
      justifyContent: 'space-between',
      padding: 15
   },
   backTextWhite: {
      color: '#FFF'
   },
   rowFront: {
      alignItems: 'center',
      backgroundColor: '#ffffff',
      borderBottomColor: 'black',
      borderBottomWidth: 1,
      justifyContent: 'center',
      height: 50,
   },
   rowBack: {
      alignItems: 'center',
      backgroundColor: '#DDD',
      flex: 1,
      flexDirection: 'row',
      justifyContent: 'space-between',
      paddingLeft: 15,
   },
   backRightBtn: {
      alignItems: 'center',
      bottom: 0,
      justifyContent: 'center',
      position: 'absolute',
      top: 0,
      width: 75
   },
   backRightBtnLeft: {
      backgroundColor: 'blue',
      right: 75
   },
   backRightBtnRight: {
      backgroundColor: 'red',
      right: 0
   },
   controls: {
      alignItems: 'center',
      marginBottom: 30
   },
   switchContainer: {
      flexDirection: 'row',
      justifyContent: 'center',
      marginBottom: 5
   }
});