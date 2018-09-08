const app = require('express')();
const initBusinesses = require('./components/businesses/routes')
const initUsers = require('./components/user/routes')
const bodyParser = require('body-parser')
const commandLineArgs = require('command-line-args')
const rateLimit = require('express-rate-limit')

module.exports = class server {
   constructor() {
      this.mongo = null;
      this.onInit();
   }

   async onInit() {
      this.addMiddleware();
      await this.grabRoutes();
      let CLA = this.pullCLA()

      app.listen(CLA.port, () => console.log(`Server running at port ${CLA.port}`))
   }

   pullCLA() {
      const options = [
         { name: 'port', alias: 'p', type: Number }
      ]
      let args = commandLineArgs(options)
      args.port = args.port ? args.port : process.env.PORT
      return args
   }

   async grabRoutes() {
      app.use('/businesses', initBusinesses());
      app.use('/users', initUsers());
   }


   addMiddleware() {
      app.use(bodyParser.json())
      app.use(function(req, res, next) {
         res.header("Access-Control-Allow-Origin", "*");
         res.header("Access-Control-Allow-Headers", "Origin, X-Requested-With, Content-Type, Accept");
         next();
      });

      app.use(new rateLimit({ max: 20 }))

      app.use(function(err, req, res, next) {
         console.log(err)
         res.status(400).json(err);
         next()
      }); // error handler for validator
   }
}