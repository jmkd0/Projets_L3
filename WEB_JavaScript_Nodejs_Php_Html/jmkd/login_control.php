<?php
    session_start();
    $email = $_POST['email'];
    $pass = $_POST['password'];

    if(isset($_POST['login'])){
        try{
            $bdd = new PDO('mysql:host=localhost; dbname=c1389801c_database; charset=utf8','c1389801c_jean','dakomaje00');
            $sql = "SELECT email_db, pass_db FROM jmkd_users WHERE email_db ='$email' AND pass_db='$pass'";
            $req = $bdd->query($sql);
            $response = $req->fetch();
            $a = $response['email_db'];
            echo "<script>console.log('$a');</script>";
            if($email == $response['email_db'] && $pass == $response['pass_db']){
                if(isset($_POST['remember'])){
                    setcookie('email', $email, time()+365*24*3600);//1an
                }
                $_SESSION['email'] = $response['email_db'];
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
