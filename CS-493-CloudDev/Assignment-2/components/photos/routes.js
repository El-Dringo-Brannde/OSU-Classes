let router = require('express').Router();
let controller = require('./logic');
let validator = require('./validator');
let validate = require('express-validation')

module.exports = function() {
   controller = new controller();


   //[GET]
   router.get('/', controller.getPhotos)
   router.get('/:photoID', controller.getPhoto)

   //[PATCH]
   router.patch('/:photoID', validate(validator.businessPhotoEdit), controller.editPhoto)

   //[POST]
   router.post('/', validate(validator.businessPhoto), controller.createBusinessPhoto)

   //[DELETE]
   router.delete('/:photoID', validate(validator.deletePhoto), controller.deletePhoto)

   return router
}

