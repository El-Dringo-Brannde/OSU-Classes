const Hapi = require('hapi');
var mysql = require("mysql");
const server = new Hapi.Server();
var Inert = require("inert");

var conn = mysql.createConnection({
    host: 'localhost',
    user: 'root',
    password: 'Beandip95',
    database: 'cs340_dringb'
});

conn.connect(function(err) {
    if (err)
        console.log("Could not connect to database", err);
    else
        console.log("Connected successfully!");
});

server.connection({
    host: '10.0.0.10',
    port: 4444
});

const path = require('path');
server.register(Inert, () => {});

//------------------------- Required Files --------------------------------------

server.route({
    method: "POST",
    path: "/test",
    handler: function(request, reply) {
        var address = request.payload.address.split(" ")[0];
        var street = request.payload.address.split(" ").splice(1, 9);
        var cleanStreet = street.join(" ").toLowerCase();
        console.log(cleanStreet);
        var query = "SELECT Delivery.`Tip$` from Delivery,Location where Location.Address = ? and LOWER(Location.Street) = ? and Delivery.DeliveryID = Location.DeliveryID";
        conn.query(query, [address, cleanStreet], function(err, rows, fields) {
            if (!err) {
                var test = 0;
                for (i in rows)
                    test += parseFloat(rows[i].Tip$);
                reply(test / rows.length);
            } else
                console.log("Error preforming request", err);
        });
    }
});

server.route({
    method: "GET",
    path: "/",
    handler: function(request, reply) {
        reply.file("./Optipmal.html")
    }
});

server.route({
    method: "GET",
    path: "/work.js",
    handler: function(request, reply) {
        reply.file("./work.js");
    }
});

server.route({
    method: "GET",
    path: "/mapStyling.css",
    handler: function(request, reply) {
        reply.file("./mapStyling.css");
    }
});

server.start((err) => {
    if (err) {
        throw err;
    }
    console.log(`Server running at: ${server.info.uri}`);
});
