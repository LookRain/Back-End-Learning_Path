var express = require('Express')
var app = express()

var fooRouter = require('./fooRouter.js')

app.get('/', (req, res) => {
  res.send('root dir')
})

app.use('/foo', fooRouter)

app.listen(4000)
