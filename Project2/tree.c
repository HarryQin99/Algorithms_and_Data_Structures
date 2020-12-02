/* * * * * * *
 * Tree module: created for COMP20003 Algorithms and Data structures
 * by Yongfeng QIN yongfengq@student.unimelb.edu.au
 * 
 * 
 * 
 * All the functions bellows are used to create the 2-D tree to store all the
 * data in the csv file
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "tree.h"
#include "link_2.h"

// ----------------- Constant Definitions -----------------

#define SITUATION_0 0
#define SITUATION_1 1
#define SITUATION_2 2
#define COMPARE_X 0
#define COMPARE_Y 1


/* Determine the new data should go to left child or right child of current tree
node */
int determine_greater(tree_t *parent, data_t *data, int compared_cord){
    if (compared_cord == COMPARE_X){
        if (data->cord->x < parent->cord->x){
            return SITUATION_1;
        }
        else{
            return SITUATION_0;
        }
    }
    else {
        if (data->cord->y < parent->cord->y){
            return SITUATION_1;
        }
        else{
            return SITUATION_0;
        }
    }
}

// Create the Tree for the data given in the csv file
tree_t *bstInsert(tree_t *parent, data_t *data, int *count){

    int compare_cor = COMPARE_Y;
    tree_t *parentInner = parent;
    tree_t **insertLocation = &parent;

    // Using a while loop to figure out where to store the current data
	while(*insertLocation){

        if((*insertLocation)->cord->x == data->cord->x && 
        (*insertLocation)->cord->y == data ->cord->y){
			break;
		} 

        // Determine left child or right child to continue
        if(determine_greater((*insertLocation), data, 
        (*insertLocation)->compare_cor)){
            parentInner = *insertLocation;
            compare_cor = (*insertLocation)->compare_cor;
			insertLocation = &((*insertLocation)->left);
		} else {
            parentInner = *insertLocation;
            compare_cor = (*insertLocation)->compare_cor;
			insertLocation = &((*insertLocation)->right);
		}
	}
    
    /* If (*inserLocation) is NULL, which means the location of the current data
    is new to the tree, create a new node to store it */
    if ((*insertLocation) == NULL){
        (*count)++;
        *insertLocation = (tree_t *) malloc(sizeof(tree_t));
	    assert(*insertLocation);
        (*insertLocation)->cord = (coordinate_t *)malloc(sizeof(coordinate_t));   
        assert((*insertLocation)->cord);
        (*insertLocation)->cord->x = data->cord->x;
        (*insertLocation)->cord->y = data->cord->y;
        if ((compare_cor) == COMPARE_X){
            (*insertLocation)->compare_cor = COMPARE_Y;
        }
        else {
            (*insertLocation)->compare_cor = COMPARE_X;
        }
        (*insertLocation)->linked_list = make_empty_list();
        (*insertLocation)->linked_list = 
        insert_at_foot((*insertLocation)->linked_list, data);
	    (*insertLocation)->left = NULL;
	    (*insertLocation)->right = NULL;
	    (*insertLocation)->parent = parentInner;
    }

    /* If (*inserLocation) is NULL, which means the tree node which represents
    the location of the data has exist, store the data into the linked_lis of
    the tree node directly */
    else {
        (*insertLocation)->linked_list = 
        insert_at_foot((*insertLocation)->linked_list, data);
    }
	return parent;
}

// The main funtion to create a two-dimention tree based on the data provided
tree_t *create_tree(FILE *fp){
    char *line = NULL;
    line = (char *)malloc(sizeof(char)*512);
    assert(line);
    data_t *data = NULL;
    tree_t *bst = NULL;
    int count_tree = 0;

    // Using a while loop to make sure store all the data in the csv file
    while(fgets(line, 512,fp)!= NULL){
        data = split_line(line);

        // Insert the data into the tree
        bst = bstInsert(bst, data, &count_tree);
    }
    //printf("%d",count_tree);
    free(line);
    return bst;
}

// Function used to do the traverse of the tree, (used for testing only)
void tree_traverse(tree_t *t, int *count){
    if (t){
        (*count)++;
        tree_traverse(t->left,count);
        tree_traverse(t->right,count);
    }
}

// Free the whole tree
void free_tree(tree_t *t){
    if (t!=NULL){
        free_tree(t->left);
        free_tree(t->right);
        free(t->cord);
        free_list(t->linked_list);
        free(t);
    }
}

// Free the struct data
void free_data(data_t *data){
    free(data->trading_name);
    free(data->base_property_id);
    free(data->block_id);
    free(data->property_id);
    free(data->census_year);
    free(data->club_area);
    free(data->cord);
    free(data->coordinate);
    free(data->indus_code);
    free(data->indus_desc);
    free(data);
}