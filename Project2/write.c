/* * * * * * *
 * Write module: created for COMP20003 Algorithms and Data structures
 * by Yongfeng QIN yongfengq@student.unimelb.edu.au
 * 
 * All function bellow is used for writing the data in specific format
 * into the output file
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "link_2.h"
#include "search.h"


// Write the search result into the outfile(stage1)
void 
write_output(char **array_header,list_search_t *linked_list_search,
FILE *fp){
    
    // Use two while to make sure write all the match into the outfile
    node_search_t *current1;
    current1 = linked_list_search->head;
    node_t *current2;
    while(current1!=NULL){
        current2 = current1->linked_list->head;
        while(current2 != NULL){
            fprintf(fp,"%s %s --> %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || \n",
            current1->x_cor, current1->y_cor,array_header[0],
            current2->data->census_year,array_header[1],
            current2->data->block_id,array_header[2],
            current2->data->property_id,array_header[3],
            current2->data->base_property_id,array_header[4],
            current2->data->club_area, array_header[5],
            current2->data->trading_name,array_header[6],
            current2->data->indus_code,array_header[7],
            current2->data->indus_desc,array_header[8],
            current2->data->x_cor,array_header[9],
            current2->data->y_cor,array_header[10],
            current2->data->coordinate);
            current2 = current2->next;
        }
        fprintf(fp,"\n");
        current1 = current1->next;
    }
}

// Write the search result into the outfiel(stage2)
void 
write_output_stage2(char **array_header,list_search_t *linked_list_search,
FILE *fp){

    // Use while loop to make sure write all the result
    node_search_t *current1;
    current1 = linked_list_search->head;
    node_t *current2;
    while(current1!=NULL){
        current2 = current1->linked_list->head;

        /* If the linked_list's head is NULL, which means the program can not
        find any match data in that radius */
        if (current2 == NULL){
            fprintf(fp,"%s %s %s --> NOFOUND",current1->x_cor, 
            current1->y_cor,current1->distance);
        }

        // Write all the match data
        while(current2 != NULL){
            fprintf(fp,"%s %s %s--> %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %s || %s: %lf || %s: %lf || %s: %s || \n",
            current1->x_cor, current1->y_cor,current1->distance,
            array_header[0],current2->data->census_year,array_header[1],
            current2->data->block_id,array_header[2],
            current2->data->property_id,array_header[3],
            current2->data->base_property_id,array_header[4],
            current2->data->club_area, array_header[5],
            current2->data->trading_name,array_header[6],
            current2->data->indus_code,array_header[7],
            current2->data->indus_desc,array_header[8],
            current2->data->cord->x,array_header[9],
            current2->data->cord->y,array_header[10],
            current2->data->coordinate);
            current2 = current2->next;
        }
        fprintf(fp,"\n");
        current1 = current1->next;
    }
   
}

