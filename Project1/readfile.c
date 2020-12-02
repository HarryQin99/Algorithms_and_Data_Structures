#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "link.h"
#include "search.h"

#define FIRST 1
#define SECOND 2
#define DOUBLE 2
#define DATA_AMOUNT 11
#define COMMA ','

char** find_all_key(int *amount){
    char *line = NULL;
    char **array_key = NULL;
    size_t lineBufferLength = 0;
    int size_array = 1;
    int amount_key = 0;
    array_key = (char **)malloc(sizeof(char*)*size_array);
    assert(array_key);
    while (getline(&line,&lineBufferLength,stdin) != EOF){
        size_array++;
        array_key = (char **)realloc(array_key,size_array*sizeof(char*));
        assert(array_key);
        make_key_valid(&line);
        if (strlen(line)>0){
        //printf("%s\n",line);
            array_key[amount_key] = (char*)malloc(sizeof(char)*(strlen(line)+1));
            assert(array_key[amount_key]);
            strcpy(array_key[amount_key],line);
            amount_key++;
        }
    }
    free(line);
    *amount = amount_key;
    return array_key;
}


char **get_all_header(FILE* fp){
    char *line = NULL;
    size_t lineBufferLength = 0;
    getline(&line, &lineBufferLength,fp);
    char **array_header = (char **)malloc(sizeof(char*)*(DATA_AMOUNT));
    assert(array_header);
    int position_array = 0;
    int position = 0;
    char *header = (char*)malloc(sizeof(char)*128);
    assert(header);
    for (int i = 0;i < strlen(line);i++){
        if (line[i] == COMMA|| line[i] == '\n'){          
            header[position] = '\0';
            array_header[position_array] = (char*)malloc(sizeof(char)*(strlen(header)+1));
            strcpy(array_header[position_array],header);
            position_array++;
            position = 0;       
        }
        else if (line[i] == '\r'){

        }
        else{
            header[position++] = line[i];
        }
    }
    
    free(header);
    free(line);
    return array_header;
}