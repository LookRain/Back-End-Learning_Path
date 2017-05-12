let http = require('http');

let options = {
	host: 'localhost',
	port: '8081',
	path: '/index.html'
};

let callback = response => {
	let body = '';
	response.on('data', data => body += data);

	response.on('end', () => console.log(body));
};

let request = http.request(options, callback);
request.end();