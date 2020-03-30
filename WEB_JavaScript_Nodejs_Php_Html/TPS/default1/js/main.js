window.addEventListener("load", event => {
	console.log("loaded");
	main();
});

const main = event => {
  let component = new MyComponent("dummy");
  let myElement=document.createElement("div");
  var canvas=document.createElement("canvas");
  myElement.style.width="75%";
  myElement.style.height="75%";
  myElement.style.backgroundColor="#FFECEC";
  myElement.addEventListener("click",onClick);
  let P1={x:4,y:10};
  let P2={x:5,y:6};
  let P3={x:7,y:63};
  let coordonnes=coorCercle(P1,P2,P3);
  let cx=coordonnes[0];
  let cy=coordonnes[1];
  let ray=coordonnes[2];
  console.log(cx);
  console.log(cy);
  console.log(ray);
  cercleDraw(cx,cy,ray);
  myElement.appendChild(canvas);
  document.body.appendChild(myElement);
  function cercleDraw(X,Y,R){
    var ctx = canvas.getContext('2d'); 
    ctx.beginPath();
    ctx.arc(X, Y, R, 0, 2 * Math.PI, false);
    ctx.lineWidth = 3;
    ctx.strokeStyle ="#000";
    ctx.stroke();
    }
}

function coorCercle( P1, P2, P3){
  let a1=-((P2.x-P1.x)/(P2.y-P1.y));
  let a2=-((P3.x-P2.x)/(P3.y-P2.y));
  let b1=(Math.pow(P2.x,2)-Math.pow(P1.x,2)+Math.pow(P2.y,2)-Math.pow(P1.y,2))/(2*(P2.y-P1.y));
  let b2=(Math.pow(P3.x,2)-Math.pow(P2.x,2)+Math.pow(P3.y,2)-Math.pow(P2.y,2))/(2*(P3.y-P2.y));
  let cx=(b1-b2)/(a2-a1);
  let cy=a1*cx+b1;
  let ray=Math.sqrt(Math.pow(P1.x-cx,2)+Math.pow(P1.y-cy,2));
  return [cx, cy, ray];

}
coordCercle(0,10,5,-6,7,63);
function coordCercle(x1,y1,x2,y2,x3,y3){
  let X=((x3*x3-x2*x2+y3*y3-y2*y2)/(2*(x3-y2))-(x2*x2-x1*x1+y2*y2-y1*y1)/(2*(y2-y1)))/((x3-x2)/(y3-y2)-(x2-x1)/(y2-y1));
  let Y=-(x2-x1)/(y2-y1)*X+(x2*x2-x1*x1+y2*y2-y1*y1)/(2*(y2-y1));
  let R=Math.sqrt((x1-X)*(x1-X)+(y1-Y)*(y1-Y));
  return [X, Y, R];
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