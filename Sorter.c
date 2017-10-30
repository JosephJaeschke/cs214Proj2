#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include "Sorter.h"

void mergeStr(CSVRow* arr,CSVRow* help, int lptr,int rptr,int llimit,int rlimit,int num)
{
    int i=lptr,j=llimit,k=0;
    while(i<=rptr && j<=rlimit) 
    {
	if(strcmp(arr[i].data,arr[j].data)==0)
	{
		if(arr[i].point<arr[j].point)
		{
        	    strcpy(help[k].data,arr[i].data);
        	    help[k].point=arr[i].point;
        	    strcpy(help[k].string_row,arr[i].string_row);
        	    k++;
        	    i++;
		}
        	else
		{
        	    strcpy(help[k].data,arr[j].data);
        	    help[k].point=arr[j].point;
        	    strcpy(help[k].string_row,arr[j].string_row);
        	    k++;
        	    j++;
		}
	}
        else if(strcmp(arr[i].data,arr[j].data)<0)
	{
            strcpy(help[k].data,arr[i].data);
            help[k].point=arr[i].point;
            strcpy(help[k].string_row,arr[i].string_row);
            k++;
            i++;
	}
        else
	{
            strcpy(help[k].data,arr[j].data);
            help[k].point=arr[j].point;
            strcpy(help[k].string_row,arr[j].string_row);
            k++;
            j++;
	}
    }

    while(i<=rptr)
    {
            strcpy(help[k].data,arr[i].data);
            help[k].point=arr[i].point;
            strcpy(help[k].string_row,arr[i].string_row);
            k++;
            i++;
    }
    while(j<=rlimit) 
    {
            strcpy(help[k].data,arr[j].data);
            help[k].point=arr[j].point;
            strcpy(help[k].string_row,arr[j].string_row);
            k++;
            j++;
    }
    for(i=lptr,j=0;i<=rlimit;i++,j++)
    {
	        strcpy(arr[i].data,help[j].data);
		arr[i].point=help[j].point;
		strcpy(arr[i].string_row,help[j].string_row);
    }
}

void sortStr(CSVRow* a,CSVRow *b, int i,int j,int num)
{
    int mid;
    if(i<j)
    {
        mid=(i+j)/2;
        sortStr(a,b,i,mid,num); 
        sortStr(a,b,mid+1,j,num);
        mergeStr(a,b, i,mid,mid+1,j,num); 
    }
}

void mergeInt(CSVRow* arr,CSVRow* help, int lptr,int rptr,int llimit,int rlimit,int num)
{
    int i=lptr,j=llimit,k=0;
    while(i<=rptr && j<=rlimit) 
    {
	if(strtof(arr[i].data,NULL)==strtof(arr[j].data,NULL))
	{
		if(arr[i].point<arr[j].point)
		{
        	    strcpy(help[k].data,arr[i].data);
        	    help[k].point=arr[i].point;
        	    strcpy(help[k].string_row,arr[i].string_row);
        	    k++;
        	    i++;
		}
        	else
		{
        	    strcpy(help[k].data,arr[j].data);
        	    help[k].point=arr[j].point;
        	    strcpy(help[k].string_row,arr[j].string_row);
        	    k++;
        	    j++;
		}
	}
        else if(strtof(arr[i].data,NULL)<strtof(arr[j].data,NULL))
	{
            strcpy(help[k].data,arr[i].data);
            help[k].point=arr[i].point;
            strcpy(help[k].string_row,arr[i].string_row);
            k++;
            i++;
	}
        else
	{
            strcpy(help[k].data,arr[j].data);
            help[k].point=arr[j].point;
            strcpy(help[k].string_row,arr[j].string_row);
            k++;
            j++;
	}
    }
    while(i<=rptr) 
    {
            strcpy(help[k].data,arr[i].data);
            help[k].point=arr[i].point;
            strcpy(help[k].string_row,arr[i].string_row);
            k++;
            i++;
    }
    while(j<=rlimit) 
    {
            strcpy(help[k].data,arr[j].data);
            help[k].point=arr[j].point;
            strcpy(help[k].string_row,arr[j].string_row);
            k++;
            j++;
    }
    for(i=lptr,j=0;i<=rlimit;i++,j++)
    {
        strcpy(arr[i].data,help[j].data);
		arr[i].point=help[j].point;
		strcpy(arr[i].string_row,help[j].string_row);
    }
}

