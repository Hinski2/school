import express from 'express'
import path from 'path'
import { fileURLToPath } from 'url';

const app = express();
const PORT = 4242;

const __filename = fileURLToPath(import.meta.url);
const __dirname = path.dirname(__filename);
app.use(express.static(path.join(__dirname, 'public')));

app.use('/pkg', express.static(path.join(__dirname, 'pkg'), {
    setHeaders: (res, filePath) => {
        if (filePath.endsWith('.wasm')) {
            res.set('Content-Type', 'application/wasm');
        }
    }
}));

app.listen(PORT, () => {
    console.log(`Server running at http://localhost:${PORT}/`);
});