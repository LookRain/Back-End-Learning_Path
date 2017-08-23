let express = require('Express')
let app = express()

// let fooRouter = require('./fooRouter.js')
// let dynamicRouter = require('./dynamicRouter.js')
var mongoose = require('mongoose')
app.set('view engine', 'pug')
app.set('views', './views')
var path = require('path')
mongoose.connect('mongodb://localhost/my_db', {
  useMongoClient: true
})
var personSchema = mongoose.Schema({
  name: String,
  age: Number,
  nationality: String
})
var Person = mongoose.model('Person', personSchema)
app.get('/person', function (req, res) {
  console.log('get')
  // res.render('person')
  res.sendFile(path.join(__dirname, '/form.html'))
})
app.get('/m', function (req, res) {
  res.render('show_message')
})

app.post('/person', function (req, res) {
  console.log('post')
  var personInfo = req.body // Get the parsed information

  if (!personInfo.name || !personInfo.age || !personInfo.nationality) {
    res.render('show_message', {
      message: 'Sorry, you provided worng info', type: 'error'})
  } else {
    var newPerson = new Person({
      name: personInfo.name,
      age: personInfo.age,
      nationality: personInfo.nationality
    })

    newPerson.save(function (err, Person) {
      if (err) {
        console.log(err)
        res.render('show_message', {message: 'Database error', type: 'error'})
      } else {
        res.render('show_message', {
          message: 'New person added', type: 'success', person: personInfo})
      }
    })
  }
})

// app.get('/', (req, res) => {
//   res.send('root dir')
// })

// app.use('/foo', fooRouter)

// app.use('/user', dynamicRouter)

app.listen(4000)
