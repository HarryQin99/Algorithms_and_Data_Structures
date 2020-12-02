/* * * * * * *
 * Readfile module: created for COMP20003 Algorithms and Data structures
 * by Yongfeng QIN yongfengq@student.unimelb.edu.au
 * 
 * All functions bellow are used for reading the header of the csv file and
 * all the search key 
 * 
 */

#ifndef READFILE_H
#define READFILE_H

#include "link_2.h"

// Struct for the node storing key
typedef struct node_key node_key_t;
struct node_key{
    node_key_t* next;
    coordinate_t *cord;
    char* x_cor;
    char* y_cor;
};

// Struct for the linked_list storing all keys provided
typedef struct list_key list_key_t;
struct list_key{
    node_key_t* head;
    node_key_t* foot;
};

// Struct for the node storing key (stage2)
typedef struct node_key_stage2 node_key_stage2_t;
struct node_key_stage2{
    node_key_stage2_t* next;
    double distance;
    coordinate_t *cord;
    char* x_cor;
    char* y_cor;
    char* distance_s;
};

// Struct for the linked_list storing all keys provided (stage2)
typedef struct list_key_stage2 list_key_stage2_t;
struct list_key_stage2{
    node_key_stage2_t* head;
    node_key_stage2_t* foot;
};

// ----------------- Function Implementations(stage1)-----------------

// Create a empty linked_list for storing key
list_key_t* make_empty_list_key(void);

/* Function used to find all the keys provided and store them into an 
arrya of string */
list_key_t *find_all_key();

/* Function used to read the first line of the input file and 
get all the header name */
char **get_all_header(FILE *fp);

// Insert the key into the end of the linked_list
list_key_t* insert_at_foot_key(list_key_t *list, char *x, char *y);

// Function used to free the array of string, based on its size
void free_string_array(char **array_string,int size);

// Free the linked_list, storing all the keys
void free_list_key(list_key_t *list);


// ----------------- Function Implementations(stage1)-----------------


// Create a empty linked_list for storing key(stage2)
list_key_stage2_t* make_empty_list_stage2(void);

/* Function used to find all the keys provided and store them into an 
arrya of string */
list_key_stage2_t *find_all_key_stage2();

// Insert the key into the end of the linked_list
list_key_stage2_t* insert_at_foot_key_stage2(list_key_stage2_t *list, char* x, 
char* y, char* distance);

// Free the linked_list, storing all the keys (stage2)
void free_list_key_stage2(list_key_stage2_t *list);

#endif