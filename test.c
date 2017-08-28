#include <stdio.h>
#include <unistd.h>
static char bar[] = "======================================="
                    "======================================>";
int main() {
    int i;
    for (i = 77; i >= 0; i--) {
        printf("[%s]\r", &bar[i]);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
    return 0;
}
