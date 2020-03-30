<?php
//contrôle de connexion à la base de données
try
{
$bdd = new PDO('mysql:host=localhost; dbname=client_grace; charset=utf8','root','');
}
catch(Exception $e)
{
 die('Erreur : '.$e->getMessage());
}
?>