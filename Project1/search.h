#ifndef SEARCH_H   /* Include guard */
#define SEARCH_H


list_t* search_from_file(list_t *linked_list,char **array_key,int amount);

list_t* search_dictionary(list_t *linked_list,list_t *linked_list_search,char *line);

void make_key_valid(char **line_add);

list_t* insert_node(list_t *list, data_t *data);

#endif