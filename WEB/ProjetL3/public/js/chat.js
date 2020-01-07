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
        this.model= model;
        this.send;
        this.receive;
        this.messages=[];
        this.sendMessage()

    }
    init(){
        let ul=document.createElement('ul');
        let divMessage=document.createElement('sdiv');

        
    }
    sendMessage(){
        let button= document.getElementsByClassName("submiter");
        let message= document.getElementsByClassName("message");
        //let button= document.getElementById('idsubmiter')
        button.onclick=function(){
            
            console.log("jfkglh:j")
            //this.model.sendMessage()
            }
        console.log("hghc,tug")
    }
}
let chat= new Chat(new Model);