#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "link.h"
#include "search.h"

void write_to_file(FILE *fp, data_t *data,char **array_header){

    fprintf(fp,"%s --> %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || \n",
    data->trading_name,array_header[0],data->census_year,array_header[1],data->block_id,array_header[2],data->property_id,
    array_header[3],data->base_property_id,array_header[4],data->club_area,
    array_header[6],data->indus_code,array_header[7],data->indus_desc,array_header[8],data->x_cor,
    array_header[9],data->y_cor,array_header[10],data->coordinate);

}

void write_notfound(int *array_int, char **array_key,FILE *fp, int amount){
    for (int i = 0; i<amount;i++){
        printf("%d",array_int[i]);
        if (array_int[i] == 0){
            fprintf(fp,"%s --> NOTFOUND\n",array_key[i]);
        }
    }
}

void write_output(char **array_header,char **array_key,list_t *linked_list_search,FILE *fp,int amount){
    int *array_int;
    //printf("%d",amount);
    array_int = (int *)malloc(sizeof(int)*amount);
    assert(array_int);
    for (int i = 0; i<amount; i++){
        array_int[i] = 0;
    }
    node_t *current;
    current = linked_list_search->head;
    while(current->next!=NULL){
        write_to_file(fp,current->data,array_header);
        current = current->next;
    }
    write_to_file(fp,current->data,array_header);
    for (int i = 0; i<amount; i++){
        current = linked_list_search->head;
        while(current->next!=NULL){
            if (strcmp(array_key[i],current->data->trading_name) == 0){
                array_int[i] = 1;
                break;
            }
            current = current->next;
        }
        if (strcmp(array_key[i],current->data->trading_name) == 0){
            array_int[i] = 1;
        }
    }
    write_notfound(array_int, array_key,fp,amount);
    free(array_int);
        
}

    


