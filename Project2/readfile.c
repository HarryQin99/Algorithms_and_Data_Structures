/* * * * * * *
 * Readfile module: created for COMP20003 Algorithms and Data structures
 * by Yongfeng QIN yongfengq@student.unimelb.edu.au
 * 
 * All functions bellow is used for reading the header of the csv file and
 * all the search key 
 * 
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "readfile.h"
#include "link_2.h"

// ----------------- Constant Definitions -----------------

#define DATA_AMOUNT 11
#define ONE 1
#define TWO 2
#define THREE 3
#define MAX_FIELD 128
#define COMMA ','
#define SWITCH_LINE '\n'
#define CARRIAGE_RETURN '\r'
#define QUOTE '"'


// Create a empty linked_list for storing key
list_key_t* make_empty_list_key(void) {
	list_key_t *list = NULL;
	list = (list_key_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}

/* Function used to find all the keys provided and store them into an 
arrya of string */
list_key_t *find_all_key(){
    list_key_t *linked_list_key;
    linked_list_key = make_empty_list_key();
    char *line = NULL;
    line = (char *)malloc(sizeof(char)*(MAX_FIELD+THREE));
    assert(line);
    char *location;
    int count = 0;
    //char *x;
    //char *y;

    // find all the key using while loop
    while (fgets(line,218,stdin) != NULL){
        count = 0;
        if (line[0] != '\n'){
            location = strtok (line," ");
            char *x = NULL ;
            char *y = NULL;
            while (strlen(line)>0 && location != NULL){
                if (location[strlen(location)-1] == '\n'){
                    location[strlen(location)-1] = '\0';
                }
                if (count == 0){
                    x = (char *)malloc(sizeof(char)*(strlen(location)+1));
                    assert(x);
                    strcpy(x,location);
                    //printf("%s",x);
                    count++;
                }
                else{
                    y = (char *)malloc(sizeof(char)*(strlen(location)+1));
                    assert(y);
                    strcpy(y,location);
                    //y = atof(location);
                    //printf("%s",y);
                    break;
                }
                location = strtok (NULL," ");           
            }

            // Once get the value of x and y, insert into the linked_list of key
            linked_list_key = insert_at_foot_key(linked_list_key, x, y);
        }

    }

    // Free and return at the end
    free(line);
    return linked_list_key;
}

/* Function used to read the first line of the input file and 
get all the header name */
char **get_all_header(FILE* fp){
    char *line = NULL;
    int position_array = 0;
    int position = 0;
    int quote = 0;
    size_t bufsize = 0;
    
    //get the first line of input file by getline()
    getline(&line,&bufsize,fp);

    // Create an array of string to store all the header
    char **array_header = (char **)malloc(sizeof(char*)*(DATA_AMOUNT));
    assert(array_header);

    // Split the whole header line into 11 field 
    char *header = (char*)malloc(sizeof(char)*MAX_FIELD);
    assert(header);
    for (int i = 0;i < strlen(line);i++){
        if (line[i] == QUOTE){
            quote++;
        } 
        // Once get a ',' , determine if it is end of a field
        if (line[i] == COMMA && quote%TWO == 0){   
            // If so, add the word in that field into array of header       
            header[position] = '\0';
            array_header[position_array] = 
            (char*)malloc(sizeof(char)*(strlen(header)+1));
            assert(array_header[position_array]);
            strcpy(array_header[position_array],header);
            position_array++;
            position = 0;       
        }
        // At the end of a line, add the word in that field into array of
        //header directly
        else if (line[i] == '\n' || i == strlen(line)-1){
            header[position] = '\0';
            array_header[position_array] = 
            (char*)malloc(sizeof(char)*(strlen(header)+1));
            assert(array_header[position_array]);
            strcpy(array_header[position_array],header);
        }
        else if (line[i] == '\r'){

        }
        else{
            header[position++] = line[i];
        }
    }
    // Free all the memory allocated and return the array of header
    free(header);
    free(line);
    return array_header;
}

