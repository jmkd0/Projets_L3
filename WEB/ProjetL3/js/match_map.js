import {CadreView} from './cadre.js'
//import {profilMatchs} from './match.js'
//export let index=1
let index
let newCadre=new CadreView()
let indexes=[]
let nobreUserProche=13
let i
for(i=1; i<=nobreUserProche; i++) indexes.push(i)

let procheDiv=document.createElement('div')
procheDiv.className="prochediv"

indexes.forEach(function(imageName, index, originalArray){
   
  })
 //profilMatchs.index=9
for(i=1; i<=nobreUserProche; i++){
    let fig=document.createElement('figure')
    let figc=document.createElement('figcaption')
    let element=document.createElement('a')
    //profilMatchs.index=i
    element.href="../html/match.html"
    let img=document.createElement('img')
    let p=document.createElement('p')
    let pn=document.createTextNode("johnson")
    p.appendChild(pn)
    figc.appendChild(p)
    p.style.color="black"
    //profilMatchs.index=i
    //procheDivi.className="prochedivi"
    img.src="../images/image"+i+".jpg"
  
    element.appendChild(img)
    //fig.append(procheDivi, figc)
    procheDiv.appendChild(element)
    
    
}
console.log(index)
//newCadre.removeChild(newCadre.firstChild)
let fils=procheDiv.children
for(i=1; i<=nobreUserProche; i++){
    /*fils[i].addEventListener('mousedown', (event)=>{
        console.log(i)
    })*/

}
//let fils=procheDiv.childElementCount
//console.log(fils)
newCadre.cadreDrag.appendChild(procheDiv)
