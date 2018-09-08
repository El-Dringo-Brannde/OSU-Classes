let valid = require('./validator')
let mongodb = require('./../../mongoDB/mongo')
let mongoID = require('mongodb').ObjectID
let self = null;
let boom = require('boom')
let uuid = require('uuid/v4')

const databaseName = 'CS493'
const collectionName = 'Businesses'
module.exports = class businessController extends mongodb {
   constructor() {
      super(databaseName, collectionName)
      self = this;
   }

   buildUserLink(businessID, array, id) {
      return {
         [array]: {
            uuid: id,
            url: `${self.url}/businesses/id/${businessID}/${array}/${id}`
         }
      }
   }

   async checkReview(business, user) {
      let safe = true
      for (var i of business.reviews) {
         for (var j of user.reviews) {
            if (i.uuid == j.uuid)
               safe = false

         }
      }
      return safe
   }

   async checkCategories(req, res) {
      self.switchCollection('Category')
      for (var i of req.body.category) {
         let category = await self.read({ "category": i })
         if (category.length == 0)
            res.json(boom.badRequest('Category not found'))
         else
            await self.checkSubcategories(i, req, res)
      }
      self.switchCollection('Businesses')
   }

   async checkSubcategories(i, req, res) {
      for (var j of req.body.subCategory) {
         let category = await self.read({ "category": i, "subCategories": j })
         if (category.length == 0)
            res.json(boom.badRequest('subCategory not found'))
      }
   }

   //GET Section
   async getUser(owner) {
      self.switchCollection('Users')
      let users = await self.read({ owner: owner })
      return users[0]
   }

   async getBusinesses(req, res) {
      let businesses = await self.readAll()
      if (req.query.page && req.query.limit) {
         self.paginate(req, businesses, res)
      } else
         res.json(businesses)
   }

   async getBusiness(req, res) {
      let business = await self.readById(req.params.businessID)
      res.json(business)
   }

   async getCategories(req, res) {
      self.switchCollection('Category')
      let results = await self.readAll()
      res.json(results)
      self.switchCollection('Businesses')
   }

   async getSubCategories(req, res) {
      self.switchCollection('Category')
      let agg = self.aggs.projectArray('category', req.params.category, 'subCategories')
      let results = await self.aggregate(agg)
      res.json(results)
      self.switchCollection('Businesses')
   }

   async businessReviews(req, res) {
      let agg = self.aggs.matchId(req.params.businessID, 'reviews')
      let result = await self.aggregate(agg)

      if (result.length != 0 && req.query.page && req.query.limit) {
         self.paginate(req, result[0].reviews, res)
      } else
         res.json(result)
   }

   async businessPhotos(req, res) {
      let agg = self.aggs.matchId(req.params.businessID, 'photos')
      let result = await self.aggregate(agg)

      if (result.length != 0 && req.query.page && req.query.limit) {
         self.paginate(req, result[0].photos, res)
      } else
         res.json(result)
   }

   async businessReview(req, res) {
      let agg = self.aggs.pullObjFromArray('_id', self.mongo_ID(req.params.businessID), 'reviews', req.params.reviewID)
      let result = await self.aggregate(agg)
      res.json(result)
   }

   async businessPhoto(req, res) {
      let agg = self.aggs.pullObjFromArray('_id', self.mongo_ID(req.params.businessID), 'photos', req.params.photoID)
      let result = await self.aggregate(agg)
      res.json(result)
   }


   // [PATCH] section
   async editBusiness(req, res) {
      let business = await self.readById(req.params.businessID)
      if (business.length == 0 || business[0].owner != req.body.owner)
         res.json(boom.badRequest('Does not own business'))
      else {
         let { result } = await self.update({ _id: self.mongo_ID(req.params.businessID) }, req.body)

         if (result.nModified === 1) {
            let result = await self.readById(req.params.businessID)
            res.json(result[0])
         } else
            res.json(boom.badRequest('business not found'))
      }
   }


   async editReview(req, res) {
      let user = await self.getUser(req.body.owner)
      self.switchCollection('Businesses')
      let agg = await self.aggs.pullObjFromArray('_id', req.params.businessID,
         'reviews', req.params.reviewID)
      let review = await self.aggregate(agg) // get review
      if (review.length == 0) {
         res.json(boom.badRequest('bad request'))
         return
      }

      review = review[0].reviews
      if (user && review.owner == user.owner) {

         let mergedObject = Object.assign({}, review, req.body);
         await self.pullFromArray('_id', self.mongo_ID(req.params.businessID),
            'reviews', req.params.reviewID)

         let result = await self.addToSet({ _id: self.mongo_ID(req.params.businessID) }, { reviews: mergedObject })
         res.json(result)
      } else
         res.json(boom.badRequest('User not Found'))
   }

   async editPhoto(req, res) {
      let user = await self.getUser(req.body.owner)
      self.switchCollection('Businesses')
      let agg = await self.aggs.pullObjFromArray('_id', req.params.businessID,
         'photos', req.params.photoID)
      let photo = await self.aggregate(agg) // get photo
      if (photo.length == 0) {
         res.json(boom.badRequest('bad request'))
         return
      }

      photo = photo[0].photos
      if (user && photo.owner == user.owner) {

         let mergedObject = Object.assign({}, photo, req.body);
         await self.pullFromArray('_id', self.mongo_ID(req.params.businessID),
            'photos', req.params.photoID)

         let result = await self.addToSet({ _id: self.mongo_ID(req.params.businessID) }, { photos: mergedObject })
         res.json(result)
      } else
         res.json(boom.badRequest('User not Found'))
   }

   async editCategory(req, res) {
      let user = await self.getUser(req.body.owner)
      self.switchCollection('Category')
      let category = await self.read({ category: req.params.category })

      if (user && category.length != 0 && user.owner == category[0].owner) {
         delete req.body.owner
         let result = await self.update({ category: req.params.category }, { category: req.body.category })
         res.json(result)
      } else
         res.json(boom.badRequest('Request error'))
   }


   // [DELETE] Section
   async deletePhoto(req, res) {
      let agg = await self.aggs.pullObjFromArray('_id', req.params.businessID,
         'photos', req.params.photoID)
      let photo = await self.aggregate(agg) // get photo
      if (photo.length == 0) {
         res.json(boom.badRequest('bad request'))
         return
      }

      photo = photo[0].photos
      let user = await self.getUser(req.body.owner)

      if (photo.owner == user.owner) {
         await self.pullFromArray('owner', req.body.owner, 'photos', req.params.photoID)

         self.switchCollection('Businesses')
         let result = await self.pullFromArray('_id', self.mongo_ID(req.params.businessID),
            'photos', req.params.photoID)
         res.json(result)
      } else
         res.json(boom.badRequest("Doesn't own photo"))
      self.switchCollection('Businesses')
   }

   async deleteReview(req, res) {
      let agg = await self.aggs.pullObjFromArray('_id', self.mongo_ID(req.params.businessID),
         'reviews', req.params.reviewID)
      let review = await self.aggregate(agg) // get photo
      if (review.length == 0) {
         res.json(boom.badRequest('bad request'))
         return
      }

      review = review[0].reviews
      let user = await self.getUser(req.body.owner)
      console.log(review, user)
      if (review.owner == user.owner) {
         let result = await self.pullFromArray('owner', req.body.owner, 'reviews',
            req.params.reviewID)

         self.switchCollection('Businesses')
         result = await self.pullFromArray('_id', self.mongo_ID(req.params.businessID),
            'reviews', req.params.reviewID)

         res.json(result)
      } else
         res.json(boom.badRequest("Doesn't own photo"))
      self.switchCollection('Businesses')
   }


   async deleteBusiness(req, res) {
      let business = await self.readById(req.params.businessID)

      if (business.length != 0 && business[0].owner == req.body.owner) {
         self.switchCollection('Users')
         await self.pullFromArray('owner', req.body.owner, 'owns', business[0].uuid)

         self.switchCollection('Businesses')
         let deleted = await self.delete({ _id: mongoID(req.params.businessID) })

         self.switchCollection('Users')
         let users = await self.getUser(req.body.owner)
         res.json(users)
      } else
         boom.badRequest("Owner not found for business")
      self.switchCollection('Businesses')
   }

   async deleteCategory(req, res) {
      self.switchCollection('Category')
      let category = await self.read({ category: req.params.category })
      if (category.length != 0 && category[0].owner == req.query.owner) {
         let result = await self.delete({ category: req.params.category })
         res.json(result);
      } else
         res.json(boom.badRequest('Request Error'))
   }

   async deleteSubCategory(req, res) {
      self.switchCollection('Category')
      let category = await self.read({ category: req.params.category, subCategories: req.params.subCategory })

      if (category.length != 0 && category[0].owner == req.query.owner) {
         let result = await self.mongo.update({ category: req.params.category }, { $pull: { 'subCategories': req.params.subCategory } })
         res.json(result);
      } else
         res.json(boom.badRequest('Request Error'))
   }

   // [POST]
   async createBusinessReview(req, res) {
      let user = await self.getUser(req.body.owner)
      self.switchCollection('Businesses')
      let business = await self.readById(req.params.businessID)
      if (business.length == 0) {
         res.json(boom.badRequest('bad request'))
         return
      }

      let reviewed = await self.checkReview(business[0], user)

      if (user && business.length != 0 && reviewed) {
         req.body.uuid = uuid();

         let result = await self.addToUserAndBusinessArray(req.body.owner, req.params.businessID,
            self.buildUserLink(req.params.businessID, 'reviews', req.body.uuid),
            { reviews: req.body })
         business = await self.readById(req.params.businessID)
         res.json(business)
      } else
         res.json(boom.badRequest('bad request'))

      self.switchCollection('Businesses')
   }

   async createBusinessPhoto(req, res) {
      if (await self.getUser(req.body.owner)) {
         req.body.uuid = uuid();

         let result = await self.addToUserAndBusinessArray(req.body.owner, req.params.businessID,
            self.buildUserLink(req.params.businessID, 'photos', req.body.uuid),
            { photos: req.body })
         let business = await self.readById(req.params.businessID)
         res.json(business)
      } else
         res.json(boom.badRequest("User not found"));

      self.switchCollection('Businesses')
   }


   async createCategory(req, res) {
      let user = await self.getUser(req.body.owner)

      if (!user || user.type != 'admin')
         res.json(boom.badRequest('User permission error'))
      else {
         req.body.subCategories = []
         self.switchCollection('Category')
         let { ops } = await self.create(req.body)
         res.json(ops)
         self.switchCollection('Businesses')
      }
   }

   async createSubCategory(req, res) {
      let users = await self.getUser(req.body.owner)

      self.switchCollection('Category')
      let category = await self.read({ category: req.params.category })
      delete req.body.owner

      if (users && users.type == 'admin' && category.length != 0) {
         let ops = await self.addToSet({ category: req.params.category },
            { subCategories: req.body.subCategory })
         let result = await self.read({ category: req.params.category })
         res.json(result)
      } else
         res.json(boom.badRequest('Bad Request Data').output)
      self.switchCollection('Businesses')
   }

   async createBusiness(req, res) {
      req.body.reviews = [];
      req.body.photos = [];
      req.body.uuid = uuid();
      let user = await self.getUser(req.body.owner)

      await self.checkCategories(req, res)

      if (user) {
         self.switchCollection('Businesses')
         let { ops } = await self.create(req.body)
         ops = ops[0] // get user out of the array
         self.switchCollection('Users')
         let userObj = {
            uuid: ops.uuid,
            url: `${self.url}/businesses/id/${ops._id}`
         }
         await self.addToSet({ owner: 'dringb' }, { owns: userObj })
         res.json(ops)
      } else
         res.json(boom.badRequest('No user found').output)

      self.switchCollection('Businesses')
   }
}