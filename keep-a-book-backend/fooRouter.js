var express = require('express')
var fooRouter = express.Router()

fooRouter.get('/', function (req, res) {
  res.send('GET route on things.')
})
fooRouter.post('/', function (req, res) {
  res.send('POST route on things.')
})

// export this router to use in our index.js
module.exports = fooRouter
