<?php
//récupération des données à partir du formulaire
 $nomclt=$_POST['nomclt'];
 $prenomclt=$_POST['prenomclt'];
 $mail=$_POST['mail'];
 $pass=$_POST['pass'];
 $confpass=$_POST['confpass'];

include("connection.php");
// On ajoute une donnée dans la table clients
$req = $bdd->prepare('INSERT INTO clients(nomclt, prenomclt, mail, pass, confpass) VALUES(:nomclt, :prenomclt, :mail, :pass, :confpass)');
$req->execute(array('nomclt'=>$nomclt,'prenomclt'=>$prenomclt,'mail'=>$mail,'pass'=>$pass,'confpass'=>$confpass));
$save="Vous etes enrégistré avec succès";
echo 'maintenant votre enregistrement est rajouté à la table des clients!';
include("compte.php");
?>