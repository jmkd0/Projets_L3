let crypto      = require('crypto');
let geolocation = require('geolocation')
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