// Insert the key into the end of the linked_list
list_key_t* insert_at_foot_key(list_key_t *list, char *x, char *y){
	node_key_t *new;

    // Malloc mamory for the new node in the linked_list for key
	new = (node_key_t*)malloc(sizeof(*new));
    assert(new);
    coordinate_t *cord = NULL;
    cord = (coordinate_t *)malloc(sizeof(coordinate_t));
    assert(cord);
    cord->x = atof(x);
    cord->y = atof(y);
    new->x_cor = x;
    new->y_cor = y;
	new->cord = cord;
	new->next = NULL;

    // Insert into the linked_list
	if (list->foot==NULL) {
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}

// Function used to free the array of string, based on its size
void
free_string_array(char **array_string,int size){
    for (int i = 0; i<size; i++){
        free(array_string[i]);
    }
    free(array_string);
}

// Free the linked_list, storing all the keys
void free_list_key(list_key_t *list){
    node_key_t *current, *previous;
    assert(list!=NULL);
    current = list->head;
    while(current){
        previous = current;
        current = current->next;
        free(previous->cord);
        free(previous->x_cor);
        free(previous->y_cor);
        free(previous);
    }
    free(list);
}

// Create a empty linked_list for storing key(stage2)
list_key_stage2_t* make_empty_list_stage2(void) {
	list_key_stage2_t *list = NULL;
	list = (list_key_stage2_t*)malloc(sizeof(*list));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}

/* Function used to find all the keys provided and store them into an 
arrya of string */
list_key_stage2_t *find_all_key_stage2(){
    list_key_stage2_t *linked_list_key;
    linked_list_key = make_empty_list_stage2();
    char *line = NULL;
    line = (char *)malloc(sizeof(char)*(MAX_FIELD+THREE));
    assert(line);
    char *location;
    int count = 0;

    while (fgets(line,218,stdin) != NULL){
        count = 0;
        if (line[0] != '\n'){
            location = strtok (line," ");
            char *x = NULL;
            char *y = NULL;
            char *distance = NULL;
            // find all the keys, and the value of the x_cord and y_cord, radius
            while (strlen(line)>0 && location != NULL){
                if (location[strlen(location)-1] == '\n'){
                    location[strlen(location)-1] = '\0';
                }
                if (count == 0){
                    x = (char *)malloc(sizeof(char)*(strlen(location)+1));
                    assert(x);
                    strcpy(x,location);
                    count++;
                }
                else if (count == 1){
                    y = (char *)malloc(sizeof(char)*(strlen(location)+1));
                    assert(y);
                    strcpy(y,location);
                    count++;
                }
                else {
                    distance = (char *)malloc(sizeof(char)*(strlen(location)+1));
                    assert(distance);
                    strcpy(distance,location);
                    //distance = atof(location);
                }
                location = strtok (NULL," ");           
            }
            //printf("(%s %s %s)\n",x,y,distance);
            /* Once get the x_cord, y_cord, and the radius, inseart the node key to
            the linked_list */
            linked_list_key = insert_at_foot_key_stage2(linked_list_key, 
            x, y,distance);
        }

    }

    free(line);
    return linked_list_key;
}

// Insert the key into the end of the linked_list
list_key_stage2_t* insert_at_foot_key_stage2(list_key_stage2_t *list, 
char* x, char* y, char* distance){
	node_key_stage2_t *new;

    // Malloc memory for the new node to store key
	new = (node_key_stage2_t*)malloc(sizeof(*new));
    assert(new);
    coordinate_t *cord = NULL;
    cord = (coordinate_t *)malloc(sizeof(coordinate_t));
    assert(cord);
    cord->x = atof(x);
    cord->y = atof(y);
    new->distance = atof(distance);
    new->distance_s = distance;
    new->x_cor = x;
    new->y_cor = y;
	assert(list!=NULL && new!=NULL);
	new->cord = cord;
	new->next = NULL;

    // Insert into the linked_list
	if (list->foot==NULL) {
		list->head = list->foot = new;
	} else {
		list->foot->next = new;
		list->foot = new;
	}
	return list;
}

// Free the linked_list, storing all the keys (stage2)
void free_list_key_stage2(list_key_stage2_t *list){
    node_key_stage2_t *current, *previous;
    assert(list!=NULL);
    current = list->head;
    while(current){
        previous = current;
        current = current->next;
        free(previous->cord);
        free(previous->x_cor);
        free(previous->y_cor);
        free(previous->distance_s);
        free(previous);
    }
    free(list);
}