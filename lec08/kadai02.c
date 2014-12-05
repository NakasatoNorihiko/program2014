#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAX_LEN 1000

int main(int argv, char *argc[])
{
    FILE *fpr, *fpw;
    char buf[MAX_LEN];
    int i;

    fpr = fopen(argc[1], "r");
    fpw = fopen(argc[2], "w");

    if (fpr == NULL || fpw == NULL) {
        printf("File open failed\n");
        return 1;
    }

    while ((buf[0] = fgetc(fpr)) != EOF) {
        i = 0;
        while ((buf[0] == ' ') && buf[0] != EOF) {
            buf[0] = fgetc(fpr);
        }
        i++;
        while (((buf[i] = fgetc(fpr)) != '.') && (buf[i] != '!') && (buf[i] != '?') && (buf[i] != EOF)) {
            i++;
        }
        buf[i+1] = '\0';
        
        i = 0;
        while (isalpha(buf[i]) == 0  && buf[i] != EOF) {
            i++;
        }
        
        buf[i] = toupper(buf[i]);
        for (i = 1; i < strlen(buf)-1; i++) {
            if (buf[i] == 'i' && isalpha(buf[i-1]) == 0 && isalpha(buf[i+1]) == 0) {
                buf[i] = toupper(buf[i]);
            }
        }
        
        fprintf(fpw, "%s ", buf);
    }
    
    fclose(fpr);
    fclose(fpw);
    
    return 0;
}
