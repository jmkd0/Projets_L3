class CadreView{
    constructor(){
      this.cadreDrag=document.createElement("div")
      this.cadre=document.createElement("div")
      this.cadreTete=document.createElement("div")
      
      let navigation=document.createElement("div")
      let aGlobe=document.createElement("a")
      let aProfil=document.createElement("a")
      let aMache=document.createElement("a")
      
      let imgGlobe=document.createElement("img")
      let imgProfil=document.createElement("img")
      let imgMache=document.createElement("img")
      
      imgGlobe.src="../images/icone_globe.jpg"
      imgMache.src="../images/icone_match.jpg"
      imgProfil.src="../images/icone_profil.png"
      
      aGlobe.href="../client/match_map.html"
      aMache.href="../client/match.html"
      aProfil.href="../client/profil_user.html"
  
      aGlobe.className="aglobe"
      aProfil.className="aprofil"
      aMache.className="amache"
      
      aGlobe.appendChild(imgGlobe)
      aMache.appendChild(imgMache)
      aProfil.appendChild(imgProfil)
      navigation.append(aGlobe,aMache,aProfil)
    
      this.cadre.append(this.cadreTete, this.cadreDrag, navigation)
   
      document.body.appendChild(this.cadre)
  
      this.cadreTete.className="cadretete"
      this.cadreDrag.className="cadredrag"
      navigation.className="navigation"
      this.cadre.className="cadre"
  
    }
  }