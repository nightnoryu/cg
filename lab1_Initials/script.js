const ACCELERATION = 1;

class MovingLetterData {
    #time = 0;
    #shift = 0;
    #startingSpeed;

    constructor(startingSpeed) {
        this.#startingSpeed = startingSpeed;
        this._startingSpeed = startingSpeed;
    }

    get time() {
        return this.#time;
    }

    set time(value) {
        this.#time = value;
    }

    get shift() {
        return this.#shift;
    }

    set shift(value) {
        this.#shift = value;
    }

    get startingSpeed() {
        return this._startingSpeed;
    }
}

window.onload = () => {
    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');

    const letters = [
        new MovingLetterData(18),
        new MovingLetterData(23),
        new MovingLetterData(20),
    ];

    const loop = () => {
        for (let letter of letters) {
            update(letter);
        }

        draw(ctx, letters);

        for (let letter of letters) {
            ++letter.time;
        }
    };

    setInterval(loop, 20);
}

function draw(ctx, letters) {
    ctx.clearRect(0, 0, 800, 600);
    drawFirstLetter(ctx, letters[0].shift);
    drawSecondLetter(ctx, letters[1].shift);
    drawThirdLetter(ctx, letters[2].shift);
}

function update(letter) {
    letter.shift = letter.time * (letter.startingSpeed - ACCELERATION * letter.time / 2);

    if (letter.shift < 0) {
        letter.time = 0;
        letter.shift = 0;
    }
}

function drawFirstLetter(ctx, shift) {
    ctx.fillStyle = 'green';

    ctx.beginPath();
    ctx.moveTo(10, 300 - shift);
    ctx.lineTo(20, 300 - shift);
    ctx.lineTo(90, 500 - shift);
    ctx.lineTo(80, 500 - shift);
    ctx.lineTo(10, 300 - shift);
    ctx.closePath();
    ctx.fill();

    ctx.beginPath();
    ctx.moveTo(80, 300 - shift);
    ctx.lineTo(90, 300 - shift);
    ctx.lineTo(20, 500 - shift);
    ctx.lineTo(10, 500 - shift);
    ctx.lineTo(80, 300 - shift);
    ctx.closePath();
    ctx.fill();
}

function drawSecondLetter(ctx, shift) {
    ctx.fillStyle = 'red';
    ctx.strokeStyle = 'red';
    ctx.lineWidth = 10;

    ctx.fillRect(130, 300 - shift, 10, 200);
    ctx.fillRect(130, 300 - shift, 110, 10);

    ctx.beginPath();
    ctx.arc(185, 445 - shift, 50, 0, 2 * Math.PI);
    ctx.closePath();
    ctx.stroke();
}

function drawThirdLetter(ctx, shift) {
    ctx.fillStyle = 'black';
    ctx.strokeStyle = 'black';
    ctx.lineWidth = 10;

    ctx.fillRect(280, 300 - shift, 10, 200);

    ctx.beginPath();
    ctx.arc(335, 350 - shift, 50, 0, 2 * Math.PI);
    ctx.closePath();
    ctx.stroke();
}
