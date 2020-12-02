/* * * * * * *
 * Assignment 2: created for COMP20003 Algorithms and Data structures
 * by Yongfeng QIN yongfengq@student.unimelb.edu.au
 *
 * Stage2...
 *
 * This program is to store data provided into a 2-D tree as a dictionary,
 * and do the radius search through the whole tree to find the match data which
 * in the radius provided of the key location
 *
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



int main(int argc, char** argv){
    FILE * fp = NULL;
    FILE * fp_output = NULL;
    char *filename_input = NULL;
    char *filename_output = NULL;
    list_key_stage2_t *linked_list_key;
    char **array_header = NULL; 

    /* get the input file and ouput file from the first and second
    position in argv, and open them */
    filename_input = argv[FIRST];
    filename_output = argv[SECOND];
    fp = fopen(filename_input,"r");
    fp_output = fopen(filename_output,"w");
    assert(fp);
    assert(fp_output);

    /* Use the funciton in "readfile.c" to figure out the header of the 
    csv file provided and find out all the key provided, store them in a 
    linked_list */
    array_header = get_all_header(fp);
    linked_list_key = find_all_key_stage2();
    
    // Create the tree stored all the data provided,
    // used the funtion in "tree.c"
    tree_t *bst;
    bst = create_tree(fp);

    // Create an linked_list to store all the match data for the key provided,
    // use the function in "search.c" to search the match data
    list_search_t *linked_list_match;
    linked_list_match = search_tree_stage2(bst,linked_list_key);

    // Write the match data into the output file, used the function
    // in "write.c"
    write_output_stage2(array_header,linked_list_match,fp_output);
    node_search_t *current;
    current = linked_list_match->head;
    while (current){
        printf("%s %s %s --> %d\n", current->x_cor,current->y_cor,current->distance,current->compare);
        current = current->next;
    }
    
    // Finally, close the input file and output file
    fclose(fp);
    fclose(fp_output);
    // Free all the memory allocated at the end
    free_list_key_stage2(linked_list_key);
    free_string_array(array_header,DATA_AMOUNT);
    free_list_search(linked_list_match);
    free_tree(bst);
    
}