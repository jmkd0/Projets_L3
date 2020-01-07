let newCadre=new CadreView()
/* User Picture */
let userImageContener=document.createElement('div')
let img=document.createElement('img');
img.src="../images/image"+0+".jpg"
img.className="imguser";
userImageContener.className="userimagecontener";
userImageContener.appendChild(img);
/* Users pseudo, age and description */
let descProfilUser=document.createElement('div')
let pseudoProfil=document.createElement("div")
let ageProfil=document.createElement("div")
let regionProfil=document.createElement("div")
pseudoProfil.innerHTML='Da Silva';
ageProfil.innerHTML='24ans';
regionProfil.innerHTML='Je suis passionné des nouvelles technos';

pseudoProfil.className="textstyleuser";
ageProfil.className="textstyleuser";
regionProfil.className="textstyleuser";
descProfilUser.className="descprofiluser";
descProfilUser.append(pseudoProfil, ageProfil, regionProfil);
/* Buttons My Like and My Discussions */
let discuLikes=document.createElement('div')
discuLikes.className="disculikes";
let myLikesDiv=document.createElement("div")
let myDiscusDiv=document.createElement("div")

let myLikes=document.createElement("a")
let myDiscus=document.createElement("a")
myLikesDiv.appendChild(myLikes);
myDiscusDiv.appendChild(myDiscus);
myLikes.innerText="My Likes";
myDiscus.innerText="My Discussions";
myLikes.href="../client/mylikes.html"
//myDiscus.href="../client/discussions.html"
myDiscus.href="../client/chat.html"
myLikes.className="mylikes";
myDiscus.className="mydiscus";
myLikesDiv.className="mydiscuslikesdiv";
myDiscusDiv.className="mydiscuslikesdiv";
discuLikes.append(myLikesDiv, myDiscusDiv);
newCadre.cadreDrag.append(userImageContener, descProfilUser, discuLikes);