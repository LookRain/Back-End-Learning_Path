let express = require('express')
let app = express()
let baz = require('./foo')


app.get('/', (req, res) => {
  res.send('<b>Hello World!</b>' + baz.testFunction())
})

app.listen(3000)