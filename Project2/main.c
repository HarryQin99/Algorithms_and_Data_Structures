/* * * * * * *
 * Assignment 2: created for COMP20003 Algorithms and Data structures
 * by Yongfeng QIN yongfengq@student.unimelb.edu.au
 *
 * Stage1...
 *
 * This program is to store data provided into a 2-D tree as a dictionary,
 * and search through the whole tree to find the nearset location of the
 * location provided
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "link_2.h"
#include "readfile.h"
#include "tree.h"
#include "search.h"
#include "write.h"


// ----------------- Constant Definitions -----------------

#define FIRST 1
#define SECOND 2
#define DATA_AMOUNT 11

// ----------------- Main Function -----------------------

int main(int argc, char** argv){
    FILE * fp = NULL;
    FILE * fp_output = NULL;
    char *filename_input = NULL;
    char *filename_output = NULL;
    list_key_t *linked_list_key;
    char **array_header = NULL;

    /* get the input file and ouput file from the first and second
    position in argv, and open them */
    filename_input = argv[FIRST];
    filename_output = argv[SECOND];
    fp = fopen(filename_input,"r");
    fp_output = fopen(filename_output,"w");
    assert(fp);
    assert(fp_output);

    // Use the function in "readfile.c" to figure the header of the csv
    // file provided and find out all the key proviede, store them in a linked_list
    array_header = get_all_header(fp);
    linked_list_key = find_all_key();

    // Create the tree stored all the data provided,
    // used the funtion in "tree.c"
    tree_t *bst;
    bst = create_tree(fp);

    // Create an linked_list to store all the match data for the key provided,
    // use the function in "search.c" to search the match data
    list_search_t *linked_list_match;
    linked_list_match = search_tree(bst, linked_list_key);

    // Traverse the linked_list of match data and print the number of comparesion
    // to stdout
    node_search_t *current1;
    current1 = linked_list_match->head;
    while(current1!=NULL){
        
        printf("%s %s --> %d\n",current1->x_cor, current1->y_cor, current1->compare);
        current1 = current1->next;
    }

    // Write the match data into the output file, used the function in "write.c"
    write_output(array_header,linked_list_match,fp_output);

    // Finally, close the input file and output file
    fclose(fp);
    fclose(fp_output);
    // Free all the memory allocated at the end
    free_list_key(linked_list_key);
    free_string_array(array_header,DATA_AMOUNT);
    free_list_search(linked_list_match);
    free_tree(bst);
}