let newCadre=new CadreView()
let divChat=document.createElement('div')
let discussArea=document.createElement('div')
discussArea.className="discussarea"
divChat.className="divchat";
let form=document.getElementById("form-chat")
divChat.append(discussArea, form)
newCadre.cadreDrag.append(divChat);
class Chat{
    constructor(model){
        this.model      = model;
        this.ulMessage  =document.createElement('ul');
        this.send;
        this.receive;
        this.messages   =[];
        this.init();
    }
    init(){
        this.ulMessage.className="ulmessage";
        discussArea.appendChild(this.ulMessage);
    }
    sendMessage(value){
        this.model.sendMessage(value);
        let liMessage=document.createElement('li');
        liMessage.className="limessage1";
        liMessage.innerHTML=value;
        this.ulMessage.appendChild(liMessage);
    }
    
    
   setMessage(){
        let liMessage=document.createElement('li');
        liMessage.className="limessage2";
        
          liMessage.innerHTML=  this.receive;
        
        this.ulMessage.appendChild(liMessage);
   }
}
let chat= new Chat(new Model);
//let socket = io.connect('http://localhost:8080');
socket.on('server-send-message', function(receive) {
    chat.setMessage();
    chat.receive= receive;
  })

function valider(formular){
    let text=formular.message.value;
    chat.sendMessage(text);
}

