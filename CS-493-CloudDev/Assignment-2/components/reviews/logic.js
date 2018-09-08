let valid = require('./validator')
let boom = require('boom')
let uuid = require('uuid/v4')
let SQL = require('./../../MySQL/sql')
let self = null;

const databaseName = 'Cloud'
const tableName = 'Reviews'
module.exports = class reviewLogic extends SQL {
   constructor() {
      super(databaseName, tableName)
      self = this;
   }

   // ([GET])
   async getReview(req, res) {
      let { Result, Err } = await self.readById('Reviews', 'reviewID', req.params.reviewID)
      self.respond(Result, Err, res)
   }


   async getReviews(req, res) {
      let { Result, Err } = await self.readAll()
      self.respond(Result, Err, res, req)
   }

   // ([PATCH])
   async editReview(req, res) {
      let owner = req.body.owner;
      req.body.dollar = req.body.cost;
      delete req.body.cost
      delete req.body.owner

      let { keys, escapes, vals } = self.pullObjectKeysAndValues(req.body)
      let updateString = self.mergeKeysAndEscapes(keys, escapes)
      vals.push(req.params.reviewID)

      let { Result, Err } = await self.update(updateString, `\`reviewID\` = ?`, vals)
      self.respond(Result, Err, res)

   }

   // ([POST])
   async createReview(req, res) {
      let { Result, Err } = await self.create(
         `\`owner\`, \`business\`,\`star\`, \`dollar\`, \`message\``,
         `?,?,?,?,?`,
         [req.body.owner, req.body.business, req.body.stars, req.body.cost, req.body.message])
      self.respond(Result, Err, res)
   }


   // ([DELETE])
   async deleteReview(req, res) {
      let { Result, Err } = await self.delete(`\`reviewID\` = ?`, [req.params.reviewID])
      self.respond(Result, Err, res)
   }
}