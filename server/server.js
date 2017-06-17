//Created by manzumbado 

var express     = require('express');
var app         = express();
var bodyParser  = require('body-parser');
var morgan		= require('morgan');
var child_p     = require('child_process');


 //*****************
 //Config
 //*****************

 var port = process.env.PORT || 8080; 
//This is to get the request parameters
app.use(bodyParser.urlencoded({ extended: false }));
app.use(bodyParser.json());
app.use(morgan('dev')); //This is lo log requests to the console
app.use('/', express.static(__dirname + '/public'));



//******************
//Routes
//******************

// // basic Route (GET http://localhost:8080)
// app.get('/', function(req, res) {
//   res.send('Hi! The API is at http://localhost:' + port + '/api');
// });
 
// Start the server
app.listen(port);
console.log('Starting the server on: http://localhost:' + port);

// bundle for the routes
var apiRoutes = express.Router();

var mapStr = {
   ':a:':"A",
   ':b:':"B",
   ':c:':"C",
   ':d:':"D",
   ':e:':"E",
   ':f:':"F",
   ':g:':"G",
   ':h:':"H",
   ':i:':"I",
   ':j:':"J",
};

// POST method to send a string (POST http://localhost:8080)
apiRoutes.post('/message', function(req, res) {
  //child_p.execSync('call a program');
  var re = /(:[a-j]:)/;
  var resStr = req.body.message.toLowerCase();
  resStr = resStr.replace(re,function(matched){return mapStr[matched]});
  child_p.execSync('../library/wrapper -p '+resStr);
  res.send(JSON.parse('{}'));
});

// connect the api routes underut /api/*
app.use('/api', apiRoutes);

