<!DOCTYPE html>
<html>
 <head>
 <meta charset="utf-8"/>
<link rel="stylesheet" href="style.css" >
 <title>Mon beau site</title>
 </head>
 <body>
 <!-- L'en-t�te -->
 <?php include("head.php"); ?>

<div style="background-color:lightsteelblue">
	 <div id="corps">
 <h1 style="color:black; text-align:center; ">Vous avez fait un choix procédez à l'achat sécurisé</h1>
</div>

 <div id="container">

</div>
<script type="text/javascript">
     var choix=<?php $choixs=$_GET['choixs']; echo json_encode($choixs); ?>;
     var container=document.getElementById('container');
     var prix=document.createTextNode('34€');
      var img=document.createElement('img');
          var div=document.createElement('div');
          div.style.padding="0px 0px 0px 150px";
    img.classList.add("imageCard");
    img.src=choix;
    img.style.width="400px";
    img.style.height="500px";
    div.appendChild(img);
    container.appendChild(div);
</script>
<button class="button2" type="button">Ajouter au Panier</button>
<br><br><br><br><br><br><br><br><br><br>




</div>
 </body>
 
 <?php include("foot.php"); ?>
</html>