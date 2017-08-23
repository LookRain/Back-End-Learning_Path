let express = require('Express')
let app = express()

let fooRouter = require('./fooRouter.js')
let dynamicRouter = require('./dynamicRouter.js')

app.get('/', (req, res) => {
  res.send('root dir')
})

app.use('/foo', fooRouter)

app.use('/user', dynamicRouter)

app.listen(4000)
