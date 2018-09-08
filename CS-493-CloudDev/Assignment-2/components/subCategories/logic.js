let valid = require('./validator')
let boom = require('boom')
let uuid = require('uuid/v4')
let SQL = require('./../../MySQL/sql')
let self = null;

const databaseName = 'Cloud'
const tableName = 'subCategories'
module.exports = class subCategoryLogic extends SQL {
   constructor() {
      super(databaseName, tableName);
      self = this;
   }


   // ([GET])
   async getSubCategories(req, res) {
      let { Result, Err } = await self.readAll('*')
      self.respond(Result, Err, res, req)
   }

   // ([PATCH])
   editCategory(req, res) {

   }

   // ([POST])
   async createSubCategory(req, res) {
      let { Result, Err } = await self.createInTable(
         ` \`name\`, \`owner\``,
         'subCategories',
         `?,?`,
         [req.body.subCategory, req.body.owner])
      self.respond(Result, Err, res)
   }

   //([DELETE])
   async deleteSubCategory(req, res) {
      let { Result, Err } = await self.delete(`\`name\` = ?`, [req.params.subCategory])
      self.respond(Result, Err, res)
   }

}
