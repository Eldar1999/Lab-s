#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>

struct list {
    char *path;
    struct list *prev;
};

void print(struct list *fpath) {
    FILE *stream = fopen("result.txt", "w");
    char tmp[30][100];
    struct list* temp;
    int i = 0;
    while (fpath) {
        strcpy(tmp[i++], fpath->path);
	temp = fpath;
        fpath = fpath->prev;
	free(temp);
    }
    for (int j = i - 1; j >= 0; j--) {
        fprintf(stream, "%s\n", tmp[j]);
    }
    fclose(stream);
}

char *createpath(char *path, char *name) {
    char *a = calloc(100, sizeof(char));
    strcpy(a, path);
    strcat(a, (const char *) &"/");
    strcat(a, name);
    return a;
}

int search(struct list *prev, char* path, char* filename) {
    DIR *dir = opendir(path);
    struct dirent *obj;
    char **dirarr = 0, **filearr = 0;
    int i = 0;
    while ((obj = readdir(dir))) {
        if (obj->d_type == DT_DIR && strcmp(obj->d_name, (char *) &".") != 0 &&
            strcmp(obj->d_name, (char *) &"..") != 0) {
            dirarr = realloc(dirarr, (i + 1) * sizeof(char *));
            dirarr[i] = calloc(100, sizeof(char));
            strcpy(dirarr[i++], obj->d_name);
        } else if (!strcmp(obj->d_name, filename)) {
            closedir(dir);
            for (int j = 0; j < i; j++) {
                free(dirarr[j]);
            }
            free(dirarr);
            dirarr = NULL;
            i = 0;
            char *filepath = createpath(path, filename);
            FILE *file = fopen(filepath, "r");
            struct list *fpath = calloc(1, sizeof(struct list));
            fpath->path = calloc(100, sizeof(char));
            fpath->prev = prev;
            strcpy(fpath->path, filepath);
            prev = fpath;
            free(filepath);
            do {
                filearr = realloc(filearr, (i + 1) * sizeof(char *));
                filearr[i] = calloc(30, sizeof(char));
                fgets(filearr[i], 30, file);
                if (!strcmp(filearr[i], (const char *) &"Deadlock")) {
                    fclose(file);
                    free(fpath);
                    return 1;
                } else if (!strcmp(filearr[i], (const char *) &"Minotaur")) {
                    fclose(file);
                    print(fpath);
                    return 2;
                }
                filearr[i] = &filearr[i][9];
                filearr[i][strlen(filearr[i]) - 1] = 0;
                i++;
            } while (!feof(file));
            free(filearr[i - 1] - 9);
            fclose(file);
            break;
        }
    }
    int return_value = 0;
    if (filearr) {
        for (int j = 0; j < i - 1; j++) {
            if (return_value != 2) {
                strcpy(filename, filearr[j]);
                strcpy(path, "./labyrinth");
                return_value = search(prev,path,filename);
            }
            free(filearr[j] - 9);
        }
        free(filearr);
    } else if (dirarr) {
        char *tmp = calloc(100, sizeof(char)), *tmp2;
        strcpy(tmp, path);
        for (int j = 0; j < i; j++) {
            tmp2 = createpath(path,dirarr[j]);
            strcpy(path, tmp2);
            free(tmp2);
            free(dirarr[j]);
            if (return_value == 0) return_value = search(prev, path, filename);
            strcpy(path, tmp);
        }
        free(dirarr);
        free(tmp);
    }
    return return_value;
}

int main() {
    char path[100] = "./labyrinth",file[30] = "file.txt";
    return search(NULL, path, file);
}
