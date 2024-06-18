int func(int a, ...);

int x = func(10);

int func (int a, ...){
    int i;
    for (i = 0; i < 5; i++){
        a++;
    }
    return a;
}

int y = func(5);