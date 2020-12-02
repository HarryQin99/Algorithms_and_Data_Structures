#ifndef WRITE_H   /* Include guard */
#define WRITE_H


void write_output(char **array_header,char **array_key,list_t *linked_list_search,FILE *fp,int amount);
void write_to_file(FILE *fp, data_t *data,char **array_header);
void write_notfound(int *array_int, char **array_key,FILE *fp, int amount);

#endif