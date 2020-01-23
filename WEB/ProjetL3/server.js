let express           = require('express');
let path              = require('path');
let http              =require('http');
let bodyParser        = require('body-parser');
let configuser        =require('./server/configuser')
let transfertConnect  =require('./server/connect-user')
let usermanage        =require('./server/usermanage')
let app               =express();
let server            = http.createServer(app);
let io                = require('socket.io').listen(server);
let ent               = require('ent');

exports.server  = server;
exports.path    = path;
exports.io      = io;
exports.ent     = ent;

app.use(bodyParser.json());//accept json params
app.use(bodyParser.urlencoded({extended: true})); //accept url encodes params
app.use('/', express.static(path.join(__dirname, 'public')));

app.get('/',(request, response, next)=>{
    response.sendFile(path.join(__dirname+'/client/index.html'));
})
app.get('/client/match.html',(request, response, next)=>{
    configuser.upDateInfo();
    usermanage.listenLikes();
    response.sendFile(path.join(__dirname+'/client/match.html'));
})
app.get('/client/match_map.html',(request, response, next)=>{
    transfertConnect.displayFreindsMap()
    response.sendFile(path.join(__dirname+'/client/match_map.html'));
})
app.get('/client/profil_user.html',(request, response, next)=>{
    response.sendFile(path.join(__dirname+'/client/profil_user.html'));
})
app.get('/client/discussions.html',(request, response, next)=>{
    response.sendFile(path.join(__dirname+'/client/discussions.html'));
})
app.get('/client/chat.html',(request, response, next)=>{
    response.sendFile(path.join(__dirname+'/client/chat.html'));
    usermanage.sendMessage();
})
app.get('/client/mylikes.html',(request, response, next)=>{
    response.sendFile(path.join(__dirname+'/client/mylikes.html'));
})
app.post('/client/index.html', (request, response, next)=>{ 
    configuser.createConnectUser(request);
    usermanage.listenLikes();
    exports.answer= response.sendFile(path.join(__dirname+'/client/match.html'));
})
server.listen(8080);