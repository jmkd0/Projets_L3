<!DOCTYPE html>
<html>
 <head>
 <meta charset="utf-8"/>
<link rel="stylesheet" href="style.css" />
 <title>Vos articles � choisir</title>
 </head>
 <body>
 <!-- L'en-t�te -->
 <?php include("head.php"); ?>


 <div>
  <ul id="imageContainer">
  </ul>
</div>
<script type="text/javascript">
  var produit=<?php $produit=$_GET['produit']; echo json_encode($produit); ?>;
  var nouveau=[];
  var chemise=[];
  var chaussure=[];
  var pantalon=[];
  var container=document.getElementById('imageContainer');
  var docFrag=document.createDocumentFragment();

  function addElementToDocFragment(imageSrc){
  var a=document.createElement('a');
   a.href="choix.php?choixs="+imageSrc;
   var prix=document.createTextNode('34EUR');
    var li=document.createElement('li');
    li.style.padding="10px";
    var img=document.createElement('img');
    img.classList.add("imageCard");
    img.src=imageSrc;
    img.style.width="250px";
    img.style.height="400px";
    a.appendChild(img);

    a.appendChild(prix);
    li.appendChild(a);
    docFrag.appendChild(li);
  }
 


  if(produit=='nouveau'){
    for(var i=1; i<7; i++){
      nouveau.push("test"+i+".jpg");
    }
    nouveau.forEach(function(imageName, index, originalArray){
      addElementToDocFragment("images/"+imageName);
    })
  }
    if(produit=='chemise'){
    for(var i=1; i<7; i++){
      nouveau.push("chemise"+i+".jpg");
    }
    nouveau.forEach(function(imageName, index, originalArray){
      addElementToDocFragment("images/"+imageName);
    })
  }
    if(produit=='chaussure'){
    for(var i=1; i<7; i++){
      nouveau.push("chaussure"+i+".jpg");
    }
    nouveau.forEach(function(imageName, index, originalArray){
      addElementToDocFragment("images/"+imageName);
    })
  }

    if(produit=='pantalon'){
    for(var i=1; i<7; i++){
      nouveau.push("pantalon"+i+".jpg");
    }
    nouveau.forEach(function(imageName, index, originalArray){
      addElementToDocFragment("images/"+imageName);
    })
  }
   if(produit=='enfant'){
    for(var i=1; i<7; i++){
      nouveau.push("enfant"+i+".jpg");
    }
    nouveau.forEach(function(imageName, index, originalArray){
      addElementToDocFragment("images/"+imageName);
    })
  }

  container.appendChild(docFrag);
</script>

<br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br><br>

 </body>
 
 <?php include("foot.php"); ?>


</html>
