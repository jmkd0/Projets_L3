let crypto      = require('crypto');
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
let saltHashPassword=function(password){
    let salt= genRandomString(16);
    let passworEncrypt=sha512(password, salt)
    return passworEncrypt;
}
exports.saltHashPassword=saltHashPassword
let checkHashPass=function(userPass, salt){
    let decriptPass=sha512(userPass, salt);
    return decriptPass;
}
exports.checkHashPass=checkHashPass;
let calculateAge= function(birthday) { // birthday is a date
    let currentYear= new Date().getFullYear();
        birthday   = new Date(birthday).getFullYear();
    return currentYear-birthday;
}
exports.calculateAge=calculateAge;

let calculeDuistance = function(latt1, long1, latt2, long2){
        latt1=latt1*Math.PI/180;
        latt2=latt2*Math.PI/180;
        long1=long1*Math.PI/180;
        long2=long2*Math.PI/180;
    return 6371*Math.acos(Math.sin(latt1)*Math.sin(latt2)+Math.cos(latt1)*Math.cos(latt2)*Math.cos(long1-long2));
}
exports.calculeDuistance = calculeDuistance;