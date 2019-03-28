#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

FILE *sol;

char path[300] = ".", filename[300] = "file.txt", ex1[2] = ".\0", ex2[3] = "..\0", min[] = "Minotaur", bl[] = "Deadlock";
typedef struct dirent *direct;

void print(char *str) {
    fprintf(sol, "%s\n", str);
}

char *createname() {
    char *a = calloc(strlen(path) + strlen(filename) + 1, sizeof(char));
    char d[2] = "/\0";
    strcpy(a, path);
    strcat(a, d);
    strcat(a, filename);
    return a;
}

void search() {
    DIR *dir = opendir(path);
    direct temp = 0;
    char **dirarr = calloc(1, sizeof(char *)), **filearr = calloc(1, sizeof(char *)), *filepath = 0;
    int i = 0;
    FILE *file = NULL;
    while ((temp = readdir(dir))) {
        if (temp->d_type == DT_DIR && strcmp(temp->d_name, ex1) != 0 && strcmp(temp->d_name, ex2) != 0) {
            dirarr = realloc(dirarr, sizeof(char *) * (i + 1));
            dirarr[i] = calloc(100, sizeof(char));
            strcat(strcat(strcpy(dirarr[i++], path), (char *) &"/"), temp->d_name);
        } else if (!strcmp(temp->d_name, filename)) {
            /* ##################*/
            for (int j = 0; j < i; j++) {
                dirarr[j] = "\0";
            }
            i = 0;
            dirarr = 0;
            /* ###################*/
            filepath = createname();
            file = fopen(filepath, "r");
            while (!feof(file)) {
                filearr = realloc(filearr, sizeof(char *) * (i + 1));
                filearr[i] = calloc(80, sizeof(char));
                fgets(filearr[i], 80, file);
                if (!strcmp(filearr[i], bl))
                    return;
                else if (!strcmp(filearr[i], min))
                    exit(0);
                filearr[i] = strtok(filearr[i], " \0\n");
                filearr[i++] = strtok(NULL, "\n \0");
            }
            print(filepath);
            free(filepath);
            fclose(file);
            break;
        }
    }
    closedir(dir);
    if (dirarr) {
        filepath = calloc(100,sizeof(char));
        strcpy(filepath,filename);
        for (int j = 0; j < i; j++) {
            if (strcmp(filename,filepath) != 0) break;
            strcpy(path, dirarr[j]);
            search();
        }
    } else if (filearr) {
        for (int j = 0; j < i; j++) {
            strcpy(path, (char *) &".");
            strcpy(filename, filearr[j]);
            search();
        }
        free(filearr);
    }
}

int main() {
    fclose(fopen("result.txt", "w"));
    sol = fopen("result.txt", "a");
    search();
    fclose(sol);
}
