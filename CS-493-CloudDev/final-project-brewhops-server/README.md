# CS493 Final Project

## Team Members:
* Billy Buffum
* Connor Christensen
* Annie Lei
* Brandon Dring

## Problem Description:
Ninkasi Brewing Company is based in Eugene, Oregon, producing and distributing nearly 100,000 barrels of beer each year across the United States and Canada. Ninkasi currently tracks brewery data using digital spreadsheets, a laborious, time consuming, and error prone process. Quality brewing requires the company to be detail-oriented, organize its data and provide timely actions in the brewing process. In order to maintain good quality control in their product and give the company room to scale its production, our team has been tasked with creating software that will improve the process of entering, storing and accessing data related to the brewing process.

## Purpose of API:
The general purpose of the API is to keep track of how a batch of beer is being brewed over time. There are some peripheral information pieces such as employees that are working on the system, the tanks that the batches are being brewed in, actions associated with those tanks, and the recipes for a brew.

## Security Mechanisms:
The API will have a JWT based authorization to ensure that the every request someone makes, they are indeed a user that is permitted to do actions on a certain table. When a user is created, or signs in, they will provide a password for authentication, after their password and username are verified they will be given a time based JWT for all their requests.

The API will also escape/validate submitted data to prevent injection attacks and to prevent illogical values from being stored in the database. Most of this kind of validation will be handled by third-party validators, like npm’s [validator](https://github.com/chriso/validator.js), as well as custom validators that validate types of data that are unique to the API. Injection attacks will also be prevented by using prepared statements when querying the database.

To prevent attacks of the denial-of-service and brute-force variety, we can limit the rate to which requests are made to the API. Rate limiting can easily be handled using a third party rate limiter, like npm’s [express-rate-limit](https://github.com/nfriedly/express-rate-limit).

Finally, the API will protect both the user’s privacy and any of the API’s architectural secrets. To protect the former, the API will take precautions like avoiding exposing any of the user’s sensitive data in route specifications. To protect the latter, it will perform responsible error handling such that the user only ever sees custom error messages instead of default debugging information that could potentially reveal sensitive information about the API.

## Resources

This project uses
* Docker
* PostgreSQL
* Express

Express uses the [pg](https://node-postgres.com/) package to interact with the postgreSQL database.


## Startup

#### Development
1. `docker-compose up` will start the development database.
1. `nodemon server.js` will start the API.
1. After launching the database, visit `http://localhost:8080` to interact with the database through a web interface.

#### Production
1. `docker-compose -f docker-compose-prod.yaml up` will start the production databse and API.

## Helpful Notes

To find the IPAddress of the docker container:

`docker inspect [container name] | grep "IPAddress"`

The default username to log into the database is *postgres*.
The rest of the DB settings are configured within the *.env* file.
