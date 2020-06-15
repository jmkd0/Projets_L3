<!DOCTYPE html> 

<html> 

    <head> 

        <title>Navigator</title>

        <meta http-equiv="content-type" content="text/html; charset=UTF-8">

        <meta name="viewport" content="initial-scale=1, user-scalable=no, maximum-scale=1, width=device-width, height=device-height">

        <link rel="stylesheet" type="text/css" href="style.css">

    </head> 

    <body> 

    	<div id="title">Welcome to JMKD web site</div> 

    	<div id="head"></div> 

    	<div id="information"></div> 

    	<div id="grid2-style">

            <div class="element"><a class="a-class-info" href="https://jmkd.fr/grace">Connect to Grace's Clothe</a></div>

            <div class="element"><a class="a-class-info" href="https://jmkd.fr/date/">Connect to Date website</a></div>

            <div class="element"><a class="a-class-info" href="#">See more about Mobile App content</a></div>

        </div>

        <div id="id-principal">

        	

            <div>

                <button id="goto" onclick="disappereAppeare('id-principal','id-container')">Go to</button>

            </div> 



        </div>



        <div id="id-container">

            <div class="container">

              <p>Please fill in this form to connect</p>

              <hr>

              <label for="email"><b>Enter a message to go</b></label>

              <input type="text" placeholder="begin typing" name="email" required>



              <div id="redirect">

              	<div id="redi1"><button type="button" id="goback" onclick="disappereAppeare('id-container','id-principal')">Go back</button></div>

              	<div id="redi2"><a id="gosignup" href="signup.php">Account</a></div>

              	<div id="redi3"><a id="gosignin" href="login.php">Connect</a></div>

              </div>





            </div>

        </div>

        <script>

          function disappereAppeare(disappere, appere){

            document.getElementById(disappere).style.display='none'

            document.getElementById(appere).style.display='block'

          }

        </script>

    </body> 

</html>

