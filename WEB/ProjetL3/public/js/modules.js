class ProfilMatchView{
  constructor(index, model){
    this.response=[]
    this.index=index-1
    this.nbreProfil
    this.newContener=document.createElement("div")
    this.contenerDrag=document.createElement("div")
    this.model=model
    this.drag=true;
    this.chargeModel();
    
  }
  async chargeModel(){
    await this.model.infosFreinds();
    this.nbreProfil=this.response.length;
    this.init();
  }

  init(){
    this.contenerDrag.style.position='absolute';
    this.newContener.style.position='absolute';
    this.contenerDrag.style.zIndex=3
    this.newContener.style.zIndex=2
    this.newContener.appendChild(document.createElement('li'))
    this.contenerDrag.appendChild(document.createElement('li'))
    this.drag=false
    this.suivantPrecedent()
    this.drag=true
    this.suivantPrecedent()
  }
  
  suivantPrecedent(){
  if(this.index>this.nbreProfil-1) this.index=0
  //if(this.index<1) this.index=this.nbreProfil
  let imageContener=document.createElement("div");
  let descProfil=document.createElement("div")
  let img=document.createElement('img')
  this.creerImage(img, imageContener, descProfil);
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
 creerImage(img, imageContener, descProfil){
  let pseudoProfil=document.createElement("div")
  let ageProfil=document.createElement("div")
  let regionProfil=document.createElement("div")
  let commentProfil=document.createElement("div")
  let i=this.index
 pseudoProfil.innerHTML=this.response[i].pseudo;
 ageProfil.innerHTML=this.response[i].age;
 regionProfil.innerHTML=this.response[i].region;
 commentProfil.innerHTML="J'aime faire le sport, danser"+
 "Je suis passioné des nouvelles technologies"+
 "Je IYTGOUHOPUYTIRTUYUHHIOUGUH"
 +"huohhpdusqbuihpeiqyfbrehfnreufoerj^ni^"+this.response[i].description;
 pseudoProfil.className="textstyle";
  ageProfil.className="textstyle";
  regionProfil.className="textstyle";
  commentProfil.className="commentstyle";
  descProfil.append(pseudoProfil, ageProfil, regionProfil,commentProfil);
  descProfil.className="descprofil"
  img.className="imagedrag";
  img.src="../images/image"+i+".jpg"
  imageContener.append(descProfil, this.iconeChat())
  imageContener.appendChild(img)

}
iconeChat(){
  
  let aChat=document.createElement('a')
  let imgIcone=document.createElement('img')
  aChat.href="../client/chat.html";
  imgIcone.className="iconechat";
  imgIcone.src="../images/icon_chat.jpg"
  aChat.appendChild(imgIcone)
  return aChat;
}
}
class UsersCadreView extends CadreView{
  constructor(){
    super();
    this.a=this.cadreDrag.getBoundingClientRect().left+(document.documentElement.scrollLeft + document.body.scrollLeft)+this.cadreDrag.offsetWidth/2,
    this.b=this.cadreDrag.getBoundingClientRect().top+(document.documentElement.scrollTop + document.body.scrollTop)+this.cadreDrag.offsetHeight,    
    this.x0=this.cadreDrag.offsetWidth/2
    this.y0=this.cadreDrag.offsetHeight*2
    this.x=1
    this.cadreDrag.appendChild(profilMatchs.newContener)
    this.cadreDrag.appendChild(profilMatchs.contenerDrag)
    this.addEvent()
    
  }
addEvent(){
  profilMatchs.contenerDrag.addEventListener('mousedown',(event)=>{
    controlCadre.onStart(event);}, true);
   document.addEventListener('mousemove',(event)=>{
     controlCadre.onMove(event)},true);
   document.addEventListener('mouseup',(event)=>{
     controlCadre.onUp(event, profilMatchs.contenerDrag)},true);
   profilMatchs.contenerDrag.addEventListener('touchstart',(event)=>{
    controlCadre.onStart(event);}, true);
   document.addEventListener('touchmove',(event)=>{
     controlCadre.onMove(event)},true);
   document.addEventListener('touchend',(event)=>{
     controlCadre.onUp(event, conteneur)},true);
}
rotation(element, x, y, degre){
  element.style.transformOrigin=x+"px "+y+"px";
  element.style.transform="rotate("+degre+"deg)";
}
}

class CadreController{
  constructor(userCadreView, model){
    this.userCadreView=userCadreView;
    this.model=model;
    this.b=this.userCadreView.b
    this.a=this.userCadreView.a
    this.x=this.userCadreView.x
    this.y=1 
    this.x0=this.userCadreView.x0
    this.y0=this.userCadreView.y0
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
    this.dragged = profilMatchs.contenerDrag;
    this.setX(event) 
    this.setAngle()
    this.ang1=this.valeurAngle
    if(this.x-this.a<0) this.ang1-=180
    profilMatchs.drag=false
    profilMatchs.suivantPrecedent()
    event.preventDefault();
  }
  onMove(event){
  if( this.dragged ) {  
    this.setX(event) 
    this.setAngle()
      this.ang2=this.valeurAngle
     if(this.x-this.a<0) this.ang2-=180
     this.angle=this.ang1-this.ang2;
     this.userCadreView.rotation(profilMatchs.contenerDrag, this.x0, this.y0, this.angle)
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
      this.userCadreView.rotation(profilMatchs.contenerDrag, this.x0, this.y0, 0)
      profilMatchs.index-=2
      profilMatchs.drag=true
      profilMatchs.suivantPrecedent() 
    }else{
        profilMatchs.contenerDrag.remove()
        controlCadre.userCadreView.cadreDrag.appendChild(profilMatchs.contenerDrag)
        profilMatchs.index--
        profilMatchs.drag=true
        profilMatchs.suivantPrecedent()
        this.userCadreView.rotation(profilMatchs.contenerDrag, this.x0, this.y0, 0);
        let i= profilMatchs.index-2;
        let drag={
          to:     i,
          pseudo: profilMatchs.response[i].pseudo,
          type:   null
        };
       if(angleRetour<0){
         //drag left
         drag.type="left";
        }else{
        //dragg right
          drag.type="right";   
      }
      this.model.dragSend(drag);
       }
    }
  }
}


