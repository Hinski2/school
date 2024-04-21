#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>

struct node {
    char id[2];                     //sizeof = 2 * 1 
    int (*hashfn)(char *);          //sizeof = 8
    short flags;                    //sizeof = 2
    union u{
        struct s{
            short n_key;            //sizeof = 2
            int n_data[2];          //sizeof = 2 * 4
            unsigned char n_type;   //sizeof = 1
        } s;

        unsigned l_value[2];        //sizeof = 2 * 4
    } u;
};

struct nodeb {
    int (*hashfn)(char *);          // offset: 0, sizeof = 8, brak paddingu
    union ub{                       // offset: 8, sizeof = 12
        struct sb {
            unsigned char n_type;   // sizeof = 1
            short n_key;            // sizeof = 2  //dodatkowy padding 1 po nim
            int n_data[2];          // sizeof = 8
        } s;
        unsigned l_value[2];        
    } u;                            
    short flags;                    // offset = 20, sizeof = 2
    char id[2];                     // offset = 22, sizeof = 2
};

int main(){
    printf("%ld\n", sizeof(struct node));
    printf("%ld\n", sizeof(struct nodeb));
    printf("%ld\n", sizeof(union ub));
    puts("\n");

    printf("%ld\n", offsetof(struct node, id));
    printf("%ld\n", offsetof(struct node, hashfn));
    printf("%ld\n", offsetof(struct node, flags));
    printf("%ld\n", offsetof(struct node, u));
    puts("\n");

    printf("%ld\n", offsetof(union u, s));
    printf("%ld\n", offsetof(union u, l_value));
    puts("\n");

    printf("%ld\n", offsetof(struct s, n_key));
    printf("%ld\n", offsetof(struct s, n_data));
    printf("%ld\n", offsetof(struct s, n_type));
}

/*
    !!! przez wskaźnik w node wyrówanie jst do 8
    w uni u wyrównanie jest do 4

    s:  sizeof = 16
        0  n_key     l_value
        1  n_key     l_value
        2  padding   l_value
        3  padding   l_value

        4  n_data    l_value
        5  n_data    l_value
        6  n_data    l_value
        7  n_data    l_value

        8  n_data
        9  n_data
        10 n_data
        11 n_data

        12 n_type
        13 padding
        14 padding
        15 padding


node: sizeof = 40
0  id
1  id
2  padding
3  padding
4  padding
5  padding
6  padding
7  padding

8  hashfn
9  hashfn
10 hashfn
11 hashfn
12 hashfn
13 hashfn
14 hashfn
15 hashfn

16 flags
17 flags
18 padding
19 padding
20 n_key     l_value
21 n_key     l_value
22 padding   l_value
23 padding   l_value

24 n_data    l_value
25 n_data    l_value
26 n_data    l_value
27 n_data    l_value
28 n_data
29 n_data
30 n_data
31 n_data

32 n_type
33 padding
34 padding
35 padding
36 padding
37 padding
38 padding
39 padding
*/