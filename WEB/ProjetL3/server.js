let express     = require('express');
let path        = require('path');
let http        =require('http');
let con         = require('./server/database');
let modulePersonnal      = require('./server/modulefonc')
let connect   = require('./server/connect-user');
let bodyParser  = require('body-parser');
let app=express();
var server = http.createServer(app);


app.use(bodyParser.json());//accept json params
app.use(bodyParser.urlencoded({extended: true})); //accept url encodes params
app.use(express.static(path.join(__dirname, 'public')));
app.get('/',(request, response, next)=>{
    response.sendFile(path.join(__dirname+'/client/index.html'));
})
app.get('/client/match.html',(request, response, next)=>{
    response.sendFile(path.join(__dirname+'/client/match.html'));
})
app.get('/client/match_map.html',(request, response, next)=>{
    response.sendFile(path.join(__dirname+'/client/match_map.html'));
})
app.get('/client/profil_user.html',(request, response, next)=>{
    response.sendFile(path.join(__dirname+'/client/profil_user.html'));
})
app.get('/client/chat.html',(request, response, next)=>{
    response.sendFile(path.join(__dirname+'/client/chat.html'));
})
app.get('/client/mylikes.html',(request, response, next)=>{
    response.sendFile(path.join(__dirname+'/client/mylikes.html'));
})
app.post('/client/index.html', (request, response, next)=>{ 
    let postData=request.body;
    let typeform=postData.form;
    if(typeform==='1'){ //connection
        connectAccount(postData.email, postData.password, response);
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
})
let connectAccount=function(emailPass, userPass, response){
    con.query('SELECT *FROM users WHERE email=?',[emailPass], function(error, result, next){
        if(error) throw error;
        if(result && result.length){
            let passwordEncrypt= result[0].password;
            let salt           = result[0].passsalt;
            let hashPass       = modulePersonnal.checkHashPass(userPass, salt).passwordHash;
            if(passwordEncrypt == hashPass){
                let age=modulePersonnal.calculateAge(result[0].birthday);
                let data={
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
                exports.server=server;
                connect.displayFreinds();
                response.sendFile(path.join(__dirname+'/client/match.html'));
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

server.listen(8080);

