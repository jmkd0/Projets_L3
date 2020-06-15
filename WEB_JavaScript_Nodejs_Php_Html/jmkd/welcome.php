<?php session_start(); ?>
<h2>Welcome and enjoy it mister or miss <?php echo $_SESSION['email']?></h2>
<!DOCTYPE html>
<html>
    <head>
        <title>Navigator</title>
        <meta http-equiv="content-type" content="text/html; charset=UTF-8">
        <meta name="viewport" content="initial-scale=1, user-scalable=no, maximum-scale=1, width=device-width, height=device-height">
        <link rel="stylesheet" type="text/css" href="style.css">
        <style>
            body {
                background-color: #E0E0E0;
                color:white;
            }
        </style>
    </head>
    <body>

        <h1>1- &lth1&gt Write big text from h1 &lt/h1&gt</h1>
        <h6>1- &lth6&gt to small text qui sont h1, h2, h3, h4, h5, h6&lt/h6&gt</h6>
        <p>1- &ltp&gt write a simple paragraphe &lt/p&gt</p>
        <p title="hihi j'étais caché ">1- &ltp title="text en info bule"&gt Passe le curceur et voir &lt/p&gt</p>
        <p>1- &lt!-- write a comment --&gt</p>
        <p>2- &ltbr&gt Go to a <br> new line</p>
        <p>3- &lthr&gt tracer une ligne horizontal</p><hr>
        <pre>4- &ltpre&gt   un    paragraphe qui        garde 
             les espaces et les allés à la ligne &lt/pre&gt</pre>
        <strong>5- &ltstrong&gt Balise strong: A test in bold &lt/strong&gt</strong>
        <p>6-  text &ltspan&gt<span style="color:red;"> change style in a part of text </span>&lt/span&gt in red color</p>
        <style>
            #p-style{
                color: white;
                opacity: 0.5; /*Color opacity Between: [0, 1] */
                background-color: pink;
                font-family: verdana;/*Police du text: "Times New Roman",sans-serif*/ ;
                font-size: 2.5vh; /* Taille du text: */
                font-style: italic;/* normal, oblique, inherit;*/
                font-weight: bold; /* normal, lighter, bolder, inherit, initial */
                text-align: center; /*Position du text: left, right, justify, inherit */
                text-transform: capitalize;/* Text en lettre: lowercase, uppercase, inherit, none */
                text-decoration: underline;/* Soulignes: overline, line-through, inherit, initial, none */
                text-indent: 10px;/* Indenter le text de 10px de la ligne: [-100px, 100px] or [0%, 100%] */
                text-shadow: #000000 3vh 1px 2vh, #000000 -1px 1px 2vh, #000000 -1px -1px 2vh, #000000 1px -1px 2vh;/* horiz, vert, rayon=[-100px, 100px], color */
                text-height: 20px; /* Ecart entre les lignes */
                word-spacing: 10px;/* Ecart entre les mots */
                letter-spacing: 5px; /* Ecart entre les lettres */
            }   
        </style>
        <p id="p-style">7- Style of a text</p>
        <style>
            #div-style{
                width: 20vh; /* Largeur */
                height: 10vw; /* Hauteur */
                margin: auto auto auto auto;/* Marge externe: auto pour tout centrer */
                padding: 2% 2% 2% 2%;/* Marge interne: Top-Right-Bottom-Left */
                box-shadow: 5px 5px 2px pink;/* horiz, vert, rayon=[-100px, 100px], color */
                border-radius: 1vh 2vh 1vh 2vh;/* Rongner bord */
                border: 2px solid #6F00D2;/* Border: [2px, (double, ridge, inset, outset, groove, dashed, dotted), color] */
                overflow: scroll; /* visible, hidde, auto, initial, inherit */
                /*Hide the scroll bar*/
                -ms-overflow-style: none; /* Internet Explorer */
                scrollbar-width: none; /* Firefox */
                background-color:#D8D8EB;
            }
            #div-style::-webkit-scrollbar{ /* Hide scroll in Chrome */
                            display: none;
            }
        </style>
        <div id="div-style">Voila un text<br><br>qui prend plusieurs<br> ligne avec scroll<br><br><br>autre</div><br><hr><br>
        <style>
            #supperpose-div-style{
                width: 22vh; /* Largeur */
                height: 12vw; /* Hauteur */
                margin: auto auto auto auto;
                background-color:#005757;
            }
            #collerInDiv{
                width: 20vh; /* Largeur */
                height: 10vw; /* Hauteur */
                background-color:#808080;
            }
            /*  position: relative; top:-10vh; left: 15vh; flotter par rapport au premier parent
                position: absolue; top:10vh; left: 15vh; flotter par rapport à son ancètre premier
                z-index: a; pour le mettre en bas des frères lui attribuer la plus petite valeure 
                float: right; left; pour flotter l'element sur un coté dans son parent directe
                display: inline-block;=("inline-block : l'un a coté de l'autre et ocupe la plus petit espace",
                                         "block: affiché vertical et occupe tout"
                                         "inline:affiché verticale  */
            #floatteInDiv{
                width: 20vh; /* Largeur */
                height: 6vw; /* Hauteur */
                position: relative;
                top:-8vh; left: 5vh;
                background-color:#D8D8EB;
            }
        </style>
        <div id="supperpose-div-style">
            <div id="collerInDiv"></div>
            <div id="floatteInDiv">Je flotte</div>
        </div><br><hr><br>
            <!-- END -->
        <style>
            #profil-style{
                width: 20vh; /* Largeur */
                height: 22vw; /* Hauteur */
                margin: auto auto auto auto;
                background-color:#005757;
            }
            #picture{
                width: 20vh;
                height: 18vh;
                -webkit-border-radius: 12vh;
                -moz-border-radius: 12vh;
                border-radius: 12vh;
                background-color:#D8D8EB;
            }
            #pseudo{
                width: 20vh;
                height: 4vh;
                background-color:#5151A2
            }
        </style>
        <div id="profil-style">
            <div id="picture"></div>
            <div id="pseudo">Jean-Marie</div>
        </div><br><hr><br>

        <style>
            #container-right{
                width: 22vh; /* Largeur */
                height: 10vw; 
                margin: auto auto auto auto;
                background-color: #474e5d;
            }
            #right{
                width: 10vh; /* Largeur */
                height: 5vw; 
                margin:  0 0 0 auto;
                background-color: #D8D8EB;
            }
        </style>
        <div id="container-right">
            <div id="right">I'm in Right of this div</div>
        </div><br><hr><br>
         <style>
            #container-right-bottom1{
                width: 22vh; /* Largeur */
                height: 10vw; 
                margin: auto auto auto auto;
                position: relative;
                background-color: #474e5d;
            }
            #right-bottom1{
                width: 10vh; /* Largeur */
                height: 6vw; 
                position: absolute;
                right:0;
                bottom: 0;
                background-color: #D8D8EB;
            }
        </style>
        <div id="container-right-bottom1">
            <div id="right-bottom1">I'm in Right bottom of this div</div>
        </div><br><hr><br>
        <style>
            #container-left-bottom1{
                width: 22vh; /* Largeur */
                height: 10vw; 
                margin: auto auto auto auto;
                position: relative;
                background-color: #474e5d;
            }
            #left-bottom1{
                width: 10vh; /* Largeur */
                height: 6vw; 
                position: absolute;
                left:0;
                bottom: 0;
                background-color: #D8D8EB;
            }
        </style>
        <div id="container-left-bottom1">
            <div id="left-bottom1">I'm in Left bottom of this div</div>
        </div><br><hr><br>
        

       <style>
            #container-top-center1{
                width: 22vh; /* Largeur */
                height: 10vw; 
                margin: auto auto auto auto;
                background-color: #474e5d;
            }
            #top-center1{
                width: 10vh; /* Largeur */
                height: 5vw; 
                margin: auto;
                background-color: #D8D8EB;
            }
        </style>
        <div id="container-top-center1">
            <div id="top-center1">I'm in Top center of this div</div>
        </div><br><hr><br>
        <style>
            #container-center{
                width: 22vh; /* Largeur */
                height: 10vw; 
                margin: auto auto auto auto;
                display:flex;
                justify-content: center;
                align-items: center;
                background-color: #474e5d;
            }
            #center{
                width: 10vh; /* Largeur */
                height: 5vw;
                background-color: #D8D8EB;
            }
        </style>
        <div id="container-center">
            <div id="center">I'm in center of this div</div>
        </div><br><hr><br>
        <style>
            #container-right-center{
                width: 55vh; /* Largeur */
                height: 30vw; 
                margin: auto auto auto auto;
                position: relative;
                background-color: #474e5d;
            }
            #top-left{
                width: 10vh; /* Largeur */
                height: 6vw; 
                position: absolute;
                transform:translate(0%, 0%);
                background-color: #D8D8EB;
            }
            #top-center{
                width: 10vh; /* Largeur */
                height: 6vw; 
                position: absolute;
                left:50%;
                transform:translate(-50%, 0%);
                background-color: #D8D8EB;
            }
            #top-right{
                width: 10vh; /* Largeur */
                height: 6vw; 
                left:100%;
                position: absolute;
                transform:translate(-100%, 0%);
                background-color: #D8D8EB;
            }
            #bottom-center{
                width: 10vh; /* Largeur */
                height: 6vw; 
                position: absolute;
                top:100%;
                left:50%;
                transform:translate(-50%, -100%);
                background-color: #D8D8EB;
            }
            #left-center{
                width: 10vh; /* Largeur */
                height: 6vw; 
                position: absolute;
                top:50%;
                transform:translate(0%, -50%);
                background-color: #D8D8EB;
            }
            #center-center{
                width: 10vh; /* Largeur */
                height: 6vw; 
                position: absolute;
                top:50%;
                left:50%;
                transform:translate(-50%, -50%);
                background-color: #D8D8EB;
            }
            #right-center{
                width: 10vh; /* Largeur */
                height: 6vw; 
                position: absolute;
                top:50%;
                left:100%;
                transform:translate(-100%, -50%);
                background-color: #D8D8EB;
            }
            #bottom-left{
                width: 10vh; /* Largeur */
                height: 6vw; 
                position: absolute;
                top:100%;
                transform:translate(0%, -100%);
                background-color: #D8D8EB;
            }
            #bottom-right{
                width: 10vh; /* Largeur */
                height: 6vw; 
                position: absolute;
                top:100%;
                left:100%;
                transform:translate(-100%, -100%);
                background-color: #D8D8EB;
            }
        </style>
        <div id="container-right-center">
            <div id="top-left">Top Left</div>
            <div id="top-center">Top Center</div>
            <div id="top-right">Top Right</div>
            <div id="left-center">Left Center</div>
            <div id="center-center">Center Center</div>
            <div id="right-center">Right Center</div>
            <div id="bottom-left">Bottom Left</div>
            <div id="bottom-center">Bottom Center</div>
            <div id="bottom-right">Bottom Right</div>
        </div><br><hr><br>
     
        <style>
            #table-style{
                width: 70vh; 
                height: 5vw; 
                margin: auto auto auto auto;
                background-color:#005757;
            }
            .td-style{
                width: auto; /* Largeur */
                height: auto; /* Hauteur */
                border: 2px solid #6F00D2;
                background-color:#808080;
            }
            table{
                border-collapse: collapse;
            }
        </style>
        <div id="table-style">
            <table>
                <div>
                <tr>
                    <td><div class="td-style">Table 1</div></td>
                    <td><div class="td-style">Table 2</div></td>
                    <td><div class="td-style">Table 3</div></td>
                </tr>
                </div>
            </table>
        </div><br><hr><br>
        <!-- END -->
        <style>
            #list-li-style{
                width: 70vh; 
                height: 5vw; 
                margin: auto auto auto auto;
                background-color:#005757;
            }
            .li-style{
                width: auto; /* Largeur */
                height: auto; /* Hauteur */
                display:inline-block;
                border: 2px solid #6F00D2;
                background-color:#808080;
            }
            ul{
                padding:0px;
                border-collapse: collapse;
            }
        </style>
        <div id="list-li-style">
                <ul>
                    <li class="li-style"><div>Liste 1</div></li>
                    <li class="li-style"><div>Liste 2</div></li>
                    <li class="li-style"><div>Liste 3</div></li>
                </ul>
        </div><br><hr><br>
        
