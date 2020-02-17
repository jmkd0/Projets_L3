<!DOCTYPE html>
<html>
 <head>
 <meta charset="utf-8"/>
<link rel="stylesheet" href="style.css" >
 <title>Contactez nous</title>
 </head>
 <body>
 <!-- L'en-t�te -->
 <?php include("head.php"); ?>

<div style="background-color:white">
	 <div id="corps">
 <h1 style="color:black; font-family:Old English Text MT; text-align:center; ">Bienvenue dans votre magasin </h1>
</div>

<?php
//récupération des données à partir du formulaire
 $mail=$_POST['mail'];
 $password=$_POST['password'];

include("connection.php");


// $reponse cet objet va contenir la réponse de mysql.
$reponse = $bdd->query('SELECT* FROM clients');
$donnees = $reponse->fetch();

$cle=0;
do{
	$a=$donnees['mail'];
	$b=$donnees['pass'];

	if($mail==$a){
		
		$cle=$donnees['codeclt'];

	}

}while($donnees = $reponse->fetch());
/*	
while ($donnees = $reponse->fetch()){
	
	
	if($mail==$donnees['mail']&&$password==$donnees['pass']){
		
		$cle=$donnees['codeclt'];

	}
}*/
$reponse->closeCursor(); // Termine le traitement de la requête
?>
<br>
<?php

if($cle==0){
	echo "Votre mot de pass ou identifiant est incorrect";
}else{
	include("pannier.php");
}
?>


 </body>
 
 <?php include("foot.php"); ?>
</html>


