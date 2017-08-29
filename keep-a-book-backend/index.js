let express = require('Express')
let app = express()
var bodyParser = require('body-parser')
var multer = require('multer')
var upload = multer()

// let fooRouter = require('./fooRouter.js')
// let dynamicRouter = require('./dynamicRouter.js')
var mongoose = require('mongoose')
app.set('view engine', 'pug')
app.set('views', './views')
// var path = require('path')
mongoose.connect('mongodb://localhost/my_db', {
  useMongoClient: true
})
var personSchema = mongoose.Schema({
  name: String,
  age: Number,
  nationality: String
})
var Person = mongoose.model('Person', personSchema)
/*
transaction: {
  payer: 'A',
  payerID: 1,
  amount: 30,
  receiver: [1,2,3]
}

transaction: {
  payer: 'B',
  payerID: 2
  amount: -30,
  receiver: [4]
}
*/
let transactionSchema = mongoose.Schema({
  id: Number,
  payer: String,
  amount: Number,
  receiver: [Number] // Array of IDs
})
let Transaction = mongoose.model('Transaction', transactionSchema)

// for parsing application/json
app.use(bodyParser.json())

// for parsing application/xwww-
app.use(bodyParser.urlencoded({ extended: true }))
// form - urlencoded
app.get('/person', function (req, res) {
  console.log('get')
  res.render('person')
  // res.sendFile(path.join(__dirname, '/form.html'))
})
app.get('/m', function (req, res) {
  res.render('show_message')
})
// app.get('/show-all', (req, res) => {
//   res.send(Person.find({}))
// })
app.get('/usersList', function (req, res) {
  Person.find({}, (err, ppl) => {
    res.send(ppl)
  })
})
app.post('/person', function (req, res) {
  console.log('post')
  var personInfo = req.body // Get the parsed information
  console.log(req.body)

  if (!personInfo.name || !personInfo.age || !personInfo.nationality) {
    console.log('missing info')
    res.render('show_message', {
      message: 'Sorry, you provided worng info', type: 'error'})
  } else {
    console.log('else')
    var newPerson = new Person({
      name: personInfo.name,
      age: personInfo.age,
      nationality: personInfo.nationality
    })
    console.log(newPerson)

    newPerson.save(function (err, Person) {
      if (err) {
        console.log(err)
        res.render('show_message', {message: 'Database error', type: 'error'})
      } else {
        // res.render('show_message', {
        //   message: 'New person added', type: 'success', person: personInfo})
        res.send(personInfo)
      }
    })
  }
})

app.post('/new-transaction', (req, res) => {
  let info = req.body
  if (!info.id || !info.payer || !info.amount || !info.receiver) {
    res.status(400).send('incomplete input')
  }
})
// app.get('/', (req, res) => {
//   res.send('root dir')
// })

// app.use('/foo', fooRouter)

// app.use('/user', dynamicRouter)

app.listen(5000)
