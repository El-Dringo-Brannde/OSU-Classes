let router = require('express').Router();
let controller = require('./logic');
let validator = require('./validator');
let validate = require('express-validation')


module.exports = function() {
   controller = new controller();

   router.use((req, res, next) => next()); //init

   // [GET]
   router.get('/', controller.getBusinesses)
   router.get('/id/:businessID', controller.getBusiness)


   //[PATCH]
   router.patch('/id/:businessID', validate(validator.editBusiness), controller.editBusiness)

   //[POST]
   router.post('/', validate(validator.createdBusiness), controller.createBusiness)

   // [DELETE]
   router.delete('/id/:businessID', validate(validator.deleteBusiness), controller.deleteBusiness)

   router.use('*', (req, res) => res.json({ err: `Oh nose, ${req.originalUrl} doesn't exist` }))
   return router;
}

