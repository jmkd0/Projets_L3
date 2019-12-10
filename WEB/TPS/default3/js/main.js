
window.addEventListener("load", event =>main());
const main= async ()=>{
  console.log("MAIN");
  //Demande du server
  let result, response;
   result=await fetch("https://ilusio.dev/base/gettest");
  console.log("Envoie de donnee");
  let data={number: 78};
  let send=Object.keys(data).map(key=> encodeURIComponent(key)+"="+encodeURIComponent(data[key])).join("&");
  result=await fetch("https://ilusio.dev/base/posttest", {
    method: "POST",
    headers:{
      "Content-Type": "application/x-www-from-urlencoded; charset=UTF-8"
    },
    body:send
  });
//
 
  response=await result.json();
  console.log(response);
}