void sortInt(CSVRow* a,CSVRow* b, int i,int j,int num)
{
    int mid;
    if(i<j)
    {
        mid=(i+j)/2;
        sortInt(a,b, i,mid,num); 
        sortInt(a,b, mid+1,j,num); 
        mergeInt(a,b, i,mid,mid+1,j,num); 
    }
}

void callMe(int size,char type,CSVRow* arr, CSVRow* b)
{
	if(type=='i')
	{
		sortInt(arr,b, 1,size-1,size);
	}
	else
	{
		sortStr(arr,b, 1,size-1,size);
	}
	return;
}

void trim(char* str)
{
	char * t = malloc(strlen(str)); 
	int i =0;
	int j=0;
	for(i=0;i<strlen(str);i++)
	{
		if(isspace(str[i])==0)
		{
			t[j]=str[i];
			j++;
		}
	}
	t[j]='\0';
	strcpy(str,t);
	free(t);
}

int main(int argc, char ** argv){
	
	int file_count = 0;
	char c = 0;
	int i = 0;
	char * str_file = malloc(10);
	char * token = malloc(10);
	int row_position = 0;
	int j;
	if(stdin == NULL){
		fprintf(stderr, "ERROR: <No Input In STDIN>\n");	
		free(token);
		free(str_file);			
		return 0;
	}
	
	if(argv[1] == NULL){
		fprintf(stderr, "ERROR: <Expected -c \"item\">\n");	
		free(token);
		free(str_file);
		return 0;
	}

	if(argv[1][0] != '-' && argv[1][1] != 'c' && argv[2] == NULL){
		fprintf(stderr, "ERROR: <Expected -c \"item\">\n");
		free(token);
		free(str_file);
		return 0;
	}
	
	token = strdup(argv[2]);

	//fprintf(stdout, "%s\n", token);	
				
	c = getc(stdin);
	while (c != EOF) {
		//printf("%c\n",c);
		str_file = realloc(str_file, (i+1) * sizeof(char));	
		str_file[i] = c;
		if(c == '\n'){
			file_count++;
		}
		i++;
		c = getc(stdin);
    }
        
	str_file[i] = '\0';
	
	CSVRow *movies = malloc(file_count * sizeof(CSVRow));
	//token = strtok(str_file, "\n");
	
	for(j = 0; j < file_count; j++){
		movies[j].data = malloc(10000);
		movies[j].point = j;
		movies[j].string_row = malloc(10000);
	}

	CSVRow* help=malloc(sizeof(CSVRow)*file_count);    //array used for merging
    for(j =0;j<file_count;j++)
    {
	help[j].data=malloc(10000);
	help[j].point=j;
	help[j].string_row=malloc(10000);
    }

	//CSVRow *tempy = malloc(file_count * sizeof(CSVRow));
	//token = strtok(str_file, "\n");
	
	//for(int j = 0; j < file_count; j++){
	//	tempy[j].data = malloc(1000);
	//	tempy[j].point = j;
	//	tempy[j].string_row = malloc(1000);
	//}


	int temp = 0;
	int count = 0;
	int index = 0;
	int comma_position_max = 0;
	int p1 = 0;
	int p2 = 0;
	int char_found = 0;
	int comma_number = 0;
	char * check_token = malloc(1000);
	c = 0;

	for(j = 0; j < i; j++){
		if(str_file[j] == '\n'){
			//printf("a\n");
			strncpy(movies[count].string_row, str_file+temp,j-temp+1);
			movies[count].string_row[j-temp+1] = '\0';
			if (count == 0){
				c = movies[count].string_row[index];
				for(index = 0; index<strlen(movies[count].string_row) ; index++){
					//fprintf(stdout, "%c\n", c);
					c = movies[count].string_row[index];
					if(c == ',' || movies[count].string_row[index+1] == '\n'){
						if( movies[count].string_row[index+1] == '\n'){
							index++;
						}
						comma_position_max++;
						if(index == p1 || index == p1+1){
							check_token = "\0";
						}
						else{
							strncpy(check_token, movies[count].string_row+p1,index-p1);
							check_token[index-p1] =  '\0';
							//fprintf(stdout, "[%s] , [%s]\n", check_token, token);
						}
						if(strcmp(check_token,token) == 0){
							char_found = 1;
							//fprintf(stdout, "[%s] , [%s]\n", check_token, token);
							break;
						}
						p1 = index+1;
						if( movies[count].string_row[index+1] == '\n'){
							index--;
						}

					}
					//printf("%d\n %c",char_found, c);
				}
				if(char_found == 0){
					fprintf(stderr, "ERROR: <Selected item was not found in parameters>\n");
					free(check_token);
					free(movies);
					free(token);
					free(str_file);

					return 0;
				}
				//fprintf(stdout,"%d : %d\n",char_found , comma_position_max);
				//fprintf(stdout, "[%s] : [%s] \n",token, check_token);
				strcpy(movies[count].data, token);
				movies[count].data[strlen(token)+1] = '\0';
			}
			else{
				//fprintf(stdout, "%d \n ", count);
				comma_number = 0;
				index = 0;
				p1 = 0;
				c = movies[count].string_row[index];
				for(index = 0; index<strlen(movies[count].string_row); index++){
					//fprintf(stdout, "%c\n", c);
					c = movies[count].string_row[index];
					if(c == ',' && index+1 != strlen(movies[count].string_row) && movies[count].string_row[index+1] == '"'){
							
						comma_number++;
						if((index == p1) && (comma_number == comma_position_max)){
							//movies[count].data = "0\0";
							break;
						}
						else if(comma_number == comma_position_max){
							strncpy(movies[count].data, movies[count].string_row+p1,index-p1);
							//fprintf(stdout, "[%s] , [%s]\n", check_token, token);
							//movies[count].data[index-p1] = '\0';
							//fprintf(stdout, "%d: %s\n",count, movies[count].data);	
							trim(movies[count].data);
							break;
						}
						p1 = index+1;
						
						index = index+2;
						int x;
						for(x = 0; c != '"'; index++){
							c = movies[count].string_row[index];
						}	
						
						c = movies[count].string_row[index];
						//fprintf(stdout,"%c\n" , c);
						comma_number++;
						if((index == p1) && (comma_number == comma_position_max)){
							//movies[count].data = "0\0";
							break;
						}
						else if(comma_number == comma_position_max){
							strncpy(movies[count].data, movies[count].string_row+p1,index-p1);
							//fprintf(stdout, "[%s] , [%s]\n", check_token, token);
							//movies[count].data[index-p1] = '\0';
							//fprintf(stdout, "%d: %s\n",count, movies[count].data);	
							trim(movies[count].data);
							break;
						}
						p1 = index+1;
						index++;
						c = movies[count].string_row[index];
	
					}
					if(c == ',' || movies[count].string_row[index+1] == '\n'){

						if( movies[count].string_row[index+1] == '\n'){
							index++;
						}

						comma_number++;
						if((index == p1) && (comma_number == comma_position_max)){
							//movies[count].data = "NULL";
							break;
						}
						else if(comma_number == comma_position_max){
							strncpy(movies[count].data, movies[count].string_row+p1,index-p1);
							//fprintf(stdout, "[%s] , [%s]\n", check_token, token);
							//movies[count].data[index-p1] = '\0';
							//fprintf(stdout, "%d: %s\n",count, movies[count].data);	
							trim(movies[count].data);
							break;
						}
						p1 = index+1;
						if( movies[count].string_row[index+1] == '\n'){
							index--;
						}

					}
				}
			}
			
			temp = j+1;
			count++;
		}
	}
	
	char type = 'i';
	int k;
	for(j = 1; j < file_count; j++){
		for(k = 0; movies[j].data[k] != '\0'; k++){
			if(!(isdigit(movies[j].data[k]))){
				if(movies[j].data[k] != '.' || movies[j].data[k] != '-'){
					type = 's';	
				}
			}
		}
	}
	//printf("%d \n", type);
	//mergesort(movies,1,file_count-1,file_count);
	callMe(file_count,type,movies,help);
	//printf("heyo\n");
	//printf("\n");
	for(j = 0; j < file_count; j++){
		fprintf(stdout, "%s", movies[j].string_row);
		//printf("[%s]\n", movies[j].data);
	}
	
	//printf("\n\n");

	

	for(j = 0; j < file_count; j++){
		free(movies[j].data);
		free(help[j].data);
		//movies[j].point = j;
		free(movies[j].string_row);
		free(help[j].string_row);
	}


	free(check_token);
	free(movies);
	free(help);
	free(token);
	free(str_file);
	return 0;
}
