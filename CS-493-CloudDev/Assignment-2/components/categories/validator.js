let Joi = require('joi')

class categoryValidator {
   constructor() { }
   get editCategory() {
      return {
         body: Joi.object().keys({
            owner: Joi.string().required(),
            category: Joi.string().required()
         }).unknown(false).required()
      }
   }

   get deleteCategory() {
      return {
         query: {
            owner: Joi.string().required()
         }
      }
   }

   get subCategory() {
      return {
         body: Joi.object().keys({
            owner: Joi.string().required(),
            subCategory: Joi.string().required() //add ability to post arrays?
         })
      }
   }


   get category() {
      return {
         body: Joi.object().keys({
            owner: Joi.string().required()
         })
      }
   }
}

module.exports = new categoryValidator()