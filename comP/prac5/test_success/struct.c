struct s1;

struct s2 {
    struct s1 s;
    int x;
};

struct s1 {
    int a;
    float b;
    char c;
} st;

struct s1 example = {1, 2.0, 'a'};