<style>
    body {
        background-image: url('ressource/image_ia.jpg');
        color: white;
    }
input[type=text], input[type=password],input[type=checkbox],  input[type=tel] {
  width: 100%;
  padding: 2vh;
  margin: 1vh 0vh 2vh 0vh;
  font-size: 2.5vh;
  border-radius: 1vh;
  display: inline-block;
  border: none;
  background: #BEBEBE;
}

input[type=text]:focus, input[type=password]:focus,input[type=checkbox]:focus, input[type=tel]:focus {
  font-size: 2.5vh;
  outline: none;
}

#btlogin{
  color: white;
  padding: 1vh 2vh 1vh 2vh ;
  font-size: 2.4vh;
  border: none;
  cursor: pointer;
  opacity: 0.9;
  border-radius: 1vh;
  border: 0.4vh outset #c0c0c0;
  float: right;
  background-color: #4CAF50;
}

.container {
  width: 50%;
  color: black;
  margin-left: auto;
  margin-right: auto;
  background-color: #F0F0F0;
  border: 3px solid #7B7B7B;
  border-radius: 2vh;
}

th{
    text-align: left;
    font-size: 4vh;
}
.entry{
    border: 3px solid red;
    border-radius: 2vh;
    box-shadow: 1px 1px 1px #474e5d;
}

</style>

<table class = "container" cellpadding = "5" cellspacing = "10" align = "center">
    <h2 style="text-align: center;">Login</h2><hr>
    <form class="container" action="login_control.php" method = "post">
        <tr><td colspan ="2">
            <h1 style="text-align: center; " >Sign In</h1></td>
        </tr>
        <tr class = "entry"><th>Email</th><td><input type="text" name = "email" placeholder="email adress"required></td></tr>
        <tr class = "entry"><th>Password</th><td><input type="password" name = "password" placeholder="password" required></td></tr>
        <tr><td colspan ="2" align ="right" >
            <input id = "btlogin" value = "Login" type="submit" name = "login"></td>
        </tr>
    </form>
</table>
