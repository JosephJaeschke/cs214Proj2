#include <unistd.h>  
#include <stdio.h>  
#include <dirent.h>  
#include <string.h>  
#include <sys/stat.h>  
#include <sys/wait.h>
#include <stdlib.h>  
  
int isCSV(char* name)
{
	char* temp=strdup(name);
	char* ext=strrchr(temp,'.');
	if(ext!=NULL&&strcmp(ext,".csv")==0)
	{
		free(temp);
		return 1;
	}
	free(temp);
	return 0;
}
  
void printdir(char *dir)  
{  
	DIR *dp;  
	struct dirent *entry;  
	struct stat statbuf;  
	char* path=malloc(1000);
	if((dp=opendir(dir))==NULL)
	{  
        	return ;  
    	}  
    	chdir(dir);  
	int id;
	int procs=0;
    	while((entry=readdir(dp))!=NULL)
	{
		strcpy(path,entry->d_name);
		strcpy(path,"\0");
        	lstat(entry->d_name,&statbuf);  
        	if(S_ISDIR(statbuf.st_mode))
		{  
            		if(strcmp(entry->d_name, ".") == 0||strcmp(entry->d_name, "..") == 0)   
                	{
				continue;
			}
			procs++;
			id=fork();
			if(id==0)
			{
				dp=opendir(entry->d_name);
				if(dp==NULL)
				{
					return;
				}
				chdir(entry->d_name);
			}
        	} 
		else if(isCSV(entry->d_name)) //fork on each csv to sort
		{
			/*
			//sortCSVFile(char* sortBy,char* fileName,char* outDir);
            		procs++;
			printf("forking on %s\n",entry->d_name);
			idCSV=fork()
			if(idCSV==0)
			{
				//sortCSVFile(char* sortBy,char* fileName,char* outDir);
			}
			*/
			printf("%s\n",entry->d_name);
		}
    	} 
	int i;
	for(i=0;i<procs;i++)
	{
		wait(NULL);
	}
    	chdir("..");  
    	closedir(dp);     
	free(path);
}  
  
  
int main(int argc, char *argv[])  
{ 

    char *topdir = argv[1];  
    if (argc >= 2)  
        topdir = argv[1];  
  
    printdir(topdir);  
    return 0; 
}  
