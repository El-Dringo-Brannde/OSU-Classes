let Joi = require('joi')

class userValidator {
   constructor() { }

   get createUser() {
      return {
         body: Joi.object().keys({
            owner: Joi.string().required(),
            type: Joi.string().allow('admin', 'user', 'owner').required()
         }).unknown(false),

      }
   }
}

module.exports = new userValidator()