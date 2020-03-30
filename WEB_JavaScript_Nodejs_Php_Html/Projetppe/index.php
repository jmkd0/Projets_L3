<!doctype>
	<!DOCTYPE html>
	<html>
	<head>
			<meta charset="utf-8">
			<link rel="stylesheet"  href="style.css">
		    <title>Bienvenu dans votre magasin</title>
		    
		    
	</head>
	<?php include ("head.php"); ?>
	
	<body>
		<div class="slideshow"><style>
.slideshow {
	background-color:white;
   width: 100%;
   height: 100%;
   overflow: hidden;
}

.slideshow ul {
   width: 100%;
   height: 100%;
   padding:0; margin:0;
   list-style: none;
}

.slideshow li {
	display: inline-block;
}
</style>
<script type="text/javascript" src="https://ajax.googleapis.com/ajax/libs/jquery/1.5.1/jquery.min.js"></script>
<script type="text/javascript">
   $(function(){
      setInterval(function(){
         $(".slideshow ul").animate({marginLeft:-2000},3000,function(){
            $(this).css({marginLeft:0}).find("li:last").after($(this).find("li:first"));
         })
      }, 4000);
   });
</script>

		<ul>
             <li><img src="images/1.jpg" alt="" width="1400" height="100%" /></li>
             <li><img src="images/2.jpg" alt="" width="1400" height="100%" /></li>
             <li><img src="images/3.jpg" alt="" width="1400" height="100%" /></li>
             <li><img src="images/4.jpg" alt="" width="1400" height="100%" /></li>
             <li><img src="images/5.jpg" alt="" width="1400" height="100%" /></li> 
             <li><img src="images/6.jpg" alt="" width="1400" height="100%" /></li>            

       </ul>
   </div>



	<?php include ("foot.php");	?>
		 
	</body>

	
	
	</html>