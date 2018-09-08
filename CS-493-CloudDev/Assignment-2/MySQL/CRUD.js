let mysql = require('mysql2/promise')

module.exports = class CRUD {
   constructor(db, tableName) {
      this.connectToDB(db)
      this.table = tableName
   }

   async connectToDB(db) {
      this.sql = await mysql.createConnection({
         host: process.env.NODE_ENV ? process.env.DB_HOST : 'trump-tweet-tracker.cz7j0jjdypdh.us-east-1.rds.amazonaws.com',
         password: process.env.NODE_ENV ? process.env.MYSQL_PASSWORD : '8HsRdCVWPGD0',
         port: process.env.MYSQL_PORT,
         user: process.env.MYSQL_USER || 'cs458_data_viz',
         database: process.env.MYSQL_DB || db,
      })
   }

   async safeExec(query, escaped) {
      try {
         console.log(query, escaped)
         let result = await this.sql.execute(query, escaped)
         return { Result: result[0] }
      } catch (err) {
         return { Err: err }
      }
   }

   async create(columns, values, escaped) {
      return await this.safeExec(`INSERT INTO ${this.table} (${columns}) VALUES (${values})`, escaped)
   }

   async createInTable(columns, table, values, escaped) {
      return await this.safeExec(`INSERT INTO ${table} (${columns}) VALUES (${values})`, escaped)
   }

   async read(columns = `*`, escaped) {
      return await this.safeExec(`Select ${columns} FROM ${this.table}`, escaped)
   }

   async readInTable(columns = `*`, table = `${this.table}`, conditions = '', escaped) {
      return await this.safeExec(`Select ${columns} FROM ${table} WHERE ${conditions}`, escaped)
   }

   async update(columns, conditions, escaped) {
      return await this.safeExec(`UPDATE ${this.table} SET ${columns} WHERE ${conditions}`, escaped)
   }

   async delete(conditions, escaped) {
      return await this.safeExec(`DELETE FROM ${this.table} WHERE ${conditions}`, escaped)
   }

   async deleteInTable(table, conditions, escaped) {
      return await this.safeExec(`DELETE FROM ${table} WHERE ${conditions}`, escaped)
   }
};