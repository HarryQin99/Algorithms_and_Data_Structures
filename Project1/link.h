#ifndef LINK_H   /* Include guard */
#define LINK_H


typedef struct data data_t;
struct data{
    char* census_year;
    char* block_id;
    char* property_id;
    char* base_property_id;
    char* club_area;
    char* trading_name;
    char* indus_code;
    char* indus_desc;
    char* x_cor;
    char* y_cor;
    char* coordinate;
};



typedef struct node node_t;
struct node{
    node_t* next;
    data_t* data;
};

typedef struct list list_t;
struct list{
    node_t* head;
    node_t* foot;
};

data_t *split_line(char *line);

char *make_valid(char *string);


list_t* create_linklist(FILE *fp);
list_t* make_empty_list(void);

list_t* insert_at_foot(list_t *list, data_t *data);

#endif