int func1(int a);

int func2 (int a){
    int i;
    for (i = 0; i < 5; i++){
        a++;
    }
    return a;
}

int main(){
    int x, y;
    x = func1(10);
    y = func2(10);
    printf("func1 = %d\n", x);
    printf("func2 = %d\n", y);
}

int func1 (int a){
    int i;
    for (i = 0; i < 5; i++){
        a++;
    }
    return a;
}