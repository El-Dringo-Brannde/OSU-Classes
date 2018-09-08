let valid = require('./validator')
let boom = require('boom')
let uuid = require('uuid/v4')
let SQL = require('./../../MySQL/sql')
let self = null;

const databaseName = 'Cloud'
const tableName = 'Businesses'
module.exports = class businessController extends SQL {
   constructor() {
      super(databaseName, tableName)
      self = this;
   }

   //GET Section
   async getBusinesses(req, res) {
      let { Result, Err } = await self.readAll()
      self.respond(Result, Err, res, req)
   }

   async getBusiness(req, res) {
      let { Result, Err } = await self.readById('Businesses', 'businessID', req.params.businessID)
      self.respond(Result, Err, res)
   }

   // [PATCH] section
   async editBusiness(req, res) {
      let owner = req.body.owner;
      delete req.body.owner

      let { keys, escapes, vals } = self.pullObjectKeysAndValues(req.body)
      let updateString = self.mergeKeysAndEscapes(keys, escapes)
      vals.push(req.params.businessID)

      let { Result, Err } = await self.update(updateString, `\`businessID\` = ?`, vals)
      self.respond(Result, Err, res);
   }

   // [DELETE] Section
   async deleteBusiness(req, res) {
      let { Result, Err } = await self.getUser(req.query.owner)
      if (!Err && Result.length != 0) {
         let { Result, Err } = await self.delete(`businessID = ?`, [req.params.businessID])
         res.json(Result)
      } else {
         if (Err)
            res.json(Err)
         else
            res.json(boom.badRequest('User not found'))
      }
   }


   // [POST]
   async createBusiness(req, res) {
      let { Result, Err } = await self.getUser(req.body.owner)
      if (!Err && Result.length != 0) {
         let { Result, Err } = await self.create(
            `\`name\`, \`owner\`, \`address\`, \`city\`, \`state\`, \`zip\`, \`phone\`, \`email\``,
            `'${req.body.name}', '${req.body.owner}', '${req.body.address}', '${req.body.city}', '${req.body.state}'
            , '${req.body.zip}', '${req.body.phone}', '${req.body.email}'`)
         res.json(Result)
      } else {
         if (Err)
            res.json(Err)
         else
            res.json(boom.badRequest('User not found'))
      }
   }
}