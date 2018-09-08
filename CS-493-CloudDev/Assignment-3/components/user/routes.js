const router = require('express').Router();
const validator = require('./validator');
const validate = require('express-validation')
const { requireAuthentication } = require('./../../middleware/auth')
const {
   baseRateLimiting,
   apiKeyLimiting
} = require('./../../middleware/rateLimiter')

let controller = require('./logic');


module.exports = function() {
   controller = new controller();

   router.use((req, res, next) => next()); //init

   // [GET] section
   router.get('/', baseRateLimiting, controller.getUsers)
   router.get('/name/:owner', baseRateLimiting, controller.getUsers)
   router.get('/name/:owner/owned-businesses',
      validate(validator.ownedBusinesses), requireAuthentication, apiKeyLimiting,
      controller.ownedBusinesses)

   router.get('/name/:owner/reviews',
      validate(validator.ownedBusinesses), requireAuthentication, apiKeyLimiting,
      controller.userReviews)

   router.get('/name/:owner/photos',
      validate(validator.ownedBusinesses), requireAuthentication, apiKeyLimiting,
      controller.userPhotos)

   //[POST] section
   router.post('/',
      validate(validator.createUser), baseRateLimiting,
      controller.createUser)
   router.post('/login',
      validate(validator.login), baseRateLimiting,
      controller.login)


   //[PATCH] section

   //[DELETE] section

   router.use('*', (req, res) => res.json({ err: `Oh nose, ${req.originalUrl} doesn't exist` }))

   return router;
}

