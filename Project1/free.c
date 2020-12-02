#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "link.h"
#include "search.h"
#include "write.h"

void
free_list(list_t *list){
    node_t *current, *previous;
    assert(list!=NULL);
    current = list->head;
    while(current){
        previous = current;
        current = current->next;
        free(previous->data->trading_name);
        free(previous->data->base_property_id);
        free(previous->data->block_id);
        free(previous->data->property_id);
        free(previous->data->census_year);
        free(previous->data->club_area);
        free(previous->data->x_cor);
        free(previous->data->y_cor);
        free(previous->data->coordinate);
        free(previous->data->indus_code);
        free(previous->data->indus_desc);
        free(previous);
    }
    free(list);
}

void
free_string_array(char **array_string,int size){
    for (int i = 0; i<size; i++){
        free(array_string[i]);
    }
    free(array_string);
}

