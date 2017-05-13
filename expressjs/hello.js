let express = require('express');

let app = express();

app.get('/', (req, res) => res.send('home'));
app.get('/test', (req, res) => res.send('test'));

let server = app.listen(8081, () => {
	let host = server.address().address;
	let port = server.address().port;
	console.log(__dirname);
	console.log("test, the address is http://%s:%s", host, port);
});