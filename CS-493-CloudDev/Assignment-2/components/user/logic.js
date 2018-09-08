let valid = require('./validator')
let SQL = require('./../../MySQL/sql')
let boom = require('boom')
let uuid = require('uuid/v4')


let self = null;

const databaseName = 'Cloud'
const tableName = 'Users'
module.exports = class userLogic extends SQL {
   constructor() {
      super(databaseName, tableName)
      self = this;
   }

   async getUsers(req, res) {
      let { Result, Err } = await self.read()
      self.respond(Result, Err, res, req)
   }

   async createUser(req, res) {
      let { Result, Err } = await self.create(`\`name\`, \`type\``,
         '?,?',
         [req.body.owner, req.body.type])
      self.respond(Result, Err, res)
   }

   async ownedBusinesses(req, res) {
      let { Result, Err } = await self.readInTable('*', 'Businesses',
         `\`owner\` = ?`, [req.params.owner])
      self.respond(Result, Err, res)
   }

   async userReviews(req, res) {
      let { Result, Err } = await self.readInTable('*', 'Reviews',
         `\`owner\` = ?`, [req.params.owner])
      self.respond(Result, Err, res, req)
   }

   async userPhotos(req, res) {
      let { Result, Err } = await self.readInTable('*', 'Photos',
         `\`owner\` = ?`, [req.params.owner])
      self.respond(Result, Err, res, req)
   }

   // ([DELETE])
   async deleteUser(req, res) {
      let { Result } = await self.getUser(req.params.owner)
      if (Result.length != 0) {
         let result = await self.delete(`\`Users\`.\`name\` = '${req.params.owner}'`)
         res.json(result)
      } else
         res.json(boom.badRequest('user not found'))
   }
}