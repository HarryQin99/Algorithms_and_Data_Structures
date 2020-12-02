#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "link.h"
#include "free.h"

#define COMMA ','
#define QUOTE '"'
#define DATA_AMOUNT 11
#define MAX_FIELD 128
#define TWO 2
#define ZERO 0
#define SWITCH_LINE '\n'




char *make_valid(char *string){
    int len = strlen(string);
    char prev_char = ' ';
    char *output;
    output = (char *)malloc(sizeof(char)*MAX_FIELD);
    assert(output);
    int position = 0;
    for (int i = 0; i< len; i++){
        if (string[i] == QUOTE){
            if (i != ZERO && i != len-1 && prev_char != QUOTE){
                output[position++] = string[i];
                prev_char = string[i];
            }
            else{

            }
        }
        else{
            output[position++] = string[i];
            prev_char = string[i];
        }
    }
    output[position] = '\0';
    strcpy(string,output);
    free(output);
    return string;

}


data_t *split_line(char *line){
    //printf("%s",line);
    //data_t *data = NULL;
    int quote = 0;
    //char **array_string = NULL;
    char **array_string = (char **)malloc(sizeof(char *)*DATA_AMOUNT);
    data_t *data = (data_t *)malloc(sizeof(data_t));
    assert(array_string);
    int position = 0;
    int position_array = 0;
    for (int i = 0; i<DATA_AMOUNT; i++){
        array_string[i] = (char *)malloc(sizeof(char)*MAX_FIELD);
        assert(array_string[i]);
    }
    //int len = strlen(line); //same as strlen()
    for (int i = 0;i < strlen(line);i++){
        if (line[i] == QUOTE){
            quote++;
        }
    
        if ((line[i] == COMMA && quote%TWO == 0)){
            array_string[position_array][position] = '\0';
            position_array++;
            position = 0;
        }
        else if (line[i] == '\n'){
            //int len = strlen(array_string[position_array])-1;
            array_string[position_array][position] = '\0';
        }
        else if (line[i] == '\r'){
            //array_string[position_array][strlen(array_string[position_array])-1] = '\0';
        }
        else{
            array_string[position_array][position++] = line[i];
        }
    }

    for (int i = 0; i< DATA_AMOUNT;i++){
        array_string[i] = make_valid(array_string[i]);
        //printf("%s",array_string[i]);
    }
    for (int i =0; i< DATA_AMOUNT; i++){
        switch(i){
            case 0:
                data->census_year = (char *)malloc(sizeof(char)*(strlen(array_string[i])+1));
                assert(data->census_year);
                strcpy(data->census_year,array_string[i]);
                break;
            case 1:
                data->block_id = (char *)malloc(sizeof(char)*(strlen(array_string[i])+1));
                assert(data->block_id);
                strcpy(data->block_id,array_string[i]);
                break;
            case 2:
                data->property_id = (char *)malloc(sizeof(char)*(strlen(array_string[i])+1));
                assert(data->property_id);
                strcpy(data->property_id,array_string[i]);
                break;
            case 3:
                data->base_property_id = (char *)malloc(sizeof(char)*(strlen(array_string[i])+1));
                assert(data->base_property_id);
                strcpy(data->base_property_id,array_string[i]);
                break;
            case 4:
                data->club_area = (char *)malloc(sizeof(char)*(strlen(array_string[i])+1));
                assert(data->club_area);
                strcpy(data->club_area,array_string[i]);
                break;
            case 5:
                data->trading_name = (char *)malloc(sizeof(char)*(strlen(array_string[i])+1));
                assert(data->trading_name);
                strcpy(data->trading_name,array_string[i]);
                break;
            case 6:
                data->indus_code = (char *)malloc(sizeof(char)*(strlen(array_string[i])+1));
                assert(data->indus_code);
                strcpy(data->indus_code,array_string[i]);
                break;
            case 7:
                data->indus_desc = (char *)malloc(sizeof(char)*(strlen(array_string[i])+1));
                assert(data->indus_desc);
                strcpy(data->indus_desc,array_string[i]);
                break;
            case 8:
                data->x_cor = (char *)malloc(sizeof(char)*(strlen(array_string[i])+1));
                assert(data->x_cor);
                strcpy(data->x_cor,array_string[i]);
                break;
            case 9:
                data->y_cor = (char *)malloc(sizeof(char)*(strlen(array_string[i])+1));
                assert(data->y_cor);
                strcpy(data->y_cor,array_string[i]);
                break;
            case 10:
                data->coordinate = (char *)malloc(sizeof(char)*(strlen(array_string[i])+1));
                assert(data->coordinate);
                strcpy(data->coordinate,array_string[i]);
                break;
        }
    }
    


    for (int i = 0; i< DATA_AMOUNT;i++){
        free(array_string[i]);
    }
    free(array_string);

    return data;
}


list_t* create_linklist(FILE *fp){
    char *line = NULL;
    data_t *data = NULL;
    size_t lineBufferLength = 0;
    list_t *linked_list;
    linked_list = make_empty_list();
    line = (char *)malloc(sizeof(char)*512);
    assert(line);
    while(getline(&line, &lineBufferLength,fp)!= EOF){
        data = split_line(line);
        linked_list = insert_at_foot(linked_list, data);
    }
	free(line);
    return linked_list;
}




list_t* make_empty_list(void) {
	list_t *list = NULL;
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}

list_t* insert_at_foot(list_t *list, data_t *data) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(list!=NULL && new!=NULL);
	new->data = data;
	new->next = NULL;
	if (list->foot==NULL) {
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}


