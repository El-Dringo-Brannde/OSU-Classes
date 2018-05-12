module.exports = () => {
   return {
      name: 'health',
      register: (server, options) => {
         server.route([{
            method: 'GET',
            path: '/status',
            handler: async req => {
               return ({ status: "UP" });
            }
         }
         ])
      }
   }
}

