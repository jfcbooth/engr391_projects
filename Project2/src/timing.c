

void delay(unsigned int count){
    unsigned int i, j;
    for(i = 0; i < count; i++){
        for(j = 0; j < 100000; j++);
    }
}
