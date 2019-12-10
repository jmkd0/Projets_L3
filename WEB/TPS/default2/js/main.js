

window.addEventListener("load", event => {
	console.log("loaded");
	main();
});

let tab=new Array();


async function  findUsersByAge(users,age){
  await sleep(50);
  return users.filter(user=>user.age> age);
}
  async function main(){

    for(let i=0; i<500; i++){
      let userObject={
        firstName:faker.fake("#{name.firstName}"),
        lastName:faker.fake("#{Name.last_name}"),
        country:faker.fake("#{adress.country}"),
        age:MM.randRange(10,100),
        gender:Math.random()>0.5
      };
      tab.push(userObject);
      console.log(tab);

    }
  }
 


function sleep(ms){
  console.log("sleep",ms);
  let callback, prom=new Promise((resolve,reject)=>callback=resolve);
  setTimeout(callback, ms);
  return prom;
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