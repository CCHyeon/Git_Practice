var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');

var indexRouter = require('./routes/index');
var usersRouter = require('./routes/users');

const boardRouter = require('./routes/board');

// require (불편해서)
// ==>
// import Express from 'express';

var app = express();

// Template Engine: js코드를 HTML내에서 실행시킬 수 있음.
const nunjucks = require('nunjucks'); // Jinja2 {%  %}
// ejs: 

// view engine setup

// set: configure("config_name", value) 
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'njk');
nunjucks.configure('views', {
  express: app,
  watch: true
})


// logger 적용.
app.use(logger('dev'));

// HTTP Body로 데이터가 전송 되면
app.use(express.json()); // json양식을 사용한다. (json => object)

// encoding:
app.use(express.urlencoded({ extended: false }));

app.use(cookieParser());


// localhost: 3000 / static / css / board.css
app.use("/static",
  express.static(
    path.join(__dirname, 'public')
  )
);

// indexRouter, usersRouter
//  
app.use('/', indexRouter);
app.use('/users', usersRouter);
app.use('/board', boardRouter);

// Module X

// catch 404 and forward to error handler
app.use(function (req, res, next) {
  next(createError(404));
});

// error handler
app.use(function (err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;
