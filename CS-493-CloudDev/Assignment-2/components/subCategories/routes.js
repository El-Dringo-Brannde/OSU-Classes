let router = require('express').Router();
let controller = require('./logic');
let validator = require('./validator');
let validate = require('express-validation')

module.exports = function() {
   controller = new controller();


   //[GET]
   router.get('/', controller.getSubCategories)


   //[PATCH]


   // [POST]
   router.post('/', controller.createSubCategory)


   // [ DELETE ]
   router.delete('/:subCategory', validate(validator.deleteCategory), controller.deleteSubCategory);


   return router;
}