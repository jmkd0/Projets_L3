<?php
    session_start();
    $email = $_POST['email'];
    $pass = $_POST['password'];

    if(isset($_POST['login'])){
        try{
            $bdd = new PDO('mysql:host=localhost; dbname=jmkddev; charset=utf8','root','');
            $req = $bdd->prepare('SELECT email_db, pass_db FROM users WHERE email_db =? AND pass_db=?');
            $req->execute(array($email, $pass));
            $reponses = $req->fetch();
            if($email == $reponses['email_db'] && $pass == $reponses['pass_db']){
                if(isset($_POST['remember'])){
                    setcookie('email', $email, time()+365*24*3600);//1an
                }
                $_SESSION['email'] = $email;
                header("location: welcome.php");
            }else{
                header("location: login.php");
            }
            $req->closeCursor();
        }catch(Exception $e){
            die('Erreur : '.$e->getMessage());
        }
    }else header("location: login.php");
?>