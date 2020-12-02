#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "link.h"
#include "search.h"
#include "write.h"
#include "free.h"
#include "readfile.h"


#define FIRST 1
#define SECOND 2
#define DOUBLE 2
#define DATA_AMOUNT 11
#define COMMA ','
 



int main(int argc, char** argv){

    FILE * fp = NULL;
    FILE * fp_output = NULL;
    char *filename_input = NULL;
    char *filename_output = NULL;

    list_t *linked_list;
    list_t *linked_list_search;
    
    
    filename_input = argv[FIRST];
    filename_output = argv[SECOND];
    fp = fopen(filename_input,"r");
    fp_output = fopen(filename_output,"w");

    char **array_header = NULL;
    array_header = get_all_header(fp);
    linked_list = create_linklist(fp);

    
    int amount = 0;
    char **array_key = find_all_key(&amount);
    //printf("%d",amount);
    //for (int i = 0; i<amount;i++){
    //    printf("%s",array_key[i]);
    //}


    linked_list_search = search_from_file(linked_list,array_key,amount);
    /*node_t *current;
    current = linked_list_search->head;
    while(current->next!=NULL){
        printf("%s\n",current->data->trading_name);
        current = current->next;
    }
    printf("%s\n",current->data->trading_name);*/

    write_output(array_header,array_key,linked_list_search,fp_output,amount);

    fclose(fp);
    fclose(fp_output);
    
    //free_list(linked_list);
    //free_list(linked_list_search);
    //free_string_array(array_key,amount);
    //free_string_array(array_header,DATA_AMOUNT);

    return 0;
}
