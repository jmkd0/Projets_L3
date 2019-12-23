console.log("Welcom")
var mysql = require('mysql');

var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "dakomaje59",
  database: "mydb"
});

con.connect(function(err) {
  if (err) throw err;
  console.log("Connected!");
  var sql = "CREATE TABLE customers (name VARCHAR(255), address VARCHAR(255))";
  con.query(sql, function (err, result) {
    if (err) throw err;
    console.log("Table created");
  });
});
create table users(
   id             int           not null        auto_increment        primary key,
   pseudo         varchar(20),
   gender         varchar(1),
   birthday       date,
   region         varchar(20),
   email          varchar(20),
   phone          varchar(20),
   password       varchar(255),
   description    varchar(255),
   loclatt        float(5,5),
   loclong        float(5,5))
   engine=innodb;