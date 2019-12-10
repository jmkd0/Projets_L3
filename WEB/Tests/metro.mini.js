(function(){'use strict';
var f,g=this||self;
function k(a,d){a=a.split(".");
var b=g;
a[0]in b||"undefined"==typeof b.execScript||b.execScript("var "+a[0]);
for(var c;a.length&&(c=a.shift());
)a.length||void 0===d?b[c]&&b[c]!==Object.prototype[c]?b=b[c]:b=b[c]={}:b[c]=d};
function l(a,d){
    this.j=d;
    this.wrapper=a;
    SS.style(this.wrapper,{position:"absolute",left:"0px",top:"0px",width:"100%",height:"100%",backgroundColor:"rgba(0, 0, 0, 0)"});
    this.a=this.wrapper.getBoundingClientRect();
    this.u=-1;
    this.o=[];
    this.i=[];
    this.create();
    this.c=100*(this.o.length-1);
    this.g=this.a.height/2-this.c;
    this.f=this.a.height/2;
    this.h=!1;this.A=0;
    this.w=this.a.height/2;
    this.b=this.a.height/2;
    this.l=this.v=0;m(this);
    EE.on(this.wrapper,"mousedown touchstart",this.B.bind(this));
    EE.on(this.wrapper,"mousemove touchmove",this.C.bind(this));
    EE.on(this.wrapper,"mouseup mouseleave touchend",this.F.bind(this));
    this.m=-1;
    EE.on(window,"resize",this.D.bind(this))}f=l.prototype;
    f.create=function(){
        var a=this;this.j.stations.forEach(function(d,b){
            d=new a.j.renderer(b,100,d);a.wrapper.appendChild(d.wrapper);
            a.o.push(d)})};f.B=function(a){
                this.h=!0;
                a.preventDefault();
                if(!(a.touches&&1<a.touches.length)){
                    for(a=EE.coord(EE.normalize(a));
                    this.i.length;)this.i.shift().stop();
                    this.A=a.y;this.s()
                }
            };
    f.C=function(a){
        this.h&&(a.preventDefault(),a=EE.coord(EE.normalize(a)),this.v=this.b,this.b=MM.forceRange(this.w-2*(this.A-a.y),this.g,this.f))
    };
        f.F=function(a){
            this.h&&(a.preventDefault(),this.h=!1,this.stop(),a=Math.round((this.c-MM.remap(this.b,this.g,this.f,0,this.c))/100),this.b=MM.remap(100*a,0,this.c,this.f,this.g),this.l!=a&&this.j.select(a),this.l=a,m(this,!0),this.w=this.b)
        };
    f.D=function(){
        var a=this;
        -1!=this.m&&clearTimeout(this.m);
        this.m=setTimeout(function(){
            a.a=a.wrapper.getBoundingClientRect();
            a.g=a.a.height/2-a.c;
            a.f=a.a.height/2;
            a.b=MM.remap(100*a.l,0,a.c,a.f,a.g);
            m(a,!0)
        },250)};
        f.s=function(){
            this.u=window.requestAnimationFrame(this.s.bind(this));
            m(this)
        };
        f.stop=function(){
            window.cancelAnimationFrame(this.u)};
    function m(a,d){
        a.v!==a.b&&(d=d||!1,a.o.forEach(function(b,c){
            var e=a.b+100*c;c=(e<a.a.height/2?e:a.a.height-e)/(a.a.height/2);
            var h=Math.max(100*c,25);
            e={top:e-50*c+"px",left:15+e/2-1/a.a.height/2*Math.pow(e,2)-50*c+"px",width:h+"px",height:h+"px",opacity:c};
            c={left:h+"px",opacity:c};
            d?a.i.push(new Effect(b.wrapper,30,e,"quartOut"),new Effect(b.text,30,c,"quartOut")):(SS.style(b.wrapper,e),SS.style(b.text,c))}),d&&a.i.forEach(
                function(b){
                    return b.play()
                }))
            }
                k("Metro",l);
    k("MetroStation",function(a,d,b){
        this.a=d;
        this.b=b;
        this.wrapper=HH.create("div");
        SS.style(this.wrapper,{position:"absolute",left:"0px",top:"0px",width:this.a+"px",height:this.a+"px",backgroundColor:"rgba(0, 55, 100, 1)"});this.text=HH.create("div");
        SS.style(this.text,{position:"absolute",height:"15px",padding:"5px",left:this.a+"px",top:"50%",transform:"translateY(-50%)",whiteSpace:"nowrap",color:"#FFFFFF",backgroundColor:"rgba(0, 0, 0, 0.3)"});
        this.text.innerHTML=this.b.name;this.wrapper.appendChild(this.text)});
    }).call(this);
    