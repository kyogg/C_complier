#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

float num;
enum {NONE,NUMBER,PLUS,STAR,LP,RP,END} token;

void get_token();
float expression();
float term();
float factor();
void error(int i);

void main()
{
    float result;
    get_token();
    result=expression();
    if (token!=END)
        error(3);
    else
        printf("%f\n",result);
}

float expression ( )
{
    float result;
    result=term();
    while (token==PLUS) {
        get_token();
        result=result+term( );
    }
    return (result);
}

float term ( )
{
    float result;
    result=factor();
    while (token==STAR) {
        get_token();
        result=result*factor( );
    }
    return (result);
}

float factor ( ) {
    float result;
    if (token==NUMBER) {
        result=num;
        get_token();
    }
    else if (token==LP) {
        get_token();
        result=expression();
        if (token==RP)
            get_token();
        else
            error(2);
    }
    else
        error(1);
    return (result);
}

void get_token() {
    char ch = getchar();
    
    while (isspace(ch)) {
        ch = getchar();
    }

    switch (ch) {
        case '+':
            token = PLUS;
            break;
        case '*':
            token = STAR;
            break;
        case '(':
            token = LP;
            break;
        case ')':
            token = RP;
            break;
        case EOF:
            token = END;
            break;
        default:
            if (isdigit(ch)) {
                num = ch - '0';
                ch = getchar();
                float frac = 0.1;

                while (isdigit(ch)) {
                    num = num * 10 + (ch - '0');
                    ch = getchar();
                }
                if (ch == '.') {
                    ch = getchar();
                    if (!isdigit(ch)) {
                        error(1);
                    }
                    while (isdigit(ch)) {
                        num = num + (ch - '0')*frac;
                        frac /= 10;
                        ch = getchar();
                    }
                }
                ungetc(ch, stdin);
                token = NUMBER;
            } else {
                token = NONE;
            }
            break;
    }
}

void error (int i)
{
    switch (i) {
        case 1:
            printf("error : 잘못된 값 입력\n"); 
            break;
        case 2: 
            printf("error : 잘못된 괄호 입력\n");
            break;
        case 3:
            printf("error : 잘못된 문자 입력\n");
            break;
    }
    exit(1);
}