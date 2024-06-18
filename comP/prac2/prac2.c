#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define NUMBER 256 
#define STAR 258 
#define RPAREN 260 
#define EXPRESSION 0
#define FACTOR 2
#define PLUS 257 
#define LPAREN 259 
#define END 261 
#define TERM 1 
#define ACC 999

typedef enum {
    INT,
    FLT
} kind;

typedef struct {
    kind type;
    union {
        int i;
        float f;
    } value;
} RET;

int yyparse();
void push(int i);
void shift(int i);
void reduce(int i);
void yyerror();
int yylex();

int action[12][6]={
    {5, 0, 0, 4, 0, 0}, {0, 6, 0, 0, 0, ACC}, {0,-2, 7, 0,-2,-2}, 
    {0,-4,-4, 0,-4,-4}, {5, 0, 0, 4, 0, 0}, {0,-6,-6, 0,-6,-6},
    {5, 0, 0, 4, 0, 0}, {5, 0, 0, 4, 0, 0}, {0, 6, 0, 0, 11, 0}, 
    {0,-1, 7, 0,-1,-1}, {0,-3,-3, 0,-3,-3}, {0,-5,-5, 0,-5,-5}};

int go_to[12][3]={
    {1,2,3},{0,0,0}, {0,0,0},{0,0,0},{8,2,3},{0,0,0},
    {0,9,3}, {0,0,10}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0} };

int prod_left[7]={0,EXPRESSION, EXPRESSION, TERM,TERM, FACTOR, FACTOR}; 
int prod_length[7]={0,3,1,3,1,3,1};

int stack[1000]; 
RET value[1000];
int top=-1; 
int sym;
char yytext[32]; 
RET yylval; 

void retPrint(RET ret) {
    if (ret.type == INT) {
        printf("값 : %d\n", ret.value.i);
    } else if (ret.type == FLT) {
        printf("값 : %f\n", ret.value.f);
    } else {
        printf("type error\n");
    }
}

RET retCalc(RET a, RET b, char ch) {
    RET result;

    if (ch == '+') {
        if (a.type == INT) {
            if (b.type == INT) {
                result.type = INT;
                result.value.i = a.value.i + b.value.i;
            }
            else {
                result.type = FLT;
                result.value.f = (float)a.value.i + b.value.f;
            }
        } 

        else {
            if (b.type == INT) {
                result.type = FLT;
                result.value.f = a.value.f + (float)b.value.i;
            }
            else {
                result.type = FLT;
                result.value.f = a.value.f + b.value.f;
            }
        }
    }

    else if (ch == '*') {
        if (a.type == INT) {
            if (b.type == INT) {
                result.type = INT;
                result.value.i = a.value.i * b.value.i;
            }
            else {
                result.type = FLT;
                result.value.f = (float)a.value.i * b.value.f;
            }
        } 

        else {
            if (b.type == INT) {
                result.type = FLT;
                result.value.f = a.value.f * (float)b.value.i;
            }
            else {
                result.type = FLT;
                result.value.f = a.value.f * b.value.f;
            }
        }
    }

    return result;
}

void main() {
    yyparse();
}

int yyparse() { 
    int i;
    stack[++top]=0;
    sym=yylex();
    do{ 
        i=action[stack[top]][sym-256];
        if (i==ACC) {
            printf("success!\n");
            retPrint(value[top]);
            return 0;
        }
        else if (i>0) 
            shift(i);
        else if (i<0) 
            reduce(-i);
        else {
            printf("%d\n", i);
            yyerror();
        }
    }
    while (i!=ACC);
}

void push(int i) {
    stack[++top]=i; 
}

void shift(int i) {
    push(i);
    value[top].type = yylval.type;
    value[top].value = yylval.value;
    sym = yylex(); 
}

void reduce(int i) {
    int old_top;
    top-=prod_length[i];
    old_top=top;
    push(go_to[stack[old_top]][prod_left[i]]);

    switch(i) {
        case 1: value[top]=retCalc(value[old_top+1], value[old_top+3], '+');
            break;
        case 2: value[top]=value[old_top+1];
            break;
        case 3: value[top]=retCalc(value[old_top+1], value[old_top+3], '*');
            break;
        case 4: value[top]=value[old_top+1];
            break;
        case 5: value[top]=value[old_top+2];
            break;
        case 6: value[top]=value[old_top+1];
            break;
        default: yyerror("parsing table error");
            break;
    }
}

void yyerror() {
    printf("syntax error\n");
    exit(1); 
}


int yylex() {
    static char ch=' ';
    int i=0;

    while (ch==' '||ch=='\t'||ch=='\n') ch=getchar();
    if (isdigit(ch)) {
        do {
            yytext[i]=ch;
            ch=getchar();
            i++;
        }
        while (isdigit(ch));

        if (ch == '.') {
            ch=getchar();
            float div = 1.0f;

            yylval.type = FLT;
            yylval.value.f = atof(yytext);

            for(int j = 0; j < i; j++)
                yytext[j]=0;
            i = 0;

            do {
                yytext[i]=ch;
                ch=getchar();
                i++;
                div *= 10.0f;
            }
            while (isdigit(ch));

            yylval.value.f += atof(yytext)/div;
        }

        else {
            yylval.type = INT;
            yylval.value.i = atoi(yytext);
        }

        for(int j = 0; j < i; j++)
            yytext[j]=0;

        return(NUMBER); 
    }
    else if (ch=='+'){ ch=getchar(); return(PLUS);} 
    else if (ch=='*'){ ch=getchar(); return(STAR);} 
    else if (ch=='('){ ch=getchar(); return(LPAREN);} 
    else if (ch==')'){ ch=getchar(); return(RPAREN);} 
    else if (ch==EOF) return(END);
    else yyerror();
}