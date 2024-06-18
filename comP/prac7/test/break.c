void main(){
    int i;
    for (i = 0; i < 10; i++){
        if (i == 2)
            continue;
        printf("%d\n", i);
        if (i == 5)
            break;
    }
    return;
}