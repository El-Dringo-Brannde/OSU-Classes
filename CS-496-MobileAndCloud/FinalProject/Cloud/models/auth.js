let axios = require('axios');

module.exports = class auth {
   constructor() { }

   async checkToken(authToken) {
      try {
         let res = await axios.get('https://www.googleapis.com/plus/v1/people/me', {
            headers: { Authorization: 'Bearer ' + authToken },
            timeout: 2000
         })
         return res.data
      } catch (err) {
         return err.response.data
      }
   }
}
