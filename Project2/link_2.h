/* * * * * * *
 * Link module: created for COMP20003 Algorithms and Data structures
 * by Yongfeng QIN yongfengq@student.unimelb.edu.au
 * 
 * 
 * All the functions bellow are used to read the data, and do the proper 
 * splic of that, inseart the data into the linked_list storing it.
 * 
 */

#ifndef LINK_H
#define LINK_H

// struct for the all the data
typedef struct coordinate coordinate_t;
struct coordinate{
    double x;
    double y;
};

typedef struct data data_t;
struct data{
    char* census_year;
    char* block_id;
    char* property_id;
    char* base_property_id;
    char* club_area;
    char* trading_name;
    char* indus_code;
    char* indus_desc;
    char* coordinate;
    char* x_cor;
    char* y_cor;
    coordinate_t *cord;
};

// struct for the node of linked_list
typedef struct node node_t;
struct node{
    node_t* next;
    data_t* data;
};

// struct for one linked_list
typedef struct list list_t;
struct list{
    node_t* head;
    node_t* foot;
};

/* Function used to solve the problem of double quote 
in some data*/
char *make_valid(char *string);

// Split one whole line to figure data for different field
data_t *split_line(char *line);

// Create an empyt linked_list
list_t* make_empty_list(void);

// Insert an new node into the linked_list
list_t* insert_at_foot(list_t *list, data_t *data);

// Free the linked_list, storing data in csv file
void free_list(list_t *list);

#endif