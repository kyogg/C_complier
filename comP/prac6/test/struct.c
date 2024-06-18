struct s1 { int b; } c;
struct s2 { struct s1 b; } e;
struct s { 
    int a; 
    struct ss{
        int x; 
        struct s y;}
        b; 
    int c; } d;
struct s3 { int a; struct s3 b; int c; } g;