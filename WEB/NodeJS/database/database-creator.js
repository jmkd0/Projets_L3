var mysql = require('mysql');

var con = mysql.createConnection({
  host: "localhost",
  user: "root",
  password: "dakomaje59"
});
con.connect(function(err) {
  if (err) throw err;
  con.query("CREATE DATABASE usermanage", function (err, result) {
    if (err) throw err;
    console.log("Database created");
  });
});