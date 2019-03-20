#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define HOMEDIR '.'

char path[3000] = ".", filename[30] = "file.txt", ex1[2] = ".\0", ex2[3] = "..\0", min[] = "Minotaur", bl[] = "Deadlock";

typedef struct dirent *direct;

void print(char *path) {
    FILE *sol = fopen("result.txt", "a");
    fprintf(sol, "%s\n", path);
    fclose(sol);
}

char *createname() {
    char *a = calloc(strlen(path) + strlen(filename) + 1, sizeof(char));
    char d[2] = "/\0";
    strcat(a, path);
    strcat(a, d);
    strcat(a, filename);
    return a;
}

void search() {
    DIR *dir = opendir(path);
    char *tmp;
    int a;

    tmp = createname(path, filename);
    FILE *doc;
    if ((doc = fopen(tmp, "r"))) {
        print(tmp);
        free(tmp);
        char buf[80];
        while (!feof(doc)) {
            fgets(buf, 80, doc);
            strcpy(filename,strtok(buf, " \n\0"));
            if (!strcmp(filename, min)) {
                exit(0);
            } else if (!strcmp(filename, bl)) {
                free(tmp);
                path[0] = HOMEDIR;
                path[1] = 0;
                return;
            }
            strcpy(filename,strtok(NULL, " \n\0"));
            path[0] = HOMEDIR;
            path[1] = 0;
            search();
        }
    } else {
        direct files;
        while ((files = readdir(dir))) {
            if (files->d_type == DT_DIR && strcmp(files->d_name, ex1) && strcmp(files->d_name, ex2)) {
                a = strlen(path);
                path[strlen(path) + 1] = '\0';
                path[strlen(path)] = '/';
                strcat(path, files->d_name);
                search();
                path[a] = '\0';
            }
        }
    }
    free(tmp);
}

int main() {
    FILE *a = fopen("result.txt", "w");
    fclose(a);
    search(path, filename);
}
