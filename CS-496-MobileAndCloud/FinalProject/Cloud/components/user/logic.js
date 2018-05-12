const mongoDB = require('./../../models/mongoDB');
let auth = require('./../../models/auth');
let uuid = require('uuid/v4');
var self = null;

module.exports = class user extends mongoDB {
   constructor(mongo, collName) {
      super(mongo, collName);
      this.auth = new auth();
      self = this; // important to escape scope when linking route to controller
   }

   async getUser(req = {}) {
      let authStatus = await self.auth.checkToken(req.query.token)
      if (authStatus.error && authStatus.error.code === 401)
         return ({ statusCode: 401 })
      return await self.read({ email: req.query.email })
   }

   async createUser(userObj) {
      return await self.createOne(userObj);
   }

   async checkUserProfile(req) {
      let authStatus = await self.auth.checkToken(req.query.token)
      if (authStatus.error && authStatus.error.code === 401)
         return ({ statusCode: 401 })

      let user = await self.read({ email: authStatus.emails[0].value })
      if (user.length == 0) {
         await self.createUser({ name: authStatus.displayName, email: authStatus.emails[0].value, deliveries: [] })
         return await self.read({ email: authStatus.emails[0].value })
      } else
         return await self.read({ email: authStatus.emails[0].value })
   }

   async addDelivery(req) {
      let authStatus = await self.auth.checkToken(req.query.token)
      if (authStatus.error && authStatus.error.code === 401)
         return ({ statusCode: 401 })
      req.payload.id = uuid();
      return await self.addToSet({ email: req.query.email }, 'deliveries', req.payload)
   };

   async editDelivery(req) {
      let authStatus = await self.auth.checkToken(req.query.token)
      if (authStatus.error && authStatus.error.code === 401)
         return ({ statusCode: 401 })
      let { result } = await self.pullFromSet({ email: req.query.email }, 'deliveries', req.payload.deliveryId)
      if (result.nModified != 1) // error removing delivery
         return { data: { ok: -1 } }
      else
         return await self.addDelivery(req)
   };

   async removeDelivery(req) {
      let authStatus = await self.auth.checkToken(req.query.token)
      if (authStatus.error && authStatus.error.code === 401)
         return ({ statusCode: 401 })
      return await self.pullFromSet({ email: req.query.email }, 'deliveries', req.query.deliveryId)
   }

   async removeUser(req) {
      let authStatus = await self.auth.checkToken(req.query.token)
      if (authStatus.error && authStatus.error.code === 401)
         return ({ statusCode: 401 })
      return await self.deleteOne({ email: req.query.email })
   }
}