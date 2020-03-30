window.addEventListener("load", event => {
	console.log("loaded");
	main();
});

const main = event => {
	
	console.log("MAIN");
	var  tab= ["Liste une", "Liste deux", "Liste trois", "Liste quatre","Liste Cinq","Liste Six","Liste sept","Liste huit","Liste neuf","Liste dix"];

	let component = new MyComponent("dummy");
  let myElement=document.createElement("div");

	document.body.appendChild(myElement);
	myElement.style.width="75%";
	myElement.style.height="100%";
let list1=document.createElement("ul");
    list1.style.width="320px";
    list1.style.height="500px";
    list1.style.padding="10px";
    list1.style.backgroundColor="#D9B3B3";
    let list2=document.createElement("ul");
    list2.style.width="320px";
    list2.style.height="500px";
    list2.style.padding ="10px";
    list2.style.backgroundColor="#D9B3B3";
    list1.style.display="inline-block";
    list2.style.display="inline-block";
    list2.style.float="right";
	myElement.style.backgroundColor="#FFECEC";


 tab.forEach(function(nom, index, originalArray){
      addElementToDocFragment(nom);
    })
 for(let i=0; i<tab.length;i++){
 	let elementListVirtuel=document.createElement("li");
 	var text1=document.createTextNode(" .");
    elementListVirtuel.style.padding ="15px 10px";
    elementListVirtuel.style.listStyleType = "none";
    elementListVirtuel.className="virtuel";
    elementListVirtuel.appendChild(text1);
 	list2.appendChild(elementListVirtuel);
 }
 let currentElementList=null;
 setInterval(()=>{
 	for(let i=0; i<tab.length; i++){
 		if(Collision(currentElementList,elementListVirtuel[i])){
         	elementListVirtuel.style.backgroundColor="#E0E0E0";
 		}
 	}
 },100);
 	myElement.appendChild(list1);
	myElement.appendChild(list2);
let Collision=function(item1, item2){
	item1.offsetBottom=item1.offtsetTop+item1.offsetHeight;
	item1.offsetRight=item1.offtsetLeft+item1.offsetWidth;
	item2.offsetBottom=item2.offtsetTop+item2.offsetHeight;
	item2.offsetRight=item2.offtsetLeft+item2.offsetWidth;
	return !((item1.offsetBottom<item2.offtsetTop)||
		     (item1.offtsetTop>item2.offsetBottom)||
		     (item1.offsetRight< item2.offtsetLeft)||
		     (item1.offtsetLeft > item2.offsetRight))
};
function addElementToDocFragment(nom){
  myElement.addEventListener("click",onClick);
	var active = false;
var dragged=null;
	var text=document.createTextNode(nom);
	let elementList=document.createElement("li");
	let ongletList=document.createElement("div");
	ongletList.style.padding ="4px 4px";
    ongletList.style.width="10px";
    ongletList.style.height="10px";
    ongletList.style.backgroundColor="#272727";
    ongletList.style.float="right";
    elementList.appendChild(ongletList);
    elementList.style.backgroundColor="#E0E0E0";
    elementList.style.padding ="15px 10px";
    elementList.style.listStyleType = "none";
    elementList.addEventListener("mousedown",(e)=>{
      dragStart(e,elementList);}, true)
    //elementList.addEventListener("mousedown", (e)=>{dragStart(e); currentElementList=elementList;}, false);
    elementList.addEventListener("mousemove", drag, true);
    elementList.addEventListener("mouseup", dragEnd,true);
    elementList.addEventListener("mouseover",()=>{
    elementList.style.backgroundColor="#6C6C6C";
    })
    elementList.addEventListener("mouseout",()=>{
    elementList.style.backgroundColor="#E0E0E0";
    })

    elementList.appendChild(text)
  list1.appendChild(elementList);
  
	function dragStart(e, elementList) {
    dragged=elementList;
    }

    function dragEnd(e) {
      dragged=null;
    }

    function drag(event) {
      if( dragged) //s'il n'y a pas d'élément en cours de déplacement, inutile de le déplacer :) 
  {
    var x = event.clientX;
    var y = event.clientY;
    dragged.style.position = 'absolute';
    dragged.style.left = x + 'px';
    dragged.style.top = y + 'px';
  }
    }
  }
	

	

}


function deplaceOnglet(ongletList){
	ongletList.style.backgroundColor="#00DB00";
	ongletList.addEventListener("mousemove",()=>{
       ongletList.style.backgroundColor="#FF0000";
	});
}
	const onClick=event=>{
		console.log("clicked");
		console.log("Event");
	}

	
class MyComponent {
	
	constructor(name) {
		console.log("my name is", name);
	}
	
}