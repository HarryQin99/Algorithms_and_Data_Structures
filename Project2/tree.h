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


#ifndef TREE_H
#define TREE_H

#include "link_2.h"

// Struct for the tree node
typedef struct tree tree_t;
struct tree {
    tree_t *left;
    tree_t *right;
	tree_t *parent;
    int compare_cor;
    coordinate_t *cord;
    list_t *linked_list;
};

// ----------------- Function Implementations-----------------

/* Determine the new data should go to left child or right child of current tree
node */
int determine_greater(tree_t *parent, data_t *data, int compared_cord);

// Create the Tree for the data given in the csv file
tree_t *bstInsert(tree_t *parent, data_t *data, int *count);


// The main funtion to create a two-dimention tree based on the data provided
tree_t *create_tree(FILE *fp);

// Function used to do the traverse of the tree, (used for testing only)
void tree_traverse(tree_t *t, int *count);

// Free the whole tree
void free_tree(tree_t *t);

// Free the struct data
void free_data(data_t *data);


#endif