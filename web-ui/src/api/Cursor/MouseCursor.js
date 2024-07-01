export class Cursor {
    lerp = (a, b, n) => (1 - n) * a + n * b;   // 线性插值函数

    constructor(dict) {
        this.pos = { curr: null, prev: null }; // 坐标
        this.create();
        this.init();
        this.render();
        // 这个地方有时间重写一下
        this.pt = { 'a': null, 'button': null };       // hover的tag属性，被什么父节点的类属性包裹
        for (let key in dict) this.pt[key] = dict[key];
    }

    init() { // 给事件处理器属性设置函数
        document.onmouseover = event => {
            for (let _tag in this.pt) {
                let _class = this.pt[_tag]
                if (event.target.tagName.toLowerCase() === _tag && (_class === null || event.target.parentNode.className.toLowerCase().includes(_class))) {
                    // 判断是否被一个父节点包裹
                    this.cursor.classList.add("hover");
                    return
                }
            }
        }
        document.onmouseout = event => {
            for (let _tag in this.pt) {
                let _class = this.pt[_tag]
                if (event.target.tagName.toLowerCase() === _tag && (_class === null || event.target.parentNode.className.toLowerCase().includes(_class))) {
                    this.cursor.classList.remove("hover");
                    return
                }
            }
        }

        document.onmousedown = event => this.cursor.classList.add("active");     // 点击的时候添加active 
        document.onmouseup = event => this.cursor.classList.remove("active");    // 移除active

        document.onmouseenter = event => this.cursor.classList.remove("hidden"); // 鼠标进页面
        document.onmouseleave = event => this.cursor.classList.add("hidden");    // 鼠标出页面隐藏圈

        document.onmousemove = event => {
            this.cursor.classList.remove("hidden");  // 防穿帮
            if (this.pos.curr === null) // 如果没坐标，定位到鼠标现在的坐标，减8是因为设置的坐标是图片左上角坐标，图片本省是16*16
                this.move(event.clientX - 8, event.clientY - 8); // e.clientX 和 e.clientY 是事件对象的属性，分别表示鼠标指针在触发事件时相对于浏览器窗口的水平和垂直坐标。
            this.pos.curr = { // 设置现在的前驱坐标
                x: event.clientX - 8,
                y: event.clientY - 8
            };
        }
    }

    create() {
        if (!this.cursor) {
            this.cursor = document.createElement("div");  // 创建div节点
            this.cursor.id = "cursor";                    // 指定指针id
            this.cursor.classList.add("hidden");          // 不加这个语句可能会穿帮
            document.body.append(this.cursor);            // 添加cursor到dom里
        }
    }

    move(left, top) {  // 设置左上角的坐标
        this.cursor.style["left"] = `${left}px`;
        this.cursor.style["top"] = `${top}px`;
    }

    render() {  // 核心动画函数
        if (this.pos.prev) {
            this.pos.prev.x = this.lerp(this.pos.prev.x, this.pos.curr.x, 0.15);
            this.pos.prev.y = this.lerp(this.pos.prev.y, this.pos.curr.y, 0.15);

            // 后继坐标根据线性插值函数更新，从而达到动画效果
            this.move(this.pos.prev.x, this.pos.prev.y);
        } else {
            this.pos.prev = this.pos.curr;
        }
        requestAnimationFrame(() => this.render());  // 每次重绘动画的时候都回调render函数
    }
}