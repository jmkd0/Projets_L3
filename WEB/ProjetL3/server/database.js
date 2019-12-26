let mysql=require('mysql');

let connection=mysql.createConnection({
    host:       'localhost',
    user:       'root',
    password:   'dakomaje59',
    database:   'userdata'
});
module.exports =connection;

