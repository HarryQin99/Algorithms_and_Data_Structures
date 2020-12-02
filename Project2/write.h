/* * * * * * *
 * Write module: created for COMP20003 Algorithms and Data structures
 * by Yongfeng QIN yongfengq@student.unimelb.edu.au
 * 
 * All function bellow is used for writing the data in specific format
 * into the output file
 */

#ifndef WRITE_H
#define WRITE_H

// Write the search result into the outfile(stage1)
void write_output(char **array_header,list_search_t *linked_list_search, 
FILE *fp);

// Write the search result into the outfiel(stage2)
void write_output_stage2(char **array_header,list_search_t *linked_list_search,
FILE *fp);
#endif
