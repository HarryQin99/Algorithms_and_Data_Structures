/* * * * * * *
 * Search module: created for COMP20003 Algorithms and Data structures
 * by Yongfeng QIN yongfengq@student.unimelb.edu.au
 * 
 * 
 * 
 * All the functions bellows are used to do the search part for stage 1 and 
 * stage2. (nearest search and radius search)
 * 
 */

#ifndef SEARCH_H
#define SEARCH_H

#include "link_2.h"
#include "tree.h"
#include "readfile.h"

// Struct for the node storing search result
typedef struct node_search node_search_t;
struct node_search{
    char *x_cor;
    char *y_cor;
    list_t *linked_list;
    node_search_t *next;
    char *distance;
    int compare;
};

// Struct of the linked_list to store search result
typedef struct list_search list_search_t;
struct list_search{
    node_search_t* head;
    node_search_t* foot;
};

// ----------------- Function Implementations(stage1)-----------------

/* Calculate the distance between two coordinates, (here is returing the square
of the distance) */
double calculate_distance(coordinate_t *cord1, coordinate_t *cord2);

/* Compare the coordinate of the tree node and the key, determine
which child(left or right or both left and right) to search next
*/
int check_search(tree_t *bst, coordinate_t *cord, double *distance);

// Create an empty linked_list to store all the match data
list_search_t* make_empty_list_search(void);

// Find the nearest coordinate and its tree node of a particular key
void search_nearest(tree_t *bst, coordinate_t *cord, double *distance, 
tree_t **node_tree, int *compare);

// Insert a new node(data) into the linked_list
list_t* insert_node(list_t *list, data_t *data);

// Create the linked_list to copy the linked_list of the neareat tree node
list_t* create_match_list(list_t *linked_list, tree_t *tree_node);

/* Insert the search retult of a particulat key into the linked_list which is
storing all the search result */
list_search_t *inseart_search(list_search_t *linked_list_match, 
list_t *linked_list, node_key_t *current, int *compare);

// Search nearest data for all the key provided
list_search_t *search_tree(tree_t *bst, list_key_t *linked_list_key);

// Free the linked_list, which store all the search result
void free_list_search(list_search_t *list);



// ----------------- Function Implementations(stage2)-----------------

// Create the linked_list to store all the data in the radius
list_t *create_match_linked_list(tree_t *bst, node_key_stage2_t *key, 
int *compare);

/* Compare the coordinate of the tree node and the key, determine
which child(left or right or both left and right) to search next(stage2)
*/
int check_search_stage2(tree_t *bst, coordinate_t *cord, double *distance);

/* Insert the match data into the linked_list, stored all the match data for a 
particular key */
list_t* insert_match_stage2(list_t *linked_list, tree_t *tree_node);

// Do the radius search and store all the match data into a linked_list
list_t *search_radius(list_t *linked_list,tree_t *bst, node_key_stage2_t *key, 
int *compare);

/* Insert the search retult of a particulat key into the linked_list which is
storing all the search result */
list_search_t *inseart_search_stage2(list_search_t *linked_list_match, 
list_t *linked_list, node_key_stage2_t *current, int *compare);

// The main funciton to control do the radius search to all the key provided
list_search_t *search_tree_stage2(tree_t *bst, 
list_key_stage2_t *linked_list_key);


#endif
