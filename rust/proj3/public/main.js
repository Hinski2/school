import init, { Image, Linspace } from '/pkg/proj3.js';

async function run(x, y, img) {
    const canvas = document.getElementById('canvas');
    const ctx = canvas.getContext('2d');
    const width = 1024;
    const height = 1024;
    const no_itr = 100;

    img.update(x, y, no_itr);

    const rendered_img = new ImageData(
        new Uint8ClampedArray(img.pixels()), 
        width, 
        height
    );

    ctx.putImageData(rendered_img, 0, 0);
}

(async () => {
    await init();

    const width = 1024;
    const height = 1024;

    const target_x = -0.74364388703;
    const target_y =  0.13182590421;
    let r = 2.0
    
    let img = new Image();
    const loop = () => {
        let x = new Linspace(target_x - r, target_x + r, width);
        let y = new Linspace(target_y - r, target_y + r, height);
        r *= 0.95;

        run(x, y, img);
        requestAnimationFrame(loop);
    }

    requestAnimationFrame(loop);
})()
