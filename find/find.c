#include <dirent.h>
#include <stdio.h>
#include<strings.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>

int stringContains(char *checkForThis, char *checkInThis);

int main(int argc, char const *argv[]) {
DIR *d;
struct dirent *dir;
int n=0;
int i=0;
char *checkForThis;
checkForThis=malloc(strlen(argv[1])*sizeof(char));
strcpy(checkForThis,argv[1]);
d = opendir("./");
while((dir = readdir(d)) != NULL) {
    if ( !strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..") ){

    } 
    else {
        n++;
        }
}
rewinddir(d);

char **items;
items= malloc(n*sizeof(char**));
while((dir = readdir(d)) != NULL) {
    if ( !strcmp(dir->d_name, ".") || !strcmp(dir->d_name, "..") ) {

    }
    else {
        items[i] = (char*) malloc (strlen(dir->d_name)+1);
        strncpy (items[i],dir->d_name, strlen(dir->d_name) );
        i++;
    }
}
rewinddir(d);

for(int i=0;i<n;i++){
    int x= stringContains(checkForThis,items[i]);
    if(x==1){
        printf("%s\n",items[i]);
    }
}

for(int i=0;i<n;i++){
    free(items[i]);
}
free(items);
free(checkForThis);
closedir(d);
return 0;
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
    free(a);
    
}