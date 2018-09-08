let valid = require('./validator')
let boom = require('boom')
let uuid = require('uuid/v4')
let SQL = require('./../../MySQL/sql')
let self = null;

const databaseName = 'Cloud'
const tableName = 'Photos'
module.exports = class photoLogic extends SQL {
   constructor() {
      super(databaseName, tableName);
      self = this;
   }

   // ([GET])
   async getPhoto(req, res) {
      let { Result, Err } = await self.readById('Photos', 'photoID', req.params.photoID)
      self.respond(Result, Err, res)
   }

   async getPhotos(req, res) {
      let { Result, Err } = await self.readAll()
      self.respond(Result, Err, res, req)
   }

   // ([PATCH])
   async editPhoto(req, res) {
      let owner = req.body.owner;
      delete req.body.owner

      let { keys, escapes, vals } = self.pullObjectKeysAndValues(req.body)
      let updateString = self.mergeKeysAndEscapes(keys, escapes)
      vals.push(req.params.photoID)

      let { Result, Err } = await self.update(updateString, `\`photoID\` = ?`, vals)
      self.respond(Result, Err, res)
   }

   // ([POST])
   async createBusinessPhoto(req, res) {
      let { Result, Err } = await self.create(
         `\`owner\`, \`business\`,\`image\`, \`caption\``,
         `?,?,?,?`,
         [req.body.owner, req.body.business, req.body.image, req.body.caption])
      self.respond(Result, Err, res)
   }

   // ([DELETE])
   async deletePhoto(req, res) {
      let { Result, Err } = await self.delete(`\`photoID\` = ?`, [req.params.photoID])
      self.respond(Result, Err, res)
   }

}