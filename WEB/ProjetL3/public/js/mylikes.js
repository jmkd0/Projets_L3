let newCadre=new CadreView()
class Likes{
    constructor(){
        this.ulLikes  =document.createElement('ul');
        this.receive;
        this.init();
    }
    init(){
        this.ulLikes.className="ullikes";
        newCadre.cadreTete.innerHTML="My Likes and Matches";
        newCadre.cadreDrag.appendChild(this.ulLikes);
    }
   setLike(){
        let liLikes=document.createElement('li');
        if(this.receive.type==="right"){
            liLikes.className="lilikes";
            liLikes.innerHTML= this.receive.pseudo+"  a été liké";
            this.ulLikes.appendChild(liLikes);
        } 
   }
}
let likes= new Likes();
//let socket = io.connect('http://localhost:8080');
socket.on('send-likes', function(receive) {
    likes.receive= receive;
    likes.setLike();
    
  })
