let newCadre=new CadreView()
let procheDiv=document.createElement('div')
procheDiv.className="prochediv"
let i

let nobreUserProche=13
for(i=1; i<=nobreUserProche; i++){
    let fig=document.createElement('figure')
    let figc=document.createElement('figcaption')
    let procheDivi=document.createElement('div')
    let img=document.createElement('img')
    let p=document.createElement('p')
    let pn=document.createTextNode("johnson");
    p.appendChild(pn)
    figc.appendChild(p)
    p.style.color="black"
    
    procheDivi.className="prochedivi"
    img.src="../images/image"+i+".jpg"
    
    procheDivi.appendChild(img)
    fig.append(procheDivi, figc)
    procheDiv.appendChild(img)
    
    
}

newCadre.cadreDrag.appendChild(procheDiv)
function onClick(element, index){
    element.addEventListener('mousedown',(event)=>{
        profilMatchs.index=index
    console.log("jghjk")
    element.href="../html/match.html"
}, true);
    
}