let crud = require('./CRUD');


module.exports = class SQL extends crud {
   constructor(db, collName) {
      super(db, collName)
      this.url = 'https://cs493-assignment1.herokuapp.com';
   }

   /*  
      Helper Functions
   */
   respond(Result, Err, res, req) {
      if (Err)
         res.json(Err)
      if (Result.length != 0 && req && req.query.page && req.query.limit)
         this.paginate(req, Result, res)
      else
         res.json(Result)
   }

   pullObjectKeysAndValues(obj) {
      let escape = '?'
      for (var i in Object.keys(obj).length - 1)
         escape += ',?'

      return {
         keys: Object.keys(obj),
         escapes: escape,
         vals: Object.values(obj)
      }
   }

   mergeKeysAndEscapes(keys, escapes) {
      let updateString = ''
      for (var i of keys)
         updateString += `\`${i}\` = ${escapes}, `
      updateString = updateString.slice(0, updateString.length - 2) // get rid of last ', '
      return updateString
   }

   paginate(req, data, res) {
      let originalUrl = req.originalUrl.split('?')[0]
      let query = req.query
      data = data.slice(query.limit * (query.page - 1), query.limit * query.page)
      let respObj = {
         prevPage: `${this.url}${originalUrl}/?limit=${query.limit}&page=${parseInt(query.page) - 1}`,
         nextPage: `${this.url}${originalUrl}/?limit=${query.limit}&page=${parseInt(query.page) + 1}`,
         data: data
      }
      res.json(respObj)
   }

   /* End Helpers */

   async getUser(owner) {
      return await this.readInTable(`*`, '`Users`', `name = ?`, [owner])
   }

   async readAll() {
      return await this.read(`*`)
   }

   async readById(table, idKey, id) {
      return await this.readInTable('*', table, `\`${idKey}\` = ?`, [id])
   }

   async getOwner(owner, table) {
      return await this.readInTable(`*`, `\`Users\`, 
         \`${table}\``,
         `\`Users\`.\`name\` = '?' AND \`Businesses\`.\`owner\` = \`Users\`.\`name\``
         , [owner])
   }
}