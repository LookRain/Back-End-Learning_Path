let express = require('express');

let app = express();

app.use(express.static('public'));

// app.get('/', (req, res) => res.sendFile(__dirname + "/public/" + "index.html"));
console.log(__dirname);

app.get('/get_name', (req, res) => {
	response = {
		first_name: req.query.first_name,
		last_name: req.query.last_name
	};
	console.log(response);
	res.end(JSON.stringify(response));
});

let server = app.listen(9999);

