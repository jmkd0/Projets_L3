export class NewCadre{
    constructor(){
      this.cadreDrag=document.createElement("div")
      let cadre=document.createElement("div")
      let cadreTete=document.createElement("div")
      
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
      
      aGlobe.href="../html/profil_user.html"
      aMache.href="../html/match.html"
      aProfil.href="../html/profil_user.html"
  
  
      aGlobe.appendChild(imgGlobe)
      aMache.appendChild(imgMache)
      aProfil.appendChild(imgProfil)
      navigation.appendChild(aGlobe)
      navigation.appendChild(aMache)
      navigation.appendChild(aProfil)
      cadre.appendChild(cadreTete)
      cadre.appendChild(this.cadreDrag)
      cadre.appendChild(navigation)
      document.body.appendChild(cadre)
  
      cadreTete.className="cadretete"
      this.cadreDrag.className="cadredrag"
      navigation.className="navigation"
      cadre.className="cadre"
  
    }
  }