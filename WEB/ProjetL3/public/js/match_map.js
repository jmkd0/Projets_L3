let newCadre=new CadreView()
let descripTete=document.createElement('div');
descripTete.innerHTML="This users are near by you";
descripTete.className="descriptete"
newCadre.cadreTete.appendChild(descripTete);
class NearOnMap{
    constructor(model){
        this.response=[]
        this.nbreConnectNear;
        this.model= model;
        this.chargeModel();
    }
    async chargeModel(){
        await this.model.infosNearFreinds();
        this.nbreConnectNear = this.response.length;
        
        this.displayNearUsers();
    }
    displayNearUsers(){
        let procheDiv=document.createElement('div')
        procheDiv.className="prochediv"
        for(let i=0; i< this.nbreConnectNear; i++){
            let aDivi=document.createElement('a')
            let index=this.response[i].id-1;
            console.log(index)
            this.createNearUser(aDivi, index , this.response[i].pseudo, this.response[i].distance);
            procheDiv.appendChild(aDivi)   
        }
        newCadre.cadreDrag.appendChild(procheDiv)
    }
    createNearUser(aDivi, i, pseudo, distance){
        let procheDivi=document.createElement('div')
        let procheIcone=document.createElement('div')
        let prochePseudo=document.createElement('div')
        let procheDistance=document.createElement('div')
        let connectDivi=document.createElement('div')
        let img=document.createElement('img')
        img.src="../images/image"+i+".jpg"
        aDivi.href="../client/match.html?index="+i;
        procheDivi.className="prochedivi"
        procheIcone.className="procheicone"
        prochePseudo.className="prochepseudo"
        procheDistance.className="prochedistance"
        connectDivi.className="connectdivi"
        aDivi.style.textDecoration="none"
        img.className="imgicone"
        prochePseudo.innerHTML=pseudo;
        procheDistance.innerHTML=distance+" km";
        prochePseudo.appendChild(connectDivi)
        procheIcone.appendChild(img)
        procheDivi.append(procheIcone, prochePseudo, procheDistance)
        aDivi.appendChild(procheDivi)
    }
}
let nearOnMap =new NearOnMap(new Model());


