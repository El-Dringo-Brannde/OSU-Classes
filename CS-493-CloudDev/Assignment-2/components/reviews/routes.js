let router = require('express').Router();
let controller = require('./logic');
let validator = require('./validator');
let validate = require('express-validation')


module.exports = function() {
   controller = new controller();

   // [GET]
   router.get('/', controller.getReviews)
   router.get('/:reviewID', controller.getReview)


   // [PATCH]
   router.patch('/:reviewID', validate(validator.businessReviewEdit), controller.editReview)

   // [POST]
   router.post('/', validate(validator.businessReview), controller.createReview)


   // [DELETE]
   router.delete('/:reviewID', validate(validator.deleteReview), controller.deleteReview)


   return router;
}