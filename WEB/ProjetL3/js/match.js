import { Users, Rotation} from './modules.js'
import {NewCadre} from './cadre.js'

  export let  users= new Users(
          1, 
          6,
          document.createElement("div"),
          document.createElement("div")
    )
  
   
    let newCadre=new NewCadre()

    export let rotation= new Rotation(
      newCadre.cadreDrag,
      newCadre.cadreDrag.getBoundingClientRect().left+(document.documentElement.scrollLeft + document.body.scrollLeft)+newCadre.cadreDrag.offsetWidth/2,
      newCadre.cadreDrag.getBoundingClientRect().top+(document.documentElement.scrollTop + document.body.scrollTop)+newCadre.cadreDrag.offsetHeight,
      1,
      newCadre.cadreDrag.offsetWidth/2,
      newCadre.cadreDrag.offsetHeight*2
    )
   
    users.newContener.appendChild(document.createElement('li'))
    users.contenerDrag.appendChild(document.createElement('li'))
    users.drag=false
    users.suivantPrecedent()
    users.drag=true
    users.suivantPrecedent()
    addEvents();
    users.contenerDrag.style.position='absolute'
    users.newContener.style.position='absolute'
    users.contenerDrag.style.zIndex=3
    users.newContener.style.zIndex=2
    rotation.cadre.appendChild(users.newContener)
    rotation.cadre.appendChild(users.contenerDrag);


    function addEvents(){
      users.contenerDrag.addEventListener('mousedown',(event)=>{
       rotation.onStart(event);}, true);
      document.addEventListener('mousemove',(event)=>{
        rotation.onMove(event)},true);
      document.addEventListener('mouseup',(event)=>{
        rotation.onUp(event, users.contenerDrag)},true);


      users.contenerDrag.addEventListener('touchstart',(event)=>{
       rotation.onStart(event);}, true);
      document.addEventListener('touchmove',(event)=>{
        rotation.onMove(event)},true);
      document.addEventListener('touchend',(event)=>{
        rotation.onUp(event, conteneur)},true);
    }
    