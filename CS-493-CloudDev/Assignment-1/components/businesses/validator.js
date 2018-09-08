let Joi = require('joi')
Joi.objectId = require('joi-objectid')(Joi)

class businessValidator {
   constructor() { }

   get createdBusiness() {
      return {
         body: Joi.object().keys({
            name: Joi.string().required(),
            owner: Joi.string().required(),
            address: Joi.string().required(),
            city: Joi.string().required(),
            state: Joi.string().required(),
            zip: Joi.number().required(),
            phone: Joi.string().required(),
            category: Joi.array().items(Joi.string()).required(),
            subCategory: Joi.array().items(Joi.string()).required(),
            website: Joi.string().uri(),
            email: Joi.string().email()
         }).unknown(false)
      }
   }

   get getBusiness() {
      return {
         params: {
            businessID: Joi.objectId()
         }
      }
   }

   get editBusiness() {
      return {
         params: {
            businessID: Joi.objectId()
         },
         body: Joi.object().keys({
            name: Joi.string(),
            owner: Joi.string().required(),
            address: Joi.string(),
            city: Joi.string(),
            state: Joi.string(),
            zip: Joi.number(),
            phone: Joi.string(),
            category: Joi.array().items(Joi.string()),
            subCategory: Joi.array().items(Joi.string()),
            website: Joi.string().uri(),
            email: Joi.string().email()
         }).unknown(false)
      }
   }

   get editCategory() {
      return {
         body: Joi.object().keys({
               owner: Joi.string().required(),
               category: Joi.string().required()
            }).unknown(false).required()
      }
   }

   get deleteBusiness() {
      return {
         params: {
            businessID: Joi.objectId()
         },
         body: Joi.object().keys({
            owner: Joi.string().required()
         }).unknown(false).required()
      }
   }

   get businessReview() {
      return {
         params: {
            businessID: Joi.objectId()
         },
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
         params: {
            businessID: Joi.objectId(),
            reviewID: Joi.string()
         },
         body: Joi.object().keys({
            owner: Joi.string(),
            stars: Joi.number(),
            cost: Joi.number(),
            message: Joi.string()
         })
      }
   }

   get businessPhotoEdit() {
      return {
         params: {
            businessID: Joi.objectId(),
            photoID: Joi.string()
         },
         body: Joi.object().keys({
            owner: Joi.string(),
            caption: Joi.string(),
            image: Joi.string().uri()
         })
      }
   }

   get getReviews() {
      return {
         params: {
            businessID: Joi.objectId()
         }
      }
   }

   get getReview() {
      return {
         params: {
            businessID: Joi.objectId(),
            reviewID: Joi.string()
         }
      }
   }

   get businessPhoto() {
      return {
         params: {
            businessID: Joi.objectId()
         },
         body: Joi.object().keys({
            owner: Joi.string().required(),
            caption: Joi.string(),
            image: Joi.string().uri().required()
         })
      }
   }

   get deletePhoto() {
      return {
         params: {
            businessID: Joi.objectId(),
            photoID: Joi.string()
         },
         body: {
            owner: Joi.string().required()
         }
      }
   }

   get deleteCategory() {
      return {
         query: {
            owner: Joi.string().required()
         }
      }
   }


   get deleteReview() {
      return {
         params: {
            businessID: Joi.objectId(),
            reviewID: Joi.string()
         },
         body: {
            owner: Joi.string().required()
         }
      }
   }

   get subCategory() {
      return {
         params: {
            category: Joi.string().required()
         },
         body: Joi.object().keys({
            owner: Joi.string().required(),
            subCategory: Joi.string().required() //add ability to post arrays?
         })
      }
   }

   get getSubCategories() {
      return {
         params: {
            category: Joi.string().required()
         }
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

module.exports = new businessValidator()