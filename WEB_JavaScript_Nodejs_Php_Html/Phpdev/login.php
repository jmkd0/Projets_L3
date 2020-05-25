<table cellpadding = "5" cellspacing = "10" align = "center">
    <h2 style="text-align: center;">Login</h2>
    <form action="login_control.php" method = "post">
        <tr><th style="text-align: left;">Email</th><td><input type="text" name = "email"></td></tr>
        <tr><th style="text-align: left;">Password</th><td><input type="password" name = "password"></td></tr>
        <tr><td colspan ="2" align ="center" >
            <input value = "1" type="checkbox" name = "remember">Remember me</td>
        </tr>
        <tr><td colspan ="2" align ="right" >
            <input value = "Login" type="submit" name = "login"></td>
        </tr>
        
    </form>
</table>