<style>
    table{
        margin: auto auto auto auto;
    }
    td,th{
   border : 1px solid black ;
}

</style>
<table>
    <thead>
           <tr>
                  <th>Matieres</th>
                  <th colspan="2">Note</th>
           </tr>
   </thead>
   <tbody>
           <tr>
                  <td>Math</td>
                  <td rowspan="2">15</td>
                  <td>13</td>
           </tr>
           <tr>
                  <td>SVT</td>
                  <td>12</td>
           </tr>

     </tbody>

   
   <tfoot>
           <tr>
                  <td>Moyenne</td>
                  <td>15</td>
                  <td>12.5</td>
           </tr>
     </tfoot>
</table><br><hr><br>


        <style>
            #grid-style{
                width: 70vh; 
                height: 5vw; 
                display: grid;
                grid-template-columns: 1fr 1fr 1fr;
                margin: auto auto auto auto;
                background-color:#005757;
            }
            .element{
                width: auto; /* Largeur */
                height: auto; /* Hauteur */
                border: 2px solid #6F00D2;
                background-color:#808080;
            }
        </style>
        <div id="grid-style">
            <div class="element">Gride 1</div>
            <div class="element">Gride 2</div>
            <div class="element">Gride 3</div>
            <div class="element">Gride 4</div>
            <div class="element">Gride 5</div>
        </div>
        <br><hr><br>
        <style>
            #grid1-style{
                width: 70%; 
                height: 5vw; 
                display: flex;
                margin: auto auto auto auto;
                background-color:#005757;
            }
            .elt1{
                flex: auto;
                border: 2px solid #6F00D2;
                background-color:#808080;
            }
            .elt2{
                flex: auto;
                border: 2px solid #6F00D2;
                background-color:#808080;
            }
            .elt3{
                flex: auto;
                border: 2px solid #6F00D2;
                background-color:#808080;
            }
        </style>
        <div id="grid1-style">
            <div class="elt1">Gride 1</div>
            <div class="elt2">Gride 2</div>
            <div class="elt3">Gride 2</div>
        </div>
        <br><hr><br>
        <style>
            #grid2-style{
                width: 70%; 
                display: flex;
                margin: auto auto auto auto;
                background-color:#005757;
            }
            .elt11{
                flex: 50%;
                border: 2px solid #6F00D2;
                background-color:#808080;
            }
            .elt21{
                flex: 10%;
                border: 2px solid #6F00D2;
                background-color:#808080;
            }
            .elt31{
                flex: 30%;
                border: 2px solid #6F00D2;
                background-color:#808080;
            }
        </style>
        <div id="grid2-style">
            <div class="elt11">Gride 1</div>
            <div class="elt21">Gride 2</div>
            <div class="elt31">Gride 2</div>
        </div>
        <br><hr><br>

        <style>
            #goback, #gosignin, #gosignup{
                color: white;
                padding: 1.5vh 1vh 1.5vh 1vh ;
                font-size: 2.4vh;
                border: none;
                cursor: pointer;
                width: 12vh;
                opacity: 0.9;
                border-radius: 1vh;
                border: 0.4vh outset #c0c0c0;
              }
            #redirect{
                width: 70%; 
                display: flex;
                margin: auto auto auto auto;
                background-color:#005757;
            }
            #redi1{
                flex: 33.33vh;
            }
            #redi2{
                flex: 33.33vh;
                position: relative;
            }
            #redi3{
                flex: 33.33vh;
                position: relative;
            }
            #goback {
                background-color: #cc9724;
            }
            #gosignup{
                text-decoration: none;
                position: absolute;
                top:50%;
                left:50%;
                transform:translate(-50%, -50%);
                background-color: #0080FF;
            }
            #gosignin{
                text-decoration: none;
                position: absolute;
                top:50%;
                left:100%;
                transform:translate(-100%, -50%);
                background-color: #4CAF50;
            }
        </style>
            <div id="redirect">
                <div id="redi1"><button type="button" id="goback">Button</button></div>
                <div id="redi2"><a id="gosignup" href="#">Elementa</a></div>
                <div id="redi3"><a id="gosignin" href="#">Elementa</a></div>
              </div>
        <br><hr><br>
    </body>
</html>


