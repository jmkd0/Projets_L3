let index;
let urlParams= new URLSearchParams(window.location.search);
if(urlParams.has('index')){
    index=urlParams.get('index');
}else index=1;
let  profilMatchs= new ProfilMatchView(index, new Model())
let controlCadre=new CadreController(new UsersCadreView(), new Model )

