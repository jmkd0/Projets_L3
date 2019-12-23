import {users, rotation} from './match.js'

export class Users{
  constructor(index,nbreProfil, newContener,contenerDrag){
    this.index=index
    this.nbreProfil=nbreProfil
    this.newContener=newContener
    this.contenerDrag=contenerDrag
    this.drag=true
  }
  suivantPrecedent(){
  let i;
  if(this.index>this.nbreProfil) this.index=1
  if(this.index<1) this.index=this.nbreProfil
  let imageContener=document.createElement("div");
  let p=document.createElement('p')
  let pn=document.createTextNode("Da Silva  25ans   reside à Aubervillier");
  p.appendChild(pn)
  p.style.color="white"
  let descProfil=document.createElement("div")
  descProfil.appendChild(p)
  descProfil.className="descprofil"
  let img=document.createElement('img')
  img.appendChild(descProfil)
  img.style.width="100%"
  img.style.height="100%"
  img.src="../images/image"+this.index+".jpg"
  imageContener.appendChild(descProfil)
  imageContener.appendChild(img)
  if(this.drag==true){
  this.contenerDrag.removeChild(this.contenerDrag.firstChild)
  this.contenerDrag.appendChild(imageContener)
  }else{
    this.newContener.removeChild(this.newContener.firstChild)
  this.newContener.appendChild(imageContener)
  }
  this.index++
this.contenerDrag.className="drag"
this.newContener.className="drag"
}
}


export class Rotation{
  constructor(cadre, a, b, y, x0, y0){
    this.cadre=cadre
    this.a=a
    this.b=b
    this.y=y
    this.x0=x0
    this.y0=y0
    this.x=1
    this.angle=0
    this.ang1=0
    this.ang2=0
    this.valeurAngle=0
    this.dragged=null
  }
  setX(event){
    if(event.touches){
        this.x = event.touches[0].clientX + (document.documentElement.scrollLeft + document.body.scrollLeft);
        }else{
        this.x = event.clientX + (document.documentElement.scrollLeft + document.body.scrollLeft);
     }
}
setAngle(){
    this.valeurAngle=(Math.atan((this.b-this.y)/(this.x-this.a)))*180/Math.PI
    }
onStart(event){
  event.returnValue = false;
  this.dragged = users.contenerDrag;
  this.setX(event) 
  this.setAngle()
  this.ang1=this.valeurAngle
  if(this.x-this.a<0) this.ang1-=180
  users.drag=false
  users.suivantPrecedent()
  event.preventDefault();
}
onMove(event){
if( this.dragged ) {  
  this.setX(event) 
  this.setAngle()
    this.ang2=this.valeurAngle
   if(this.x-this.a<0) this.ang2-=180
   this.angle=this.ang1-this.ang2;
   users.contenerDrag.style.transformOrigin=this.x0+"px "+this.y0+"px";
   users.contenerDrag.style.transform="rotate("+this.angle+"deg)";
  }
}
onUp(event){
if(this.dragged){
  this.dragged = null;
this.setAngle()
    let angleRetour=this.valeurAngle
    if(this.x-this.a<0) angleRetour=-angleRetour-90
    if(this.x-this.a>0) angleRetour=90-angleRetour
   if(angleRetour<15 && angleRetour>-15){ 
    users.contenerDrag.style.transform="rotate("+0+"deg)";
    users.index-=2
    users.drag=true
    users.suivantPrecedent() 
  }else{
      users.contenerDrag.remove()
      rotation.cadre.appendChild(users.contenerDrag)
      users.index--
      users.drag=true
      users.suivantPrecedent()
      users.contenerDrag.style.transform="rotate("+0+"deg)"
     if(angleRetour<0){
      console.log("dragg gauche")
    }else console.log("dragg droite")
     }
  }
}
}
