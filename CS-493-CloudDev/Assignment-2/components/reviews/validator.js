let Joi = require('joi')

class reviewValidator {
   constructor() { }
   get businessReview() {
      return {
         body: Joi.object().keys({
            owner: Joi.string().required(),
            stars: Joi.number().required(),
            cost: Joi.number().required(),
            message: Joi.string()
         })
      }
   }

   get businessReviewEdit() {
      return {
         body: Joi.object().keys({
            owner: Joi.string(),
            business: Joi.string(),
            stars: Joi.number(),
            cost: Joi.number(),
            message: Joi.string()
         }).unknown(false)
      }
   }

   get deleteReview() {
      return {
         body: {
            owner: Joi.string().required()
         }
      }
   }
}

module.exports = new reviewValidator()