let valid = require('./validator')
let mongodb = require('./../../mongoDB/mongo')
let boom = require('boom')


let self = null;

const databaseName = 'CS493'
const collectionName = 'Users'
module.exports = class userController extends mongodb {
   constructor() {
      super(databaseName, collectionName)
      self = this;
   }

   async getUsers(req, res) {
      let users = await self.readAll()
      if (req.query.page && req.query.limit) {
         self.paginate(req, users, res)
      } else
         res.json(users)
   }

   async createUser(req, res) {
      req.body.owns = []
      req.body.reviews = []
      req.body.photos = []
      let created = await self.create(req.body)
      let user = await self.read(req.body)
      res.json(user)
   }

   async ownedBusinesses(req, res) {
      let agg = self.aggs.projectArray('owner', req.params.owner, 'owns')
      let businesses = await self.aggregate(agg)
      if (req.query.page && req.query.limit) {
         self.paginate(req, businesses, res)
      } else
         res.json(businesses)
   }

   async userReviews(req, res) {
      let agg = self.aggs.projectArray('owner', req.params.owner, 'reviews')
      let reviews = await self.aggregate(agg)
      if (reviews.length == 0)
         res.json(boom.badRequest('user not found'))
      else {
         if (req.query.page && req.query.limit) {
            self.paginate(req, reviews[0].reviews, res)
         } else
            res.json(reviews)
      }
   }

   async userPhotos(req, res) {
      let agg = self.aggs.projectArray('owner', req.params.owner, 'photos')
      let photos = await self.aggregate(agg)

      if (photos.length == 0)
         res.json(boom.badRequest('user not found'))
      else {
         if (req.query.page && req.query.limit) {
            self.paginate(req, photos[0].photos, res)
         } else
            res.json(photos)
      }
   }
}