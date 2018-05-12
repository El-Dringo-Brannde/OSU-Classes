var express = require('express');
var mysql = require ('mysql');
var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});
var session = require('express-session');
var bodyParser = require('body-parser');
var request = require ('request');

app.use(bodyParser.urlencoded({ extended: false }));
app.use(session({secret:'SuperSecretPassword'}));

app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 3000);

var key = '1aeab2a0dfe6b0d9ef6a9a7fc8aedf04';

var mysql = require('mysql');
var pool = mysql.createPool({
  host  : 'localhost',
  user  : 'student',
  password: 'default',
  database: 'student'
});

app.get('/seestuff',function(req,res,next){
  var context = {};
  pool.query("DROP TABLE IF EXISTS todo", function(err){
    var createString = "CREATE TABLE todo(" +
    "id INT PRIMARY KEY AUTO_INCREMENT," +
    "name VARCHAR(255) NOT NULL," +
    "done BOOLEAN," +
    "due DATE)";
    pool.query(createString, function(err){
      context.results = "Table reset";
      res.render('home',context);
    })
  });
});






app.get('/get-ex',function(req,res,next){
  var context = {};
  var key = '1aeab2a0dfe6b0d9ef6a9a7fc8aedf04';
  request('http://api.openweathermap.org/data/2.5/weather?q=corvallis&APPID=' + key, function(err, response, body){
    if(!err && response.statusCode < 400){
      var stuff = JSON.parse(body);
      context.owm = stuff.main.temp;
      res.render('home',context);
    } else {
      if(response){
        console.log('poop');
        console.log(response.statusCode);
      }
      next(err);
    }
  });
});

//whats with the next arguement?
app.get('/',function(req,res,next){
	var data = {};

	if (!req.session.name){
		res.render('intro',data);
		return; 
	}
	else {
    console.log("I'm in get!");
		data.name = req.session.name; 
		data.todocount = req.session.todo.length || 0;
		data.todo = req.session.todo || [];
    data.temp = req.session.temp; 
    console.log(data.todo);
		res.render('todo.handlebars',data);
	}
});


app.post('/', function(req,res){
  var data = {}; 
  
  if (req.body['New list']){
    req.session.name = req.body.name; 
    req.session.temp = req.body.temperature; 
    req.session.todo = []; 
    req.session.curid = 0;
  }

  if (!req.session.name){
    res.render ('intro'.data);
    return;
  }
  //stupid capitals
  //error if you don't have colons outside of string?
  if (req.body['Add Item']){
    var dumb;
    req.session.todo.push({"name": req.body.name, "id": req.session.curid,"temperature": req.body.temperature});
    request('http://api.openweathermap.org/data/2.5/weather?q=corvallis&APPID=' + key, function(err, response, body){
      if(!err && response.statusCode < 400){
        var stuff = JSON.parse(body);
        dumb = stuff.main.temp;
        console.log(stuff);
        console.log(req.body.temperature);
        if (dumb > req.body.temperature){
          console.log("ITS HOT");
        }
      } else {
        if(response){
          console.log('poop');
          console.log(response.statusCode);
        }
        next(err);
      }
    });
    //--------------------------
    req.session.curid++;
  }

  if (req.body['Done']){
    req.session.todo = req.session.todo.filter(function(x){
      return x.id != req.body.id; 
    })
  }

  data.name = req.session.name; 
  data.todocount = req.session.todo.length;
  data.todo = req.session.todo; 
  console.log(data.todo);
  res.render('todo',data);
});




//what does req.session actually do?
//How do you know the names of the properties of the current project?
//Eg. name, todocount 
app.get('/count',function(req,res){
  var context = {};
  context.count = req.session.count || 0;
  req.session.count = context.count + 1;
  res.render('counter', context);
});

app.post('/count',function(req,res){
  var context = {};
  if(req.body.command === "resetCount"){
    //req.session.count = 0;
    req.session.destroy();
  } else {
    context.err = true;
  }
  if(req.session != NULL){
    context.count = req.session.count;
  } else {
    context.count = 0;
  }
  req.session.count = context.count + 1;
  res.render('counter', context);
});

app.use(function(req,res){
  res.status(404);
  res.render('lost');
});

app.use(function(err, req, res, next){
  console.error(err.stack);
  res.type('plain/text');
  res.status(500);
  res.render('error');
});

app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});