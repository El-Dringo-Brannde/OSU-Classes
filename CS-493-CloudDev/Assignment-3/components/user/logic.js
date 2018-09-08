const valid = require('./validator')
const mongodb = require('./../../mongoDB/mongo')
const boom = require('boom')

const bcrypt = require('bcrypt')
const saltRounds = 10

let self = null;

const databaseName = 'CS493'
const collectionName = 'Users'

const { generateAuthToken, requireAuthentication } = require('./../../middleware/auth')

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
      const userCheck = await self.read({ owner: req.body.owner })

      if (userCheck.length != 0)
         res.status(401).json({ message: `Username already taken` })
      else {
         req.body.password = bcrypt.hashSync(req.body.password, saltRounds)
         await self.create(req.body)
         let user = await self.read(req.body)
         user = user[0]

         user.token = await generateAuthToken(user.owner)
         res.json(user)
      }
   }

   async login(req, res) {
      let user = await self.read({ owner: req.body.owner })
      if(user.length != 0)
            user = user[0]
      else {
            res.status(401).json({ message: `Not authorized` })   
            return
      }
      const password = bcrypt.compareSync(req.body.password, user.password)
      if (password) {
         user.token = await generateAuthToken(user.owner)
         delete user.password
         res.json(user)
      } else
         res.status(401).json({ message: `Not authorized` })
   }

   async ownedBusinesses(req, res) {
      let agg = self.aggs.projectArray('owner', req.params.owner, 'owns')
      let businesses = await self.aggregate(agg)
      if(req.user != req.params.owner)
            res.json(boom.badRequest('Restricted Access'))   
      if (req.query.page && req.query.limit) {
         self.paginate(req, businesses, res)
      } else
         res.json(businesses)
   }

   async userReviews(req, res) {
      let agg = self.aggs.projectArray('owner', req.params.owner, 'reviews')
      let reviews = await self.aggregate(agg)
      if(req.user != req.params.owner)
            res.json(boom.badRequest('Restricted Access'))   
      if (reviews.length == 0 )
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

      if(req.user != req.params.owner)
            res.json(boom.badRequest('Restricted Access'))   
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