#include <stdio.h>

void loop() {
    printf("unused\n");
}

int main() {
    for(int i=0;i<10;i++){
        loop();
    }
    return 0;
}