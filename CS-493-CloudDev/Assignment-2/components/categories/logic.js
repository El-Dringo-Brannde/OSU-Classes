let valid = require('./validator')
let boom = require('boom')
let uuid = require('uuid/v4')
let SQL = require('./../../MySQL/sql')
let self = null;

const databaseName = 'Cloud'
const tableName = 'Categories'
module.exports = class categoryLogic extends SQL {
   constructor() {
      super(databaseName, tableName);
      self = this;
   }


   // ([GET])
   async getCategories(req, res) {
      let { Result, Err } = await self.readAll()
      self.respond(Result, Err, res, req)
   }

   // ([PATCH])
   async editCategory(req, res) {
      let owner = req.body.owner;
      req.body.name = req.body.category;
      delete req.body.category;
      delete req.body.owner

      let { keys, escapes, vals } = self.pullObjectKeysAndValues(req.body)
      let updateString = self.mergeKeysAndEscapes(keys, escapes)
      vals.push(req.params.category)

      let { Result, Err } = await self.update(updateString, `\`name\` = ?`, vals)
      self.respond(Result, Err, res);
   }

   // ([POST])
   async createCategory(req, res) {
      let { Result, Err } = await self.create(
         ` \`name\`, \`owner\``,
         `?,?`,
         [req.body.category, req.body.owner])
      self.respond(Result, Err, res)
   }

   async createSubCategory(req, res) {
      let { Result, Err } = await self.createInTable(
         ` \`name\`, \`owner\``,
         'subCategories',
         `?,?`,
         [req.body.subCategory, req.body.owner])
      self.respond(Result, Err, res)
   }

   //([DELETE])
   async deleteCategory(req, res) {
      let { Result, Err } = await self.delete(`\`name\` = ?`, [req.params.category])
      self.respond(Result, Err, res)
   }
}
