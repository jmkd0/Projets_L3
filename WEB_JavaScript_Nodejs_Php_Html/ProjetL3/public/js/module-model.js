let socket = io.connect('http://localhost:8080');
class Model{
    constructor(){
      //this.url='http://localhost:8080';
      //this.socket = io.connect(this.url);
      this.geolocalisation();
      //this.val="moins"
    }
    dragSend(drag){
      //let socket = this.socket;
      socket.emit('send-drag', drag);
    }
    infosFreinds=function(){
       //let socket=this.socket;
      return new Promise(function(resolve){
        socket.on('send-data', function(receive) {
          //console.log(val)
          for(let i=0; i<receive.length; i++){
            profilMatchs.response[i]={
              id:     receive[i].id,
              pseudo: receive[i].pseudo,
              age:    receive[i].age+" ans",
              region: 'Reside à '+receive[i].region,
              description: receive[i].description
            }
            
        }
        resolve()
      })
      })
    }
   sendMessage= function(message){
    //let socket = io.connect('http://localhost:8080');
    socket.emit('client-send-message', message);
   }
    infosNearFreinds=function(){
        //let socket=this.socket;
       return new Promise(function(resolve){
         socket.on('send-near-users', function(receive) {
           for(let i=0; i<receive.length; i++){
            nearOnMap.response[i]={
               id:        receive[i].id,
               pseudo:     receive[i].pseudo,
               distance:   receive[i].distance
             }
         }
         resolve()
       })
       })
     }
     infoMainUser=function(){
      //let socket=this.socket;
     return new Promise(function(resolve){
       socket.on('main-user-data', function(receive) {
          mainUser.response={
             id:            receive.id,
             pseudo:        receive.pseudo,
             age:           receive.age+" ans",
             region:        "Vous résidez à"+receive.region,
             phone:         receive.phone,
             description:   receive.description
           }
       resolve()
     })
     })
   }
     
  geolocalisation= function(){
    if(navigator.geolocation){
      navigator.geolocation.getCurrentPosition(this.geo)
    }else console.log("your browser has refused !")
  }
  geo = function( position){
    let local={
      latt: position.coords.latitude,
      long: position.coords.longitude
    }
    //let socket = io.connect('http://localhost:8080');
    socket.emit('send-location', local);
  }
  
  }