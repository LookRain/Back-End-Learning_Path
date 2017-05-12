let express = require('express');

let app = express();

app.get('/', (req, res) => {
	console.log('a GET request');
	res.send('a GET request');
});


app.get('/del_user', (req, res) => {
	console.log("responding to delete request");
	res.send('a delete request');
});

app.get('/list_user', (req, res) => {
	console.log('listing user');
	res.send('a list request');
})

app.get('/ab*cd', (req, res) => {
	console.log('a regex request example');
	res.send('CORRECT: a regex request example');
})


app.post('/', (req, res) => {
	console.log(req.baseUrl);
	res.send('a POST request');
});



let server = app.listen(8888, () => {
	console.log('server listening on http://%s:%s', 
		server.address().address, server.address().port);
});