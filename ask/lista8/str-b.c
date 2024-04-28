char *somestr(void) {
    static char c[] = "Hello, world!";
    return c;
}