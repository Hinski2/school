import init, { Renderer, Linspace } from '/pkg/proj3.js';

async function run(x, y, wasm) {
    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');
    const width = 1024;
    const height = 1024;
    const no_itr = 175;

    Renderer.update(x, y, no_itr);
    const ptr = Renderer.get_buffer_ptr();

    const mem = new Uint8ClampedArray(
        wasm.memory.buffer, 
        ptr, 
        width * height * 4
    );

    const img = new ImageData(mem, width, height);
    ctx.putImageData(img, 0, 0);
}

(async () => {
    const fpsElement = document.getElementById('fps-counter')

    const wasm = await init();
    Renderer.init();

    const width = 1024;
    const height = 1024;

    const target_x = -0.74364388703;
    const target_y =  0.13182590421;
    let r = 2.0

    let lastTime = performance.now();
    let frames = 0;   

    const loop = () => {
        const now = performance.now();
        frames++;

        if (now - lastTime >= 1000) {
            fpsElement.innerText = `FPS: ${frames}`;
            frames = 0;
            lastTime = now;  
        }

        let x = new Linspace(target_x - r, target_x + r, width);
        let y = new Linspace(target_y - r, target_y + r, height);
        r *= 0.95;

        run(x, y, wasm);
        requestAnimationFrame(loop);
    }

    requestAnimationFrame(loop);
})()
