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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "link_2.h"
#include "tree.h"
#include "readfile.h"
#include "search.h"

// ----------------- Constant Definitions -----------------

#define SITUATION_0 0
#define SITUATION_1 1
#define SITUATION_2 2
#define COMPARE_X 0
#define COMPARE_Y 1
#define NO_USE "NO_USE"


/* Calculate the distance between two coordinates, (here is returing the square
of the distance) */
double calculate_distance(coordinate_t *cord1, coordinate_t *cord2){
    double distance;
    distance = (cord1->x-cord2->x)*(cord1->x-cord2->x)+
    (cord1->y-cord2->y)*(cord1->y-cord2->y);
    return distance;
}

/* Compare the coordinate of the tree node and the key, determine
which child(left or right or both left and right) to search next
*/
int check_search(tree_t *bst, coordinate_t *cord, double *distance){
    int output;

    // Comapre the value of x coordinate
    if (bst->compare_cor == COMPARE_X){
        if (fabs(bst->cord->x-cord->x) <= sqrt(*distance)){
            output = SITUATION_0;
        }
        else {
            if (bst->cord->x > cord->x){
                output = SITUATION_1;
            }
            else{
                output = SITUATION_2;
            }
        }
    }

    // Compare the value of y coordinate
    if (bst->compare_cor == COMPARE_Y){
        if (fabs(bst->cord->y-cord->y) <= sqrt(*distance)){
            output = SITUATION_0;
        }
        else {
            if (bst->cord->y > cord->y) {
                output = SITUATION_1;
            }
            else{
                output = SITUATION_2;
            }
        }
    }

    return output;
}

// Create an empty linked_list to store all the match data
list_search_t* make_empty_list_search(void) {
	list_search_t* list = NULL;
	list = (list_search_t*)malloc(sizeof(list_search_t));
	assert(list!=NULL);
	list->head = list->foot = NULL;
	return list;
}

// Find the nearest coordinate and its tree node of a particular key
void search_nearest(tree_t *bst, coordinate_t *cord, double *distance, 
tree_t **node_tree, int *compare){
    
    /* Start comparing the current nearest distance, with the distance of the
    key and the coordinate of the current tree node*/
    if (bst!=NULL){
        (*compare)++;

        /* If the distance is less than the current nearest distance, update the 
        nearest distance */
        if ((calculate_distance(cord, bst->cord) < *distance)) {       
            *distance = (calculate_distance(cord, bst->cord));
            (*node_tree) = bst;
        }
        
        // Decide search left or right or both by using function "check_search"
        if (check_search(bst, cord, distance) == SITUATION_0){
            search_nearest(bst->left, cord, distance, node_tree,compare);
            search_nearest(bst->right,cord, distance, node_tree, compare);         
        }
        else if (check_search(bst, cord, distance) == SITUATION_1){
            search_nearest(bst->left,cord, distance, node_tree,compare);
        }
        else {
            search_nearest(bst->right, cord, distance, node_tree,compare);
        }       
    }
}

