#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "link.h"
#include "free.h"



list_t* insert_node(list_t *list, data_t *data) {
    node_t *new;
	new = (node_t*)malloc(sizeof(*new));
    data_t *data_new;
    data_new = (data_t *)malloc(sizeof(data_t));
	assert(list!=NULL && new!=NULL);
    data_new->census_year = (char *)malloc(sizeof(char)*(strlen(data->census_year)+1));
    assert(data_new->census_year);
    strcpy(data_new->census_year,data->census_year);
    //strcpy(data.census_year,array_string[ZERO]);

    data_new->block_id = (char *)malloc(sizeof(char)*(strlen(data->block_id)+1));
    assert(data_new->block_id);
    strcpy(data_new->block_id,data->block_id);
    //strcpy(data.block_id,array_string[ONE]);

    data_new->property_id = (char *)malloc(sizeof(char)*(strlen(data->property_id)+1));
    assert(data_new->property_id);
    strcpy(data_new->property_id,data->property_id);
    //strcpy(data.property_id,array_string[TWO]);

    data_new->base_property_id = (char *)malloc(sizeof(char)*(strlen(data->base_property_id)+1));
    assert(data_new->base_property_id);
    strcpy(data_new->base_property_id,data->base_property_id);
    //strcpy(data.base_property_id,array_string[THREE]);

    data_new->club_area = (char *)malloc(sizeof(char)*(strlen(data->club_area)+1));
    assert(data->club_area);
    strcpy(data_new->club_area,data->club_area);
    //strcpy(data.club_area,array_string[FOUR]);

    data_new->trading_name = (char *)malloc(sizeof(char)*(strlen(data->trading_name)+1));
    assert(data->trading_name);
    strcpy(data_new->trading_name,data->trading_name);
    //strcpy(data.trading_name,array_string[FIVE]);

    data_new->indus_code = (char *)malloc(sizeof(char)*(strlen(data->indus_code)+1));
    assert(data->indus_code);
    strcpy(data_new->indus_code,data->indus_code);
    //strcpy(data.indus_code,array_string[SIX]);

    data_new->indus_desc = (char *)malloc(sizeof(char)*(strlen(data->indus_desc)+1));
    assert(data->indus_desc);
    strcpy(data_new->indus_desc,data->indus_desc);
    //strcpy(data.indus_desc,array_string[SEVEN]);

    data_new->x_cor = (char *)malloc(sizeof(char)*(strlen(data->x_cor)+1));
    assert(data->x_cor);
    strcpy(data_new->x_cor,data->x_cor);
    //strcpy(data.x_cor,array_string[EIGHT]);

    data_new->y_cor = (char *)malloc(sizeof(char)*(strlen(data->y_cor)+1));
    assert(data->y_cor);
    strcpy(data_new->y_cor,data->y_cor);
    //strcpy(data.y_cor,array_string[NIGHT]);

    data_new->coordinate = (char *)malloc(sizeof(char)*(strlen(data->coordinate)+1));
    assert(data->coordinate);
    strcpy(data_new->coordinate,data->coordinate);
    //strcpy(data.coordinate,array_string[TEN]);
    new->data = data_new;
	new->next = NULL;
	if (list->foot==NULL) {
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}

list_t* search_dictionary(list_t *linked_list,list_t *linked_list_search, char *line){
    node_t *current;
    current = linked_list->head;
    while(current->next!=NULL){
        if (strcmp(current->data->trading_name,line) == 0){
            linked_list_search = insert_node(linked_list_search,current->data);
        }
        current = current->next;
    }
    if (strcmp(current->data->trading_name,line) == 0){
            linked_list_search = insert_node(linked_list_search,current->data);
            //break;
    }
    return linked_list_search;
}


void make_key_valid(char **line_add){
    //printf("%d",len);
    if ((*line_add)[strlen(*line_add)-1] == '\n'){
       (*line_add)[strlen(*line_add)-1] = '\0';
    }
    //printf("%lu",strlen(*line_add));
}


list_t* search_from_file(list_t *linked_list,char **array_key,int amount){
    char line[128];
    list_t *linked_list_out;
    linked_list_out = make_empty_list();
    //free(linked_list_out);
    for (int i = 0; i<amount; i++){
        strcpy(line,array_key[i]);
        //printf("%s\n",line);
        linked_list_out = search_dictionary(linked_list, linked_list_out, line);
    }
    //free_list(linked_list_out);
    return linked_list_out;
}






