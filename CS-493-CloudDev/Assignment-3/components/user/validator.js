let Joi = require('joi')

class userValidator {
   constructor() { }

   get createUser() {
      return {
         body: Joi.object().keys({
            owner: Joi.string().required(),
            type: Joi.string().allow('admin', 'user', 'owner').required(),
            email: Joi.string().required(),
            password: Joi.string().required()
         }).unknown(false),

      }
   }

   get ownedBusinesses() {
      return {
         params: {
            owner: Joi.string().required()
         }
      }
   }

   get login() {
      return {
         body: Joi.object().keys({
            owner: Joi.string().required(),
            password: Joi.string().required()
         })
      }
   }
}

module.exports = new userValidator()