let express = require('express')
let dynamicRouter = express.Router()

dynamicRouter.get('/:id', (req, res) => {
  res.send(`the user id is ${req.params.id}`)
})

module.exports = dynamicRouter
