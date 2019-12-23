let crypto=require('crypto');
let geolocation=require('geolocation')
let express=require('express');
let path = require('path');
let mysql=require('mysql');
let connectUser=require('./server/connect-user')
let bodyParser=require('body-parser');
let app=express();
let con=mysql.createConnection({
    host:       'localhost',
    user:       'root',
    password:   'dakomaje59',
    database:   'userdata'
});
app.use(bodyParser.json());//accept json params
app.use(bodyParser.urlencoded({extended: true})); //accept url encodes params
app.use(express.static(path.join(__dirname, 'public')));
app.get('/',(request, response, next)=>{
    response.sendFile(path.join(__dirname+'/client/index.html'));
})
app.post('/client/index.html', (request, response, next)=>{ 
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
})
let connectAccount=function(emailPass, userPass){
    con.query('SELECT *FROM users WHERE email=?',[emailPass], function(error, result, next){
        if(error) throw error;
        if(result && result.length){
            let passwordEncrypt= result[0].password;
            let salt           = result[0].passsalt;
            let hashPass       = checkHashPass(userPass, salt).passwordHash;
            if(passwordEncrypt == hashPass){
                //let connect=connectUser();
                //geolocate(geolocation);
                console.log("Connected!");
                console.log("pseudo= "+result[0].pseudo);
                console.log("genre= "+result[0].gender);
                console.log("birthday= "+result[0].birthday);
                console.log("region= "+result[0].region);
                console.log("phone= "+result[0].phone);
                console.log("description= "+result[0].description);
                console.log("gps= "+result[0].loclatt+" "+result[0].loclong);
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
            let pass=saltHashPassword(user.password);
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
// password encryptation
let genRandomString=function(length){
    return crypto.randomBytes(Math.ceil(length/2))
    .toString('hex') //convert to hexa forma
    .slice(0,length); //return required number of character
}
let sha512=function(password, salt){
    let hash=crypto.createHmac('sha512', salt);
    hash.update(password);
    let value=hash.digest('hex');
    return { salt: salt, passwordHash: value}
}
function saltHashPassword(password){
    let salt= genRandomString(16);
    let passworEncrypt=sha512(password, salt)
    return passworEncrypt;
}
let checkHashPass=function(userPass, salt){
    let decriptPass=sha512(userPass, salt);
    return decriptPass;
}
/*let geolocate=function(geolocation){
    geolocation.getCurrentPosition(function(error, position){
        if(error) throw error;
        console.log(position);
    })
}*/
app.listen(8080);

