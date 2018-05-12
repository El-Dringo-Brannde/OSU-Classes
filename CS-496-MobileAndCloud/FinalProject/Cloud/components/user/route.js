let userController = require('./logic')
let userSchema = require('./schema');

// all routes are prefixed with '/user'
module.exports = mongo => {
   userController = new userController(mongo, 'users')

   return {
      name: 'user',
      register: (server, options) => {

         server.route([
            {
               method: 'GET',
               path: '/',
               handler: userController.getUser
            },
            {
               method: 'DELETE',
               path: '/',
               handler: userController.removeUser,
            },
            {
               method: 'POST',
               path: '/check',
               handler: userController.checkUserProfile,
            },
            {
               method: 'POST',
               path: '/delivery',
               handler: userController.addDelivery,
            },
            {
               method: 'PATCH',
               path: '/delivery',
               handler: userController.editDelivery,
            },
            {
               method: 'DELETE',
               path: '/delivery',
               handler: userController.removeDelivery,
            }
         ])

      }
   }
}

