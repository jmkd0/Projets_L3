let importserver            = require('../server')
let sendMessage=function(){
    importserver.io.sockets.on('connection', function( socket, request){
        socket.on('client-send-message', function(sendmessage){
            sendmessage = importserver.ent.encode(sendmessage);
            importserver.io.sockets.emit('server-send-message', sendmessage);    
        })
        
    })
}
exports.sendMessage = sendMessage;
let listenLikes= function(){
    importserver.io.sockets.on('connection', function( socket, request){
        
        socket.on('send-drag', function(drag){
            importserver.io.sockets.emit('send-likes', drag);    
        })
        
    })
}
exports.listenLikes = listenLikes;