#define parbegin(a, b) { a(); b(); }
const int n = 50;
static int tally = 0;

void total() {
    for (int count = 1; count <= n; count++)
        tally = tally + 1;
}

void main() {
    parbegin (total, total);
}