// Insert a new node(data) into the linked_list
list_t* insert_node(list_t *list, data_t *data) {
    node_t *new;
	new = (node_t*)malloc(sizeof(*new));
    assert(new!=NULL);
    data_t *data_new;
    data_new = (data_t *)malloc(sizeof(data_t));
    assert(data_new);
    data_new->cord = (coordinate_t *)malloc(sizeof(coordinate_t));
    assert(data_new->cord);

    // Allocated just enought size of the string in the new_data structure
    // and copy use strcpy()
    data_new->census_year = 
    (char *)malloc(sizeof(char)*(strlen(data->census_year)+1));
    assert(data_new->census_year);
    strcpy(data_new->census_year,data->census_year);

    data_new->block_id = 
    (char *)malloc(sizeof(char)*(strlen(data->block_id)+1));
    assert(data_new->block_id);
    strcpy(data_new->block_id,data->block_id);

    data_new->property_id = 
    (char *)malloc(sizeof(char)*(strlen(data->property_id)+1));
    assert(data_new->property_id);
    strcpy(data_new->property_id,data->property_id);

    data_new->base_property_id = 
    (char *)malloc(sizeof(char)*(strlen(data->base_property_id)+1));
    assert(data_new->base_property_id);
    strcpy(data_new->base_property_id,data->base_property_id);

    data_new->club_area = 
    (char *)malloc(sizeof(char)*(strlen(data->club_area)+1));
    assert(data_new->club_area);
    strcpy(data_new->club_area,data->club_area);

    data_new->trading_name = 
    (char *)malloc(sizeof(char)*(strlen(data->trading_name)+1));
    assert(data_new->trading_name);
    strcpy(data_new->trading_name,data->trading_name);

    data_new->indus_code = 
    (char *)malloc(sizeof(char)*(strlen(data->indus_code)+1));
    assert(data_new->indus_code);
    strcpy(data_new->indus_code,data->indus_code);

    data_new->indus_desc = 
    (char *)malloc(sizeof(char)*(strlen(data->indus_desc)+1));
    assert(data_new->indus_desc);
    strcpy(data_new->indus_desc,data->indus_desc);


    data_new->x_cor = (char *)malloc(sizeof(char)*(strlen(data->x_cor)+1));
    assert(data_new->x_cor);
    strcpy(data_new->x_cor,data->x_cor);

    data_new->y_cor = (char *)malloc(sizeof(char)*(strlen(data->y_cor)+1));
    assert(data_new->y_cor);
    strcpy(data_new->y_cor,data->y_cor);
    //("%s %s\n",data_new->x_cor,data_new->y_cor);
    data_new->cord->x = data->cord->x;
    data_new->cord->y = data->cord->y; 

    
    data_new->coordinate = 
    (char *)malloc(sizeof(char)*(strlen(data->coordinate)+1));
    assert(data->coordinate);
    strcpy(data_new->coordinate,data->coordinate);
    
    // create the new node and add into the linked_list
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

// Create the linked_list to copy the linked_list of the neareat tree node
list_t* create_match_list(list_t *linked_list, tree_t *tree_node){
    linked_list = make_empty_list();
    node_t *current;
    current = tree_node->linked_list->head;
    while(current!=NULL){
        linked_list = insert_node(linked_list, current->data);
        current = current->next;
    }
    return linked_list;
}

/* Insert the search retult of a particulat key into the linked_list which is
storing all the search result */
list_search_t *inseart_search(list_search_t *linked_list_match, 
list_t *linked_list, node_key_t *current, int *compare){
    node_search_t *new;
    new = (node_search_t *)malloc(sizeof(node_search_t));
    assert(new);
    new->x_cor = (char *)malloc(sizeof(char)*(strlen(current->x_cor)+1));
    assert(new->x_cor);
    new->y_cor = (char *)malloc(sizeof(char)*(strlen(current->y_cor)+1));
    assert(new->y_cor);
    strcpy(new->x_cor,current->x_cor);
    strcpy(new->y_cor,current->y_cor);
    new->compare = (*compare);
    new->linked_list = linked_list;
    new->distance = (char *)malloc(sizeof(char)*(strlen(NO_USE)+1));
    assert(new->distance);
    strcpy(new->distance,NO_USE);
    new->next = NULL;
    if (linked_list_match->foot==NULL) {
		linked_list_match->head = linked_list_match->foot = new;
	} else {
		linked_list_match->foot->next = new;
		linked_list_match->foot = new;
	}
	return linked_list_match;
}

// Search nearest data for all the key provided
list_search_t *search_tree(tree_t *bst, list_key_t *linked_list_key){
    list_search_t *linked_list_match;
    linked_list_match = make_empty_list_search();
    list_t *linked_list = NULL;
    node_key_t *current;
    current = linked_list_key->head;
    double distance;
    tree_t *tree_node = bst;
    int compare;

    // Use while loop to keey doing the search for all the key
    while(current!=NULL){
        compare = 0;

        // Initialize the nearest distance is the distance between key and 
        // the root node
        distance = calculate_distance(current->cord, bst->cord);

        // Search through the whole tree and figure out which tree node has the 
        // nearest distance to the key
        search_nearest(bst, current->cord, &distance, &tree_node, &compare);
        
        // Copy the linked list of the nearest tree node
        linked_list = create_match_list(linked_list, tree_node);
        
        // Insert the search result into a linked_list, which storing all the 
        // search result
        linked_list_match = inseart_search(linked_list_match, 
        linked_list, current, &compare);
        
        current = current->next;
    }
    // return the search result
    return linked_list_match;
}

// Free the linked_list, which store all the search result
void free_list_search(list_search_t *list){
    node_search_t *current, *previous;
    assert(list!=NULL);
    current = list->head;
    while(current){
        previous = current;
        current = current->next;
        free(previous->x_cor);
        free(previous->y_cor);
        free(previous->distance);
        free_list(previous->linked_list);
        free(previous);
    }
    free(list);
}

// ----------------- Function Implementations(stage2)-----------------

// Create the linked_list to store all the data in the radius
list_t *create_match_linked_list(tree_t *bst, node_key_stage2_t *key, 
int *compare){
    list_t *linked_list = NULL;
    linked_list = make_empty_list();
    linked_list = search_radius(linked_list,bst, key, compare);
    return linked_list;
}

int check_search_stage2(tree_t *bst, coordinate_t *cord, double *distance){
    int output;

    // Comapre the value of x coordinate
    if (bst->compare_cor == COMPARE_X){
        if (fabs(bst->cord->x-cord->x) <= (*distance)){
            output = SITUATION_0;
        }
        else {
            if (bst->cord->x > cord->x){
                output = SITUATION_1;
            }
            else{
                output = SITUATION_2;
            }
        }
    }

    // Compare the value of y coordinate
    if (bst->compare_cor == COMPARE_Y){
        if (fabs(bst->cord->y-cord->y) <= (*distance)){
            output = SITUATION_0;
        }
        else {
            if (bst->cord->y > cord->y) {
                output = SITUATION_1;
            }
            else{
                output = SITUATION_2;
            }
        }
    }
    return output;
}


/* Insert the match data into the linked_list, stored all the match data for a 
particular key */
list_t* insert_match_stage2(list_t *linked_list, tree_t *tree_node){
    node_t *current;
    current = tree_node->linked_list->head;
    while(current!=NULL){
        linked_list = insert_node(linked_list, current->data);
        current = current->next;

    }
    return linked_list;
}


// Do the radius search and store all the match data into a linked_list
list_t *search_radius(list_t *linked_list,tree_t *bst, node_key_stage2_t *key, 
int *compare){
    if (bst!=NULL){
        (*compare)++;
        if ((calculate_distance(key->cord, bst->cord) < 
        key->distance*key->distance)) {
               linked_list = insert_match_stage2(linked_list, bst);
        }
        // Decide which side to continus the search next
        if (check_search_stage2(bst, key->cord, &(key->distance)) == 
        SITUATION_0){
            search_radius(linked_list,bst->left, key,compare);
            search_radius(linked_list,bst->right,key,compare);         
        }
        else if (check_search_stage2(bst, key->cord, &(key->distance)) == 
        SITUATION_1){
            search_radius(linked_list,bst->left,key,compare);
        }
        else {
            search_radius(linked_list,bst->right, key,compare);

        }
    }
    return linked_list;
}

/* Insert the search retult of a particulat key into the linked_list which is
storing all the search result */
list_search_t *inseart_search_stage2(list_search_t *linked_list_match, 
list_t *linked_list, node_key_stage2_t *current, int *compare){
    node_search_t *new;
    new = (node_search_t *)malloc(sizeof(node_search_t));
    assert(new);
    new->x_cor = (char *)malloc(sizeof(char)*(strlen(current->x_cor)+1));
    assert(new->x_cor);
    new->y_cor = (char *)malloc(sizeof(char)*(strlen(current->y_cor)+1));
    assert(new->y_cor);
    strcpy(new->x_cor,current->x_cor);
    strcpy(new->y_cor,current->y_cor);
    new->compare = (*compare);
    new->distance = (char *)malloc(sizeof(char)*(strlen(current->distance_s)+1));
    assert(new->distance);
    strcpy(new->distance,current->distance_s);
    new->linked_list = linked_list;
    new->next = NULL;
    if (linked_list_match->foot==NULL) {
		linked_list_match->head = linked_list_match->foot = new;
	} 
    else {
		linked_list_match->foot->next = new;
		linked_list_match->foot = new;
	}
	return linked_list_match;
}

// The main funciton to control do the radius search to all the key provided
list_search_t *search_tree_stage2(tree_t *bst, 
list_key_stage2_t *linked_list_key){
    list_search_t *linked_list_match;
    linked_list_match = make_empty_list_search();
    list_t *linked_list = NULL;
    node_key_stage2_t *current;
    current = linked_list_key->head;
    int compare;

    // Using while loop to keep searching, untill all the key have been searched
    while(current!=NULL){
        compare = 0;

        // Store all the match data into a linked_list
        linked_list = create_match_linked_list(bst, current, &compare);
      
        // Insert the search result into a linked_list, which storing all the 
        // search result
        linked_list_match = inseart_search_stage2(linked_list_match, linked_list, current, &compare);
        
        current = current->next;
    }
    return linked_list_match;
}

