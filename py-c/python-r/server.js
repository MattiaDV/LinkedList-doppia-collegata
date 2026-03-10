const http = require('http');

let hog = [];

const server = http.createServer((req, res) => {
    // 10MB per richiesta
    hog.push(Buffer.alloc(10 * 1024 * 1024, "A"));
    res.end(`Allocati ${hog.length * 10} MB\n`);
});

server.listen(3000, () => console.log("Server fragile in ascolto"));