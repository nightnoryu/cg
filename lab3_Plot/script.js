import * as THREE from 'https://unpkg.com/three/build/three.module.js';

const START = -6 * Math.PI;
const END = 6 * Math.PI;
const STEP = 0.05;
const DRAWING_STEP = 2;
const FUNC = x => Math.sin(3 * x) + Math.cos(2 * x + Math.PI / 12);

const LINE_COLOR = 0x000000;
const X_AXIS_COLOR = 0xff0000;
const Y_AXIS_COLOR = 0x00ff00;
const MARKER_LENGTH = 0.5;

window.onload = () => {
    const scene = new THREE.Scene();
    const camera = initializeCamera();
    const renderer = initializeRenderer();

    const plot = new Plot();
    const xAxis = initializeXAxis();
    const yAxis = initializeYAxis();

    scene.add(xAxis, yAxis);
    plot.addToScene(scene);

    function render() {
        requestAnimationFrame(render);
        plot.update();
        renderer.render(scene, camera);
    }

    render();
};


// TODO: draw without three.js
class Plot {
    #plot;
    #drawRange = DRAWING_STEP;

    constructor() {
        const material = new THREE.LineBasicMaterial({ color: LINE_COLOR });
        const geometry = new THREE.BufferGeometry();
        this.#plot = new THREE.Line(geometry, material);

        this.#calculatePoints();
    }

    addToScene(scene) {
        scene.add(this.#plot);
    }

    update() {
        this.#drawRange += DRAWING_STEP;
        this.#plot.geometry.setDrawRange(0, this.#drawRange);
    }

    #calculatePoints() {
        const plotPoints = [];

        for (let x = START; x < END; x += STEP) {
            plotPoints.push(x, FUNC(x));
        }

        this.#plot.geometry.setAttribute('position', new THREE.Float32BufferAttribute(plotPoints, 2));
        this.#plot.geometry.setDrawRange(0, DRAWING_STEP);
    }
}


function initializeRenderer() {
    const renderer = new THREE.WebGLRenderer({ alpha: true, antialias: true });
    renderer.setClearColor(0xffffff, 0);
    renderer.setSize(window.innerWidth, window.innerHeight);
    document.body.appendChild(renderer.domElement);

    window.addEventListener('resize', () => {
        renderer.setSize(window.innerWidth, window.innerHeight);
    });

    return renderer;
}

function initializeCamera() {
    const camera = new THREE.PerspectiveCamera(45, window.innerWidth / window.innerHeight, 0.1, 1000);
    camera.position.z = 30;

    window.addEventListener('resize', () => {
        camera.aspect = window.innerWidth / window.innerHeight;
        camera.updateProjectionMatrix();
    });

    return camera;
}

function initializeXAxis() {
    const material = new THREE.LineBasicMaterial({ color: X_AXIS_COLOR });
    const points = [new THREE.Vector2(-20, 0), new THREE.Vector2(20, 0)];
    const geometry = new THREE.BufferGeometry().setFromPoints(points);

    const arrow = new THREE.ArrowHelper(
        new THREE.Vector3(1, 0, 0),
        new THREE.Vector3(15, 0, 0),
        5,
        X_AXIS_COLOR);
    const axis = new THREE.Line(geometry, material);

    const group = new THREE.Group();
    group.add(axis, arrow);

    for (let x = -18; x <= 18; x += 4) {
        if (x === 0) {
            continue;
        }

        const points = [new THREE.Vector2(x, -MARKER_LENGTH), new THREE.Vector2(x, MARKER_LENGTH)];
        const geometry = new THREE.BufferGeometry().setFromPoints(points);

        const marker = new THREE.Line(geometry, material);
        group.add(marker);
    }

    return group;
}

function initializeYAxis() {
    const material = new THREE.LineBasicMaterial({ color: Y_AXIS_COLOR });
    const points = [new THREE.Vector2(0, -10), new THREE.Vector2(0, 10)];
    const geometry = new THREE.BufferGeometry().setFromPoints(points);

    const arrow = new THREE.ArrowHelper(
        new THREE.Vector3(0, 1, 0),
        new THREE.Vector3(0, 5, 0),
        5,
        Y_AXIS_COLOR);
    const axis = new THREE.Line(geometry, material);

    const group = new THREE.Group();
    group.add(axis, arrow);

    for (let y = -8; y <= 8; y += 2) {
        if (y === 0) {
            continue;
        }

        const points = [new THREE.Vector2(-MARKER_LENGTH, y), new THREE.Vector2(MARKER_LENGTH, y)];
        const geometry = new THREE.BufferGeometry().setFromPoints(points);

        const marker = new THREE.Line(geometry, material);
        group.add(marker);
    }

    return group;
}
