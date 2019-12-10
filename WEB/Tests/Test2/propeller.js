!function (a) {
    var b = "propeller",
        c = {
            angle: 0,
            speed: 0,
            inertia: 0,
            minimalSpeed: .001,
            minimalAngleChange: .1,
            step: 0,
            stepTransitionTime: 0,
            stepTransitionEasing: "linear",
            rotateParentInstantly: !1,
            touchElement: null
        },
        d = function (a, b) {
            return "string" == typeof a && (a = document.querySelectorAll(a)), a.length > 1 ? d.createMany(a, b) : (1 === a.length && (a = a[0]), this.element = a, this.active = !1, this.transiting = !1, this.update = this.update.bind(this), this.initCSSPrefix(), this.initAngleGetterSetter(), this.initOptions(b), this.initHardwareAcceleration(), this.initTransition(), this.bindHandlers(), this.addListeners(), void this.update())
        };
    d.createMany = function (a, b) {
        for (var c = [], e = 0; e < a.length; e++) c.push(new d(a[e], b));
        return c
    };
    var e = d.prototype;
    e.initAngleGetterSetter = function () {
        Object.defineProperty(this, "angle", {
            get: function () {
                return this._angle
            },
            set: function (a) {
                this._angle = a, this.virtualAngle = a, this.updateCSS()
            }
        })
    }, e.bindHandlers = function () {
        this.onRotationStart = this.onRotationStart.bind(this), this.onRotationStop = this.onRotationStop.bind(this), this.onRotated = this.onRotated.bind(this)
    }, e.addListeners = function () {
        this.listenersInstalled = !0, "ontouchstart" in document.documentElement ? (this.touchElement.addEventListener("touchstart", this.onRotationStart), this.touchElement.addEventListener("touchmove", this.onRotated), this.touchElement.addEventListener("touchend", this.onRotationStop), this.touchElement.addEventListener("touchcancel", this.onRotationStop), this.touchElement.addEventListener("dragstart", this.returnFalse)) : (this.touchElement.addEventListener("mousedown", this.onRotationStart), this.touchElement.addEventListener("mousemove", this.onRotated), this.touchElement.addEventListener("mouseup", this.onRotationStop), this.touchElement.addEventListener("mouseleave", this.onRotationStop), this.touchElement.addEventListener("dragstart", this.returnFalse)), this.touchElement.ondragstart = this.returnFalse
    }, e.removeListeners = function () {
        this.listenersInstalled = !1, "ontouchstart" in document.documentElement ? (this.touchElement.removeEventListener("touchstart", this.onRotationStart), this.touchElement.removeEventListener("touchmove", this.onRotated), this.touchElement.removeEventListener("touchend", this.onRotationStop), this.touchElement.removeEventListener("touchcancel", this.onRotationStop), this.touchElement.removeEventListener("dragstart", this.returnFalse)) : (this.touchElement.removeEventListener("mousedown", this.onRotationStart), this.touchElement.removeEventListener("mousemove", this.onRotated), this.touchElement.removeEventListener("mouseup", this.onRotationStop), this.touchElement.removeEventListener("mouseleave", this.onRotationStop), this.touchElement.removeEventListener("dragstart", this.returnFalse))
    }, e.bind = function () {
        this.listenersInstalled !== !0 && this.addListeners()
    }, e.unbind = function () {
        this.listenersInstalled === !0 && (this.removeListeners(), this.onRotationStop())
    }, e.stop = function () {
        this.speed = 0, this.onRotationStop()
    }, e.onRotationStart = function (a) {
        this.initCoordinates(), this.initDrag(), this.active = !0, void 0 !== this.onDragStart && this.onDragStart(), this.rotateParentInstantly === !1 && a.stopPropagation()
    }, e.onRotationStop = function () {
        void 0 !== this.onDragStop && this.active === !0 && this.onDragStop(), this.active = !1
    }, e.onRotated = function (a) {
        this.active === !0 && (a.stopPropagation(), a.preventDefault(), void 0 !== a.targetTouches && void 0 !== a.targetTouches[0] ? this.lastMouseEvent = {
            pageX: a.targetTouches[0].pageX,
            pageY: a.targetTouches[0].pageY
        } : this.lastMouseEvent = {
            pageX: a.pageX || a.clientX,
            pageY: a.pageY || a.clientY
        })
    }, e.update = function () {
        void 0 !== this.lastMouseEvent && this.active === !0 && this.updateAngleToMouse(this.lastMouseEvent), this.updateAngle(), this.applySpeed(), this.applyInertia(), Math.abs(this.lastAppliedAngle - this._angle) >= this.minimalAngleChange && this.transiting === !1 && (this.updateCSS(), this.blockTransition(), void 0 !== this.onRotate && "function" == typeof this.onRotate && this.onRotate.bind(this)(), this.lastAppliedAngle = this._angle), window.requestAnimFrame(this.update)
    }, e.updateAngle = function () {
        this.step > 0 ? this._angle = this.getAngleFromVirtual() : this._angle = this.normalizeAngle(this.virtualAngle)
    }, e.getAngleFromVirtual = function () {
        return Math.ceil(this.virtualAngle / this.step) * this.step
    }, e.normalizeAngle = function (a) {
        var b = a;
        return b %= 360, 0 > b && (b = 360 + b), b
    }, e.differenceBetweenAngles = function (a, b) {
        var c = a * (Math.PI / 180),
            d = b * (Math.PI / 180),
            e = Math.atan2(Math.sin(c - d), Math.cos(c - d)),
            f = e * (180 / Math.PI);
        return Math.round(100 * f) / 100
    }, e.applySpeed = function () {
        this.inertia > 0 && 0 !== this.speed && this.active === !1 && (this.virtualAngle += this.speed)
    }, e.applyInertia = function () {
        this.inertia > 0 && (Math.abs(this.speed) >= this.minimalSpeed ? (this.speed = this.speed * this.inertia, this.active === !1 && Math.abs(this.speed) < this.minimalSpeed && void 0 !== this.onStop && this.onStop()) : 0 !== this.speed && (this.speed = 0))
    }, e.updateAngleToMouse = function (a) {
        var b = a.pageX - this.cx,
            d = a.pageY - this.cy,
            e = Math.atan2(b, d),
            f = e * (180 / Math.PI * -1) + 180;
        if (void 0 === this.lastMouseAngle && (this.lastElementAngle = this.virtualAngle, this.lastMouseAngle = f), this.stepTransitionTime !== c.stepTransitionTime) this.speed = this.mouseDiff = this.differenceBetweenAngles(f, this.lastMouseAngle), this.virtualAngle = this.lastElementAngle + this.mouseDiff, this.lastElementAngle = this.virtualAngle, this.lastMouseAngle = f;
        else {
            var g = this.virtualAngle;
            this.mouseDiff = f - this.lastMouseAngle, this.virtualAngle = this.lastElementAngle + this.mouseDiff;
            var h = this.virtualAngle;
            this.speed = this.differenceBetweenAngles(h, g)
        }
    }, e.initCoordinates = function () {
        var a = this.getViewOffset();
        this.cx = a.x + this.element.offsetWidth / 2, this.cy = a.y + this.element.offsetHeight / 2
    }, e.initDrag = function () {
        this.speed = 0, this.lastMouseAngle = void 0, this.lastElementAngle = void 0, this.lastMouseEvent = void 0
    }, e.initOptions = function (a) {
        a = a || c, this.touchElement = document.querySelectorAll(a.touchElement)[0] || this.element, this.onRotate = a.onRotate || a.onrotate, this.onStop = a.onStop || a.onstop, this.onDragStop = a.onDragStop || a.ondragstop, this.onDragStart = a.onDragStart || a.ondragstart, this.step = a.step || c.step, this.stepTransitionTime = a.stepTransitionTime || c.stepTransitionTime, this.stepTransitionEasing = a.stepTransitionEasing || c.stepTransitionEasing, this.angle = a.angle || c.angle, this.speed = a.speed || c.speed, this.inertia = a.inertia || c.inertia, this.minimalSpeed = a.minimalSpeed || c.minimalSpeed, this.lastAppliedAngle = this.virtualAngle = this._angle = a.angle || c.angle, this.minimalAngleChange = this.step !== c.step ? this.step : c.minimalAngleChange, this.rotateParentInstantly = a.rotateParentInstantly || c.rotateParentInstantly
    }, e.initCSSPrefix = function () {
        void 0 === d.cssPrefix && ("undefined" != typeof document.body.style.transform ? d.cssPrefix = "" : "undefined" != typeof document.body.style.mozTransform ? d.cssPrefix = "-moz-" : "undefined" != typeof document.body.style.webkitTransform ? d.cssPrefix = "-webkit-" : "undefined" != typeof document.body.style.msTransform && (d.cssPrefix = "-ms-"))
    }, e.initHardwareAcceleration = function () {
        this.accelerationPostfix = "";
        var a, b = document.createElement("p"),
            c = {
                webkitTransform: "-webkit-transform",
                OTransform: "-o-transform",
                msTransform: "-ms-transform",
                MozTransform: "-moz-transform",
                transform: "transform"
            };
        document.body.insertBefore(b, null);
        for (var e in c) void 0 !== b.style[e] && (b.style[e] = "translate3d(1px,1px,1px)", a = window.getComputedStyle(b).getPropertyValue(c[e]));
        document.body.removeChild(b);
        var f = void 0 !== a && a.length > 0 && "none" !== a;
        f === !0 && (this.accelerationPostfix = "translateZ(0)", this.element.style[d.cssPrefix + "transform"] = this.accelerationPostfix, this.updateCSS())
    }, e.initTransition = function () {
        if (this.stepTransitionTime !== c.stepTransitionTime) {
            var a = "all " + this.stepTransitionTime + "ms " + this.stepTransitionEasing;
            this.element.style[d.cssPrefix + "transition"] = a
        }
    }, e.updateCSS = function () {
        this.element.style[d.cssPrefix + "transform"] = "rotate(" + this._angle + "deg) " + this.accelerationPostfix
    }, e.blockTransition = function () {
        if (this.stepTransitionTime !== c.stepTransitionTime) {
            var a = this;
            setTimeout(function () {
                a.transiting = !1
            }, this.stepTransitionTime), this.transiting = !0
        }
    }, e.getViewOffset = function (a) {
        var b = {
            x: 0,
            y: 0
        };
        return this.element && this.addOffset(this.element, b, "defaultView" in document ? document.defaultView : document.parentWindow), b
    }, e.addOffset = function (a, b, c) {
        var d = a.offsetParent;
        if (b.x += a.offsetLeft - (d ? d.scrollLeft : 0), b.y += a.offsetTop - (d ? d.scrollTop : 0), d) {
            if (1 == d.nodeType) {
                var e = c.getComputedStyle(d, "");
                if ("static" != e.position) {
                    if (b.x += parseInt(e.borderLeftWidth), b.y += parseInt(e.borderTopWidth), "table" == d.localName.toLowerCase()) b.x += parseInt(e.paddingLeft), b.y += parseInt(e.paddingTop);
                    else if ("body" == d.localName.toLowerCase()) {
                        var f = c.getComputedStyle(a, "");
                        b.x += parseInt(f.marginLeft), b.y += parseInt(f.marginTop)
                    }
                } else "body" == d.localName.toLowerCase() && (b.x += parseInt(e.borderLeftWidth), b.y += parseInt(e.borderTopWidth));
                for (var g = a.parentNode; d != g;) b.x -= g.scrollLeft, b.y -= g.scrollTop, g = g.parentNode;
                this.addOffset(d, b, c)
            }
        } else {
            if ("body" == a.localName.toLowerCase()) {
                var f = c.getComputedStyle(a, "");
                b.x += parseInt(f.borderLeftWidth), b.y += parseInt(f.borderTopWidth);
                var h = c.getComputedStyle(a.parentNode, "");
                b.x += parseInt(h.paddingLeft), b.y += parseInt(h.paddingTop), b.x += parseInt(h.marginLeft), b.y += parseInt(h.marginTop)
            }
            a.scrollLeft && (b.x += a.scrollLeft), a.scrollTop && (b.y += a.scrollTop);
            var i = a.ownerDocument.defaultView;
            i && i.frameElement && this.addOffset(i.frameElement, b, i)
        }
    }, e.returnFalse = function () {
        return !1
    }, void 0 !== a.$ && ($.propeller = {}, $.propeller.propellers = [], $.fn[b] = function (a) {
        return this.each(function () {
            if (!$.data(this, "plugin_" + b)) {
                var c = new d(this, a);
                $.data(this, "plugin_" + b, c), $.propeller.propellers.push(c)
            }
        })
    }), d.deg2radians = 2 * Math.PI / 360, a.Propeller = d
}(window), window.requestAnimFrame = function () {
    return window.requestAnimationFrame || window.webkitRequestAnimationFrame || window.mozRequestAnimationFrame || function (a) {
        window.setTimeout(a, 1e3 / 60)
    }
}();