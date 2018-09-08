let router = require('express').Router();
let controller = require('./logic');
let validator = require('./validator');
let validate = require('express-validation')


module.exports = function() {
   controller = new controller();

   router.use((req, res, next) => next()); //init

   // [GET]
   router.get('/', controller.getBusinesses)
   router.get('/id/:businessID', validate(validator.getBusiness), controller.getBusiness)
   router.get('/id/:businessID/reviews', controller.businessReviews)
   router.get('/id/:businessID/photos', controller.businessPhotos)
   router.get('/id/:businessID/reviews/:reviewID', validate(validator.getReview), controller.businessReview)
   router.get('/id/:businessID/photos/:photoID', controller.businessPhoto)

   router.get('/categories', controller.getCategories)
   router.get('/categories/:category/sub-categories', validate(validator.getSubCategories), controller.getSubCategories)

   //[PATCH]
   router.patch('/id/:businessID', validate(validator.editBusiness), controller.editBusiness)
   router.patch('/id/:businessID/reviews/:reviewID', validate(validator.businessReviewEdit), controller.editReview)
   router.patch('/id/:businessID/photos/:photoID', validate(validator.businessPhotoEdit), controller.editPhoto)
   router.patch('/categories/:category', validate(validator.editCategory), controller.editCategory)


   //[POST]
   router.post('/', validate(validator.createdBusiness), controller.createBusiness)
   router.post('/id/:businessID/reviews', validate(validator.businessReview), controller.createBusinessReview)
   router.post('/id/:businessID/photos', validate(validator.businessPhoto), controller.createBusinessPhoto)
   router.post('/categories', validate(validator.category), controller.createCategory)
   router.post('/categories/:category/sub-categories', validate(validator.subCategory), controller.createSubCategory)

   // [DELETE]
   router.delete('/id/:businessID', validate(validator.deleteBusiness), controller.deleteBusiness)
   router.delete('/id/:businessID/photos/:photoID', validate(validator.deletePhoto), controller.deletePhoto)
   router.delete('/id/:businessID/reviews/:reviewID', validate(validator.deleteReview), controller.deleteReview)
   router.delete('/categories/:category/', validate(validator.deleteCategory), controller.deleteCategory);
   router.delete('/categories/:category/sub-categories/:subCategory', validate(validator.deleteCategory), controller.deleteSubCategory);



   router.use('*', (req, res) => res.json({ err: `Oh nose, ${req.originalUrl} doesn't exist` }))
   return router;
}

