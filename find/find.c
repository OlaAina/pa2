#include <dirent.h>
#include <stdio.h>
#include<strings.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>


int stringContains(char *checkForThis, char *checkInThis);
void readInto(char *filename, char *checkForThis);

int main(int argc, char const *argv[]) {

char *checkForThis;
checkForThis=malloc(strlen(argv[1])*sizeof(char));
strcpy(checkForThis,argv[1]);
readInto(".",checkForThis);
free(checkForThis);
return EXIT_SUCCESS;
}

void readInto(char *basePath, char *checkForThis)
{
    DIR *dir;
    dir = opendir(basePath);
    struct dirent *dp;
    int i;
    char path[1000];
    if (!dir){
        return;
    }
    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);
            if(stringContains(checkForThis,dp->d_name)==1){
                    printf("%s\n",path);
            }

            readInto(path,checkForThis); 
        }
    }

    closedir(dir);
}

int stringContains(char *checkForThis, char *checkInThis){
    char *a;
    a= strstr(checkInThis,checkForThis);
    if(a){
        return 1;
    }
    else{
        return 0;
    }
}