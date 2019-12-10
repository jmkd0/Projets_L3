/**
* @nocollapse
* @export
*/
class MM {
	
	/**
	 * @export
	 * @method forceRange: 
	 * @param {number} val: 
	 * @param {number} min: 
	 * @param {number} max: 
	 * @return {number}
	 */
	static forceRange(val, min, max) {
		return Math.max(Math.min(max, val), min);
	}
	
	/**
	 * @export
	 * @method randRange: 
	 * @param {number} min: 
	 * @param {number} max: 
	 * @return {number}
	 */
	static randRange(min, max) {
		return Math.floor(Math.random() * (max - min + 1)) + min;
	}
	
	/**
	 * @export
	 * @method roundNearest: 
	 * @param {number} value: 
	 * @param {number} multiple: 
	 * @return {number}
	 */
	static roundNearest(value, multiple) {
		return multiple * Math.round(value / multiple);
	}
	
	/**
	 * @export
	 * @method scale: 
	 * @param {number} curW: 
	 * @param {number} curH: 
	 * @param {number} maxW:
	 * @param {number} maxH: 
	 * @return {Array}
	 */
	static scale(curW, curH, maxW, maxH) {
		let r = Math.min(maxW / curW, maxH / curH);
		return [curW * r, curH * r, r];
	}
	
	/**
	 * @export
	 * @method scaleFill: 
	 * @param {number} curW: 
	 * @param {number} curH: 
	 * @param {number} maxW: 
	 * @param {number} maxH: 
	 * @return {Array}
	 */
	static scalefill(curW, curH, maxW, maxH) {
		let r = Math.max(maxW / curW, maxH / curH);
		return [curW * r, curH * r, r];
	}
	
	/**
	 * @export
	 * @method distance: 
	 * @param {number} x1: 
	 * @param {number} y1: 
	 * @param {number} x2: 
	 * @param {number} y2: 
	 * @return {number}
	 */
	static distance(x1, y1, x2, y2) {
		return Math.sqrt(Math.pow(x2 - x1, 2) + Math.pow(y2 - y1, 2));
	}
	
	/**
	 * @export
	 * @method angle: 
	 * @param {number} x1: 
	 * @param {number} y1: 
	 * @param {number} x2: 
	 * @param {number} y2: 
	 * @return {number}
	 */
	static angle(x1, y1, x2, y2) {
		return Math.round(Math.atan2(y1 - y2, x1 - x2) * 10000) / 10000;
	}
	
	/**
	 * @export
	 * @method pointBetween: 
	 * @param {number} x1: 
	 * @param {number} y1: 
	 * @param {number} x2: 
	 * @param {number} y2: 
	 * @param {number} distance: 
	 * @return {Object}
	 */
	static pointBetween(x1, y1, x2, y2, distance) {
		let angle = MM.angle(x2, y2, x1, y1);
		return {x: x1 + distance * Math.cos(angle), y: y1 + distance * Math.sin(angle)};
	}
	
	/**
	 * @export
	 * @method pointAround
	 * @param {number} centerx: 
	 * @param {number} centery: 
	 * @param {number} x: 
	 * @param {number} y: 
	 * @param {number} angle: 
	 * @return {Object}
	 */
	static pointAround(centerx, centery, x, y, angle) {
		let x1 = x - centerx;
		let y1 = y - centery;
		let x2 = x1 * Math.cos(angle) - y1 * Math.sin(angle);
		let y2 = x1 * Math.sin(angle) + y1 * Math.cos(angle);
		return {x: x2 + centerx, y: y2 + centery};
	}
	
	/**
	 * @export
	 * @method remap: 
	 * @param {number} value: 
	 * @param {number} min: 
	 * @param {number} max: 
	 * @param {number} remin: 
	 * @param {number} remax: 
	 * @return {number}
	 */
	static remap(value, min, max, remin, remax) {
		return (value - min) / (max - min) * (remax - remin) + remin; // clean ?
	}
	
	/**
	 * @export
	 * @method hit: hit test box
	 * @param {number} x1: 
	 * @param {number} y1: 
	 * @param {number} w1: 
	 * @param {number} h1: 
	 * @param {number} x2: 
	 * @param {number} y2: 
	 * @param {number} w2: 
	 * @param {number} h2: 
	 * @return {boolean}
	 */
	static hit(x1, y1, w1, h1, x2, y2, w2, h2) {
		return ((x1 + w1 >= x2) && (x1 <= x2 + w2)) && ((y1 + h1 >= y2) && (y1 <= y2 + h2));
	}
	
	/**
	 * @export
	 * @method round: 
	 * @param {number} value:
	 * @param {number} decimals: 
	 * @return {number}
	 */
	static round(value, decimals) {
		let pows = Math.pow(10, decimals);
		return Math.round(value * pows) / pows;
	}
	
	/**
	 * @export
	 * @method around: 
	 * @param {number} value: 
	 * @param {number} min: 
	 * @param {number} max: 
	 * @return {number}
	 */
	static around(value, min, max) {
		return value < min ? max : value > max ? min : value;
	}

	/**
	 * @export
	 * @method nthRoot: 
	 * @param {number} value: 
	 * @param {number} root: 
	 * @return {number}
	 */
	static nthRoot(value, root) {
		return Math.pow(value, 1 / root);
	}
}