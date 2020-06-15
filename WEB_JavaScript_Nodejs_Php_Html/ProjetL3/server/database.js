let mysql=require('mysql');

let connection=mysql.createConnection({
    host:       'localhost:8080',
    user:       'root',
    password:   'dakomaje59',
    database:   'datedata'
});
module.exports =connection;

