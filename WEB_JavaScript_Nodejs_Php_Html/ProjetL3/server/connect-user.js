let con                     = require('./database')
let transfertData           = require('./configuser');
let transfertModule         =require('./modulefonc')
let importserver            = require('../server')
let data                    =transfertData.userData;

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
        senderResponse("send-data", response);

    }else{
        console.log("problems no user");// come back and continue
    }
})
}
exports.displayFreinds=displayFreinds;

let displayFreindsMap=function(){
    let userresponse;
    let response=[];
    //Select all users exept the main user
    con.query('SELECT id, pseudo, loclatt,loclong FROM users WHERE not email=?',[transfertData.identity], function(error, result, next){
        if(error) throw error;
        if(result && result.length){  
            for(let i=0; i<result.length; i++){
                response[i]={
                    id:             result[i].id,  
                    pseudo:         result[i].pseudo,
                    latitude:      result[i].loclatt,
                    longitude:      result[i].loclong
                }
            }
            //Select the main user
            con.query("SELECT id, pseudo, loclatt, loclong FROM users WHERE email=?", [transfertData.identity], function (err, result, next) {
                if (err) throw err;
                userresponse=result[0];
                calculeUserNear(userresponse, response);
          });
        }else{
            console.log("no user near you");// come back and continue
        }
    })
    }
    exports.displayFreindsMap=displayFreindsMap;

let calculeUserNear = function( userresponse, response){
    let near=[];
    let k=0;
    for(let i=0; i<response.length; i++){
        let d= transfertModule.calculeDuistance(userresponse.loclatt, userresponse.loclong, response[i].latitude, response[i].longitude);
        if(d< 20){ // if d least than 10 km then they are near
            near[k]={
                id:       response[i].id,
                pseudo:   response[i].pseudo,
                distance: parseInt(d)
            }
            k++;
        }
    }
    if(near && near.length){
        senderResponse("send-near-users", near);
    }
}
let senderResponse=function(message, response){
    importserver.io.sockets.on('connection', function( socket, request){
            socket.emit(message, response);
        });
}