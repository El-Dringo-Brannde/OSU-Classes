const rate = require('express-rate')
const redis = require('redis')
const client = process.env.NODE_ENV == 'prod' ? redis.createClient({
   host: '172.16.231.8'
}) : redis.createClient();
const redisHandler = new rate.Redis.RedisRateHandler({ client: client });

const moment = require('moment')

const baseRateLimiting = rate.middleware({
   handler: redisHandler,
   limit: 5,
   interval: 20,
   onLimitReached: function(req, res, rate, limit, resetTime, next) {
      // HTTP code 420 from http://mehack.com/inventing-a-http-response-code-aka-seriously
      res.status(420).json({ error: `Base Rate limit exceeded. Take a chill for: ${moment(resetTime).diff(moment(), 'seconds')} seconds` });
   }
});

const apiKeyLimiting = rate.middleware({
   handler: redisHandler,
   limit: 3,
   interval: 20,
   getRemoteKey: function(req) {
      const authHeader = req.get('Authorization') || '';
      const authHeaderParts = authHeader.split(' ');
      const token = authHeaderParts[0] === 'Bearer' ? authHeaderParts[1] : null;
      return token;
   },
   onLimitReached: function(req, res, rate, limit, resetTime, next) {
      // HTTP code 420 from http://mehack.com/inventing-a-http-response-code-aka-seriously
      res.status(420).json({ error: `API Key Rate limit exceeded. Slow down for ${moment(resetTime).diff(moment(), 'seconds')} seconds homie ` });
   }
})


exports.baseRateLimiting = baseRateLimiting
exports.apiKeyLimiting = apiKeyLimiting
exports.getRedisClient = new rate.Redis.RedisRateHandler({ client: client });