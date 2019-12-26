let con         = require('./database')
let transfertData= require('../server');
let transfertModule=require('./modulefonc')

let data=transfertData.userData;
let displayFreinds=function(){
con.query('SELECT id, pseudo, birthday, region, description FROM users', function(error, result, next){
    if(error) throw error;
    if(result && result.length){  
        let age=transfertModule.calculateAge(result[0].birthday);
        console.log(result.length)
        let response=[];
        for(let i=0; i<result.length; i++){
            response[i]={
                id:             result[i].id,
                pseudo:         result[i].pseudo,
                age:            transfertModule.calculateAge(result[i].birthday),
                region:         result[i].region,
                description:    result[i].description
            }
        }
        
        //send response to the client
        senderResponse(response);

    }else{
        console.log("problems no user");// come back and continue
    }
})
}
exports.displayFreinds=displayFreinds;

let senderResponse=function(response){
    let io=require('socket.io').listen(transfertData.server);
        io.sockets.on('connection', function( socket, request){
            socket.emit('send-data', response);
        })
}