window.addEventListener("load", main);

let metro;

function main() {

	console.log("metro");

	let metroWrap = HH.create("div");
	document.body.appendChild(metroWrap);
	metro = new Metro(metroWrap, {"stations": [
		{name: "room 1"},
		{name: "room 2"},
		{name: "room 3"},
		{name: "room 4"},
		{name: "room 5"},
		{name: "room 6"},
		{name: "room 7"},
		{name: "room 8"},
		{name: "room 9"},
		{name: "room 10"},
		{name: "room 11"}
	], "renderer": SuezStation, "select": onSelect});
}

function onSelect(index) {
	trace("select", index);
}

class SuezStation {

	constructor(index, size) {

		this._index = index;
		this._size = size;

		this.wrapper = HH.create("div");
		SS.style(this.wrapper, {"position": "absolute", "left": "0px", "top": "0px", "width": this._size + "px", "height": this._size + "px"});

		this.pic = HH.create("img");
		HH.attr(this.pic, {"src": "assets/menu/p" + (this._index + 1) + ".png"});
		SS.style(this.pic, {"width": "100%", "height": "100%"});
		this.wrapper.appendChild(this.pic);

		this.text = HH.create("div");
		SS.style(this.text, {"position": "absolute", "height": "15px", "lineHeight": "15px", "marginLeft": "5px", "padding": "5px", "left": this._size + "px", "top": "50%", "transform": "translateY(-50%)", "whiteSpace": "nowrap", "color": "#FFFFFF", "backgroundColor": "rgba(0, 0, 0, 0.3)", "borderRadius": "15px"});
		this.text.innerHTML = "room n°" + (this._index + 1);
		this.wrapper.appendChild(this.text);

	}

}