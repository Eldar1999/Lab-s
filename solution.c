#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

typedef struct dirent* dirent;

void print(char* path)
{
	FILE* sol = fopen("result.txt","a");
	fprintf(sol,"%s",path);
}

void search(char* path,char* filename)
{
	DIR* base = opendir(path);
	FILE* file;
	if((file = fopen(filename,"r")))
	{
		char* s = malloc(sizeof(char)*80);
		do
		{
			fgets(s,80,file);
			s = strtok(s," ");
			s = strtok(s," ");
			if(!strtok(s,"Deadlock"))
			{
				print(strcat(strcat(path,"/"),filename));
				return;
			}
			else if (!strtok(s,"Minotaur"))
			{
				print(strcat(strcat(path,"/"),filename));
				exit(0);
			}
			else
			{
				search(path,s);
			}
		}while(feof(file));
	}
	else
	{
		dirent direct;
		while((direct = readdir(base)))
		{
			if(direct->d_type == 4 && !strcmp(direct->d_name,".") && !strcmp(direct->d_name,".."))
			{
				path[strlen(path)+1]='\0';
				path[strlen(path)]='/';
				search(strcat(path,direct->d_name),filename);
				path[strlen(path)-1] = '\0';
			}
		}
	}
}

int main()
{
	search(".","file.txt");
}
