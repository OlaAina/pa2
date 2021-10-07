#include <dirent.h>
#include <stdio.h>
#include<strings.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>

char **sortArray(char **sortThis,int n);

int main(int argc, char const *argv[]) {
DIR *d;
struct dirent *dir;
int n=0;
int i=0;
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

sortArray(items,i);

for(i=0; i<n; i++){
printf("%s\n", items[i]);
}
for(int i=0;i<n;i++){
        free(items[i]);
}
free(items);
closedir(d);
return 0;
}

char **sortArray(char **sortThis,int n){
    int i,j;
    int x=100;
    char *store= malloc(x*sizeof(char));
    for (i = 0; i < n-1; i++){
        for (j = i + 1; j < n; j++){
            if (strcasecmp(sortThis[i],sortThis[j])>0)
            {
                strcpy(store,sortThis[i]);
                strcpy(sortThis[i],sortThis[j]);
                strcpy(sortThis[j],store);
            }
        }
    }
    free(store);
    return sortThis;
}
           