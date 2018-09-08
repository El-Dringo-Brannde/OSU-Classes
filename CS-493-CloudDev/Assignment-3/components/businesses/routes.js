let router = require('express').Router();
let controller = require('./logic');
let validator = require('./validator');
let validate = require('express-validation')
const {
   baseRateLimiting
} = require('./../../middleware/rateLimiter')


module.exports = function() {
   controller = new controller();

   router.use((req, res, next) => next()); //init

   // [GET]
   router.get('/', baseRateLimiting, controller.getBusinesses)
   router.get(
      '/id/:businessID',
      validate(validator.getBusiness), baseRateLimiting,
      controller.getBusiness
   )
   router.get('/id/:businessID/reviews', baseRateLimiting, controller.businessReviews)
   router.get('/id/:businessID/photos', baseRateLimiting, controller.businessPhotos)
   router.get(
      '/id/:businessID/reviews/:reviewID',
      validate(validator.getReview), baseRateLimiting,
      controller.businessReview
   )
   router.get('/id/:businessID/photos/:photoID', baseRateLimiting, controller.businessPhoto)

   router.get('/categories', baseRateLimiting, controller.getCategories)
   router.get(
      '/categories/:category/sub-categories',
      validate(validator.getSubCategories), baseRateLimiting,
      controller.getSubCategories
   )

   //[PATCH]
   router.patch(
      '/id/:businessID',
      validate(validator.editBusiness), baseRateLimiting,
      controller.editBusiness
   )
   router.patch(
      '/id/:businessID/reviews/:reviewID',
      validate(validator.businessReviewEdit), baseRateLimiting,
      controller.editReview
   )
   router.patch(
      '/id/:businessID/photos/:photoID',
      validate(validator.businessPhotoEdit), baseRateLimiting,
      controller.editPhoto
   )
   router.patch(
      '/categories/:category',
      validate(validator.editCategory), baseRateLimiting,
      controller.editCategory
   )


   //[POST]
   router.post(
      '/',
      validate(validator.createdBusiness), baseRateLimiting,
      controller.createBusiness
   )
   router.post(
      '/id/:businessID/reviews',
      validate(validator.businessReview), baseRateLimiting,
      controller.createBusinessReview
   )
   router.post(
      '/id/:businessID/photos',
      validate(validator.businessPhoto),
      controller.createBusinessPhoto
   )
   router.post(
      '/categories',
      validate(validator.category), baseRateLimiting,
      controller.createCategory
   )
   router.post(
      '/categories/:category/sub-categories',
      validate(validator.subCategory), baseRateLimiting,
      controller.createSubCategory
   )

   // [DELETE]
   router.delete(
      '/id/:businessID',
      validate(validator.deleteBusiness), baseRateLimiting,
      controller.deleteBusiness
   )
   router.delete(
      '/id/:businessID/photos/:photoID',
      validate(validator.deletePhoto), baseRateLimiting,
      controller.deletePhoto
   )
   router.delete(
      '/id/:businessID/reviews/:reviewID',
      validate(validator.deleteReview), baseRateLimiting,
      controller.deleteReview
   )
   router.delete(
      '/categories/:category/',
      validate(validator.deleteCategory), baseRateLimiting,
      controller.deleteCategory
   );
   router.delete(
      '/categories/:category/sub-categories/:subCategory',
      validate(validator.deleteCategory), baseRateLimiting,
      controller.deleteSubCategory
   );



   router.use('*', (req, res) => res.json({ err: `Oh nose, ${req.originalUrl} doesn't exist` }))
   return router;
}

