let router = require('express').Router();
let controller = require('./logic');
let validator = require('./validator');
let validate = require('express-validation')


module.exports = function() {

   controller = new controller();

   router.use((req, res, next) => next()); //init

   // [GET] section
   router.get('/', controller.getUsers)
   router.get('/name/:owner', controller.getUsers)
   router.get('/name/:owner/owned-businesses', validate(validator.ownedBusinesses), controller.ownedBusinesses)
   router.get('/name/:owner/reviews', validate(validator.ownedBusinesses), controller.userReviews)
   router.get('/name/:owner/photos', validate(validator.ownedBusinesses), controller.userPhotos)

   //[POST] section
   router.post('/', validate(validator.createUser), controller.createUser)


   //[PATCH] section

   //[DELETE] section

   router.use('*', (req, res) => res.json({ err: `Oh nose, ${req.originalUrl} doesn't exist` }))

   return router;
}

