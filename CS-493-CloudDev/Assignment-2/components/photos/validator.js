let Joi = require('joi')

class photoValidator {
   constructor() { }
   get businessPhotoEdit() {
      return {
         body: Joi.object().keys({
            owner: Joi.string(),
            caption: Joi.string(),
            image: Joi.string().uri()
         })
      }
   }

   get businessPhoto() {
      return {
         body: Joi.object().keys({
            owner: Joi.string().required(),
            business: Joi.string().required(),
            caption: Joi.string(),
            image: Joi.string().uri().required()
         })
      }
   }

   get deletePhoto() {
      return {
         body: {
            owner: Joi.string().required()
         }
      }
   }
}

module.exports = new photoValidator()