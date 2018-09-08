let router = require('express').Router();
let controller = require('./logic');
let validator = require('./validator');
let validate = require('express-validation')

module.exports = function() {
   controller = new controller();


   //[GET]
   router.get('/', controller.getCategories)

   //[PATCH]
   router.patch('/:category', controller.editCategory)

   // [POST]
   router.post('/', validate(validator.category), controller.createCategory)

   // [ DELETE ]
   router.delete('/:category/', validate(validator.deleteCategory), controller.deleteCategory);


   return router;
}