<?php
session_start();
//récupération des données à partir du formulaire
 $name 		    =$_POST['name'];
 $email			=$_POST['email'];
 $pass			=$_POST['password'];
 
 $size_max           = 3145728; ///3Mo\\\
 $name_file          = $_FILES['file']['name'];
 $type_file          = $_FILES['file']['type'];
 $size_file          = $_FILES['file']['size'];
 $error_file         = $_FILES['file']['error'];
 $tmp_adress_file    = $_FILES['file']['tmp_name'];
 $extensions_valides = array( 'jpg' , 'jpeg'  , 'png', 'pdf' );

if(isset($_POST['signin'])){
    try{
        $_SESSION['email'] = $email;
        $extension_upload   = strtolower(  substr(  strrchr($name_file, '.')  ,1)  );
        if ( in_array($extension_upload, $extensions_valides) ){
            echo "Extension correcte";
            header("location: signin.php?response=extention");
        } 
        if ($size_file > $size_max){
            $erreur = "Le fichier est trop gros";
            header("location: signin.php?response=bigsize");
        } 
        $name_file_uniq = md5 (uniqid(rand(), true));
        $path = "ressource/{$name_file_uniq}.{$extension_upload}";
        
        $bdd = new PDO('mysql:host=localhost; dbname=jmkddev; charset=utf8','root','');
        $sql = "INSERT INTO users (name_db, email_db, pass_db, avatar_db) VALUES('$name', '$email', '$pass', '$path')";
        $bdd->exec($sql);
        
        $resultat = move_uploaded_file($tmp_adress_file, $path);
        if ($resultat) echo "Transfert réussi";
		header("location: welcome.php");
    }catch(Exception $e){
        die('Erreur : '.$e->getMessage());
    }

}else header("location: signin.php");
?>
?>