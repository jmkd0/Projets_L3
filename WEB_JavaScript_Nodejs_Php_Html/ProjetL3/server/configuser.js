let importserver            = require('../server')
let con                     = require('./database');
let modulePersonnal         = require('./modulefonc')
let connect                 = require('./connect-user');
let  identity;

let createConnectUser= function(request){
    let postData=request.body;
    let typeform=postData.form;
    if(typeform==='1'){ //connection
        connectAccount(postData.email, postData.password);
    }
    if(typeform==='2'){ //inscription
        let  passconfirm=postData.passconfirm; //come back and continue
        let user={
             pseudo:        postData.pseudo,
             gender:        postData.gender,
             birthday:      postData.birthday,
             region:        postData.region,
             email:         postData.email,
             phone:         postData.phone,
             password:      postData.password,
             passsalt:      postData.password,
             description:   postData.description,
             loclatt:       24.2,
             loclong:       18.3
        }
        createAccount(user);     
    }   
}
exports.createConnectUser = createConnectUser

let connectAccount=function(emailPass, userPass){
    con.query('SELECT *FROM users WHERE email=?',[emailPass], function(error, result, next){
        if(error) throw error;
        if(result && result.length){
            let passwordEncrypt= result[0].password;
            let salt           = result[0].passsalt;
            let hashPass       = modulePersonnal.checkHashPass(userPass, salt).passwordHash;
            if(passwordEncrypt == hashPass){
                let age=modulePersonnal.calculateAge(result[0].birthday);
                let data={
                    id:             result[0].id,
                    pseudo:         result[0].pseudo,
                    gender:         result[0].gender,
                    age:            age,
                    region:         result[0].region,
                    phone:          result[0].phone,
                    description:    result[0].description,
                    loclatt:        result[0].loclatt,
                    loclong:        result[0].loclong
                }
                exports.userData = data;
                console.log("Connected!");
                //send data to the client
                importserver.io.sockets.on('connection', function( socket, request){
                    socket.emit("main-user-data", data);
                });
                identity=emailPass;
                exports.identity =identity;
                exports.server=importserver.server;
                connect.displayFreinds();
                importserver.answer;
            }else{
                console.log("You forget your password")
            }
            
        }else{
            console.log("User not exist");// come back and continue
        }
    })
}
let createAccount=function (user){
    con.query('SELECT *FROM users WHERE email=?',[user.email], function(error, result, next){
        if(error) throw error;
        if(result && result.length){
            console.log("User already registred");// come back and continue
        }else{
            let pass=modulePersonnal.saltHashPassword(user.password);
            user.password=pass.passwordHash;
            user.passsalt=pass.salt;
            let sqls="INSERT INTO users SET ?";
            con.query(sqls, user, function (error, result) {
            if (error) throw error;
            console.log("1 row added");
        });
   
        }
    })
}
let upDateInfo= function(){
  importserver.io.sockets.on('connection', function (socket) { 
 	socket.on('send-location', function(response) {
         let data=[response.latt, response.long, identity];
        con.query(function(result,error) {
            if (error) throw error;
            let sql = "UPDATE users SET loclatt = ?, loclong=? WHERE email =?";
            con.query(sql, data, function (err, result) {
              if (err) throw err;
              console.log("updated");
            });
          });
 	}); 
})
    
}
exports.upDateInfo = upDateInfo;