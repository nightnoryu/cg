const DOOR_HEIGHT = 180;
const DOOR_WINDOW_WIDTH = 15;
const DOOR_WINDOW_HEIGHT = 90;
const WINDOW_HEIGHT = 80;

class RectangleInfo {
    #x;
    #y;
    #width;
    #height;

    constructor(x, y, width, height) {
        this.#x = x;
        this.#y = y;
        this.#width = width;
        this.#height = height;
    }

    get x() {
        return this.#x;
    }

    get y() {
        return this.#y;
    }

    get width() {
        return this.#width;
    }

    get height() {
        return this.#height;
    }
}

window.onload = function () {
    const canvas1 = document.getElementById('canvas1');
    const ctx1 = canvas1.getContext('2d');

    const canvas2 = document.getElementById('canvas2');
    const ctx2 = canvas2.getContext('2d');

    drawTrolley(ctx1);
    useDragAndDrop(canvas1);

    drawTrolley(ctx2);
    useDragAndDrop(canvas2);
};

function drawTrolley(ctx) {
    ctx.clearRect(0, 0, 800, 600);
    drawMain(ctx);
    drawDoors(ctx);
    drawWindows(ctx);
    drawWheels(ctx);
    drawLights(ctx);
    drawCables(ctx);
}

function drawMain(ctx) {
    ctx.strokeStyle = 'black';
    ctx.lineWidth = 1;

    ctx.fillStyle = 'white';
    ctx.beginPath();
    ctx.rect(50, 150, 700, 100);
    ctx.fill();
    ctx.stroke();

    ctx.fillStyle = 'blue';
    ctx.beginPath();
    ctx.rect(50, 250, 700, 100)
    ctx.fill();
    ctx.stroke();
}

function drawDoors(ctx) {
    const doors = [
        new RectangleInfo(80, 170, 90, DOOR_HEIGHT),
        new RectangleInfo(350, 170, 90, DOOR_HEIGHT),
        new RectangleInfo(680, 170, 45, DOOR_HEIGHT),
    ];

    ctx.fillStyle = 'white';

    for (const door of doors) {
        ctx.beginPath();
        ctx.rect(door.x, door.y, door.width, door.height);
        ctx.fill();
        ctx.stroke();
    }

    const doorWindows = [
        new RectangleInfo(86, 175, DOOR_WINDOW_WIDTH, DOOR_WINDOW_HEIGHT),
        new RectangleInfo(106, 175, DOOR_WINDOW_WIDTH, DOOR_WINDOW_HEIGHT),
        new RectangleInfo(129, 175, DOOR_WINDOW_WIDTH, DOOR_WINDOW_HEIGHT),
        new RectangleInfo(148, 175, DOOR_WINDOW_WIDTH, DOOR_WINDOW_HEIGHT),
        new RectangleInfo(356, 175, DOOR_WINDOW_WIDTH, DOOR_WINDOW_HEIGHT),
        new RectangleInfo(376, 175, DOOR_WINDOW_WIDTH, DOOR_WINDOW_HEIGHT),
        new RectangleInfo(399, 175, DOOR_WINDOW_WIDTH, DOOR_WINDOW_HEIGHT),
        new RectangleInfo(419, 175, DOOR_WINDOW_WIDTH, DOOR_WINDOW_HEIGHT),
        new RectangleInfo(685, 175, DOOR_WINDOW_WIDTH, DOOR_WINDOW_HEIGHT),
        new RectangleInfo(705, 175, DOOR_WINDOW_WIDTH, DOOR_WINDOW_HEIGHT),
    ];

    ctx.fillStyle = 'cyan';
    ctx.strokeStyle = 'black';

    for (const doorWindow of doorWindows) {
        ctx.beginPath();
        ctx.rect(doorWindow.x, doorWindow.y, doorWindow.width, doorWindow.height);
        ctx.fill();
        ctx.stroke();
    }

    ctx.strokeStyle = 'black';

    ctx.beginPath();
    ctx.moveTo(125, 170);
    ctx.lineTo(125, 350);
    ctx.stroke();

    ctx.beginPath();
    ctx.moveTo(395, 170);
    ctx.lineTo(395, 350);
    ctx.stroke();
}

function drawWindows(ctx) {
    const windows = [
        new RectangleInfo(50, 160, 15, WINDOW_HEIGHT),
        new RectangleInfo(180, 160, 160, WINDOW_HEIGHT),
        new RectangleInfo(450, 160, 220, WINDOW_HEIGHT),
        new RectangleInfo(740, 160, 10, WINDOW_HEIGHT),
    ];

    ctx.fillStyle = 'cyan';
    ctx.strokeStyle = 'black';

    for (const window of windows) {
        ctx.beginPath();
        ctx.rect(window.x, window.y, window.width, window.height);
        ctx.fill();
        ctx.stroke();
    }
}

function drawWheels(ctx) {
    ctx.fillStyle = 'grey';
    ctx.strokeStyle = 'black';
    ctx.lineWidth = 15;

    ctx.beginPath();
    ctx.arc(220, 350, 35, 0, 2 * Math.PI);
    ctx.fill();
    ctx.stroke();

    ctx.beginPath();
    ctx.arc(620, 350, 35, 0, 2 * Math.PI);
    ctx.fill();
    ctx.stroke();

    ctx.fillStyle = 'black';

    ctx.beginPath();
    ctx.arc(220, 350, 3, 0, 2 * Math.PI);
    ctx.fill();

    ctx.beginPath();
    ctx.arc(620, 350, 3, 0, 2 * Math.PI);
    ctx.fill();
}

function drawLights(ctx) {
    ctx.fillStyle = 'orange';
    ctx.strokeStyle = 'black';
    ctx.lineWidth = 1;

    ctx.beginPath();
    ctx.rect(744, 290, 6, 10);
    ctx.fill();
    ctx.stroke();

    ctx.beginPath();
    ctx.rect(50, 290, 6, 10);
    ctx.fill();
    ctx.stroke();
}

function drawCables(ctx) {
    ctx.fillStyle = 'grey';
    ctx.strokeStyle = 'black';
    ctx.lineWidth = 2;

    ctx.beginPath();
    ctx.rect(380, 130, 100, 20);
    ctx.fill();
    ctx.stroke();

    ctx.beginPath();
    ctx.moveTo(180, 10);
    ctx.lineTo(420, 130);
    ctx.fill();
    ctx.stroke();

    ctx.beginPath();
    ctx.moveTo(220, 10);
    ctx.lineTo(460, 130);
    ctx.fill();
    ctx.stroke();

    ctx.strokeStyle = 'grey';
    ctx.beginPath();
    ctx.moveTo(10, 10);
    ctx.lineTo(800, 10);
    ctx.stroke();
}

function useDragAndDrop(element) {
    element.addEventListener('mousedown', event => {
        const position = element.getBoundingClientRect();
        const shiftX = position.left - event.pageX;
        const shiftY = position.top - event.pageY;

        const mouseMoveHandler = event => {
            element.style.left = event.pageX + shiftX + 'px';
            element.style.top = event.pageY + shiftY + 'px';
        };
        const mouseUpHandler = () => {
            document.removeEventListener('mousemove', mouseMoveHandler);
            document.removeEventListener('mouseup', mouseUpHandler);
        };

        document.addEventListener('mousemove', mouseMoveHandler);
        document.addEventListener('mouseup', mouseUpHandler);
    });
}
