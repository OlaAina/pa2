#include <dirent.h>
#include <stdio.h>
#include<strings.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <time.h>

char **sortArray(char **sortThis,int n);
void longlsprint(char** items);

int main(int argc, char const *argv[]) {

int mode = 0; 
if(argc == 1){
    mode = 1;
}

else if((argc == 2) && (strcmp(argv[1], "-l") == 0)){
    mode = 2;
}

else{
    printf("error\n");
    return EXIT_SUCCESS;
}

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

sortArray(items, i);

if(mode == 2) {
    for(i=0; i<n; i++){
        longlsprint(&items[i]);
    }
}

else if (mode == 1){
    for(i=0; i<n; i++){
        printf("%s\n", items[i]);
    }
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

void longlsprint(char** items) {
    struct stat fileStat;
    stat(*items, &fileStat);
    
    //prints permissions
    printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");


    //get user info
    struct passwd *p = getpwuid(fileStat.st_gid);
    uid_t  uid=0;
    if ((p = getpwuid(uid)) == NULL) {
        printf("error"); 
        return;
    }

    if(p->pw_name == NULL) {
        printf(" %d", (int)p);
    }
    else {
        printf(" %s", p->pw_name);
    }
 
    //get group info
    struct group *grp = getgrgid(fileStat.st_gid);
    if(grp->gr_name == NULL){
        printf(" %d", (int)grp);
    }
    else{
        printf(" %s", grp->gr_name);
    }

    //print size 
    if (stat(*items, &fileStat) == 0) { 
        printf(" %lld", fileStat.st_size);
    }

    //date 
    char time[50];
    strftime(time, 50, "%b %d %H:%M", localtime(&fileStat.st_mtime));
    printf (" %s", time);

    printf(" %s", *items);
    printf("\n");
    return;
}

 