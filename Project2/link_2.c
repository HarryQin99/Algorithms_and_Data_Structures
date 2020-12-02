/* * * * * * *
 * Link module: created for COMP20003 Algorithms and Data structures
 * by Yongfeng QIN yongfengq@student.unimelb.edu.au
 *
 *
 * All the functions bellow are used to read the data, and do the proper
 * splic of that, inseart the data into the linked_list storing it.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "link_2.h"


// ----------------- Constant Definitions -----------------

#define COMMA ','
#define QUOTE '"'
#define TWO 2
#define ZERO 0
#define MAX_FIELD 128
#define SWITCH_LINE '\n'


/* Function used to solve the problem of double quote
in some data*/
char *make_valid(char *string){
    int len = strlen(string);
    char prev_char = ' ';
    char *output;
    output = (char *)malloc(sizeof(char)*(strlen(string)+1));
    assert(output);
    int position = 0;

    /* Use a for loop to read the whole string, keep only one quote
    when there are double quote in the string*/
    for (int i = 0; i< len; i++){

        // determine if the quote is a part of double quota
        if (string[i] == QUOTE){
            if (i != ZERO && i != len-1 && prev_char != QUOTE){
                output[position++] = string[i];
                prev_char = string[i];
            }
            else{

            }
        }
        // for the char which is not quote
        else{
            output[position++] = string[i];
            prev_char = string[i];
        }
    }
    // Copy and free at the end
    output[position] = '\0';
    strcpy(string,output);
    free(output);
    return string;

}

// Split one whole line to figure data for different field
data_t *split_line(char *line){
    int quote = 0;
    data_t *data = (data_t *)malloc(sizeof(data_t));
    assert(data);
    data->cord = (coordinate_t *)malloc(sizeof(coordinate_t));
    assert(data->cord);
    int position = 0;
    int position_array = 0;
    char *string = (char *)malloc(sizeof(char)*(MAX_FIELD));
    assert(string);


    // Use for loop to read each char in the line one by one
    for (int i = 0;i < strlen(line);i++){

        if (line[i] == QUOTE){
            quote++;
        }

        // Split the line when there is a comma and the
        // amount of the quote before it is an even number
        if ((line[i] == COMMA && quote%TWO == 0)){
            string[position] = '\0';
            string = make_valid(string);

            /* Use Switch to decide the current string is
            the data for which field. */
            switch(position_array){
                case 0:
                    // For space efficient, only allocate just enough size
                    // for the string in 'data' structure
                    data->census_year =
                    (char *)malloc(sizeof(char)*(strlen(string)+1));
                    assert(data->census_year);
                    strcpy(data->census_year,string);
                    break;
                case 1:
                    data->block_id =
                    (char *)malloc(sizeof(char)*(strlen(string)+1));
                    assert(data->block_id);
                    strcpy(data->block_id,string);
                    break;
                case 2:
                    data->property_id =
                    (char *)malloc(sizeof(char)*(strlen(string)+1));
                    assert(data->property_id);
                    strcpy(data->property_id,string);
                    break;
                case 3:
                    data->base_property_id =
                    (char *)malloc(sizeof(char)*(strlen(string)+1));
                    assert(data->base_property_id);
                    strcpy(data->base_property_id,string);
                    break;
                case 4:
                    data->club_area =
                    (char *)malloc(sizeof(char)*(strlen(string)+1));
                    assert(data->club_area);
                    strcpy(data->club_area,string);
                    break;
                case 5:
                    data->trading_name =
                    (char *)malloc(sizeof(char)*(strlen(string)+1));
                    assert(data->trading_name);
                    strcpy(data->trading_name,string);
                    break;
                case 6:
                    data->indus_code =
                    (char *)malloc(sizeof(char)*(strlen(string)+1));
                    assert(data->indus_code);
                    strcpy(data->indus_code,string);
                    break;
                case 7:
                    data->indus_desc =
                    (char *)malloc(sizeof(char)*(strlen(string)+1));
                    assert(data->indus_desc);
                    strcpy(data->indus_desc,string);
                    break;
                case 8:
                    data->cord->x = atof(string);
                    data->x_cor =
                    (char *)malloc(sizeof(char)*(strlen(string)+1));
                    assert(data->x_cor);
                    strcpy(data->x_cor,string);
                    break;
                default:
                    data->cord->y = atof(string);
                    data->y_cor =
                    (char *)malloc(sizeof(char)*(strlen(string)+1));
                    assert(data->y_cor);
                    strcpy(data->y_cor,string);
                    break;
            }
            // Change for recording the string of next field
            position_array++;
            position = 0;
        }

        // At the end of the line, assign the value of 'coordinate' in data
        // structure as the current string
        else if (line[i] == '\n' || i == strlen(line)-1){
            if (line[i] == '\n'){
                string[position] = '\0';
            }
            else{
                string[position++] = line[i];
                string[position] = '\0';
            }
            string = make_valid(string);
            data->coordinate = (char *)malloc(sizeof(char)*(strlen(string)+1));
            assert(data->coordinate);
            strcpy(data->coordinate,string);
        }
        else if (line[i] == '\r'){

        }
        else{
            string[position++] = line[i];
        }
    }
    // Free the memory allocated, which would not
    // be used any more at the end
    free(string);
    return data;
}


// Create an empyt linked_list
list_t* make_empty_list(void) {
	list_t *list = NULL;
	list = (list_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}


// Insert an new node into the linked_list
list_t* insert_at_foot(list_t *list, data_t *data) {
	node_t *new;
	new = (node_t*)malloc(sizeof(*new));
	assert(new!=NULL);
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

// Free the linked_list, storing data in csv file
void free_list(list_t *list){
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
        free(previous->data->cord);
        free(previous->data->coordinate);
        free(previous->data->indus_code);
        free(previous->data->indus_desc);
        free(previous->data->x_cor);
        free(previous->data->y_cor);
        free(previous->data);
        free(previous);
    }
    free(list);
}
