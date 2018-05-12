
var express = require('express');

var app = express();
var handlebars = require('express-handlebars').create({defaultLayout:'main'});
//var bodyParser = require('body-parser');

//app.use(bodyParser.urlencoded({extended: false}));
//app.use(bodyParser.json());


app.engine('handlebars', handlebars.engine);
app.set('view engine', 'handlebars');
app.set('port', 1995);

app.get('/',function(req,res){
	res.render('home.handlebars');
});

app.get('/intro', function(req,res){
	res.render('intro.handlebars');
});

app.get('/start', function (req,res){
	res.render('start.handlebars');
});

app.get('/EAPIex',function(req,res){
	res.render('EAPIex.handlebars');
});

app.get('/pictures',function(req,res){
	res.render('Pictures.handlebars');
});

app.get('/Review',function(req,res){
	res.render('Review.handlebars');
});

app.get('/getorpost',function(req,res){
	var parameters = []; 
	for (var p in req.query){
		parameters.push({'name': p, 'value': req.query[p]})
	}
	var printable = {};
	printable.dataList = parameters; 
	res.render('GETstuff.handlebars', printable);
});

app.post('/getorpost', function(req,res){
  var parameters = [];
  for (var p in req.body){
    parameters.push({'name':p,'value':req.body[p]})
  }
  console.log(parameters);
  console.log(req.body);
  var printable = {};
  printable.dataList = parameters;
  res.render('post', printable);
});



app.get('/other',function(req,res){
  res.render('other.handlebars');
});



app.get('/getstuff', function(req,res) {
	var parameters = []; 
	for (var p in req.query){
		parameters.push({'name': p, 'value': req.query[p]})
	}
	var printable = {};
	printable.dataList = parameters; 
	res.render('GETstuff.handlebars', printable);
});	

app.post('/post-stuff', function(req,res){
  var parameters = [];
  for (var p in req.body){
    parameters.push({'name':p,'value':req.body[p]})
  }
  console.log(parameters);
  console.log(req.body);
  var printable = {};
  printable.dataList = parameters;
  res.render('post', printable);
});

app.use(function(req,res){
  res.status(404);
  res.render('error404');
});

app.use(function(err, req, res, next){
  console.error(err.stack);
  res.type('plain/text');
  res.status(500);
  res.render('error500');
});

function gettime(){
	var temp = {};
	temp.time = (new Date(Date.now())).toLocaleTimeString('en-US');
	return temp; 
}

app.listen(app.get('port'), function(){
  console.log('Express started on http://localhost:' + app.get('port') + '; press Ctrl-C to terminate.');
});
