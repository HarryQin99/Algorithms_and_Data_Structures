#include <time.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <assert.h>

#include "ai.h"
#include "utils.h"
#include "hashtable.h"
#include "stack.h"


void copy_state(state_t* dst, state_t* src){

	//Copy field
	memcpy( dst->field, src->field, SIZE*SIZE*sizeof(int8_t) );

	dst->cursor = src->cursor;
	dst->selected = src->selected;
}

/**
 * Saves the path up to the node as the best solution found so far
*/
void save_solution( node_t* solution_node ){
	node_t* n = solution_node;
	while( n->parent != NULL ){
		copy_state( &(solution[n->depth]), &(n->state) );
		solution_moves[n->depth-1] = n->move;
		n = n->parent;
	}
	solution_size = solution_node->depth;
}


node_t* create_init_node( state_t* init_state ){
	node_t * new_n = (node_t *) malloc(sizeof(node_t));
	new_n->parent = NULL;
	new_n->depth = 0;
	copy_state(&(new_n->state), init_state);
	return new_n;
}

/**
 * Apply an action to node n and return a new node resulting from executing the action
*/
node_t* applyAction(node_t* n, position_s* selected_peg, move_t action ){

    // Create new generated node
    node_t* new_node = NULL;
	new_node = (node_t*)malloc(sizeof(node_t));

	// Assign the depth of the new node be 1 greater than the old node
	new_node->depth = (n->depth)+1;

	// point the new node's parent to the old node
	new_node->parent = n;

	// Record the action of generating this node
	new_node->move = action;

	// Update the state
	copy_state(&(new_node->state),&(n->state));

	// Assign the state cursor
	new_node->state.cursor.x = selected_peg->x;
	new_node->state.cursor.y = selected_peg->y;

    // Update the field in board
    execute_move_t( &(new_node->state), &(new_node->state.cursor), action );


	return new_node;

}



/**
 * Find a solution path as per algorithm description in the handout
 */

void find_solution( state_t* init_state  ){

	HashTable table;

	// Choose initial capacity of PRIME NUMBER
	// Specify the size of the keys and values you want to store once
	ht_setup( &table, sizeof(int8_t) * SIZE * SIZE, sizeof(int8_t) * SIZE * SIZE, 16769023);


	// Add the initial node
	node_t* n = create_init_node( init_state );

    // Calculate the initial remaining_peg
    int remaining_peg = num_pegs(&(n->state));

	// Initialize the global stack
	initialize_stack();

    // Create a linked list to hold all the explored node
	list_t* linked_list = NULL;
	linked_list = make_empty_list();


	// Push the initial node into the stack
	stack_push(n);

	while(!is_stack_empty()){

		// Pop a new node for exploring
		node_t* node = stack_top();
		stack_pop();

		// Put this explored node into the explored array help 
		// for freeing later
		linked_list = insert_at_foot(linked_list, node);
		expanded_nodes++;
        
		// If the current exploring node's peg amount is less that the current
		// peg amount, update the current solution
		if (num_pegs(&(node->state)) < remaining_peg){
			save_solution(node);
			remaining_peg = num_pegs(&(node->state));
		}
        
		// For each possible jump, figure out which one is a valid one
		for (int i = 0; i<SIZE; i++){
			for (int j = 0; j<SIZE; j++){
				for (int z = 0; z<4; z++){
					node_t* created_node;
					position_s new_position = {i,j};
                
					// Figure out if the new node is a valid
					if (can_apply(&(node->state), &new_position, z)){
						generated_nodes++;

						// If valid, created the new node
						created_node = applyAction(node, &new_position, z);

						// Check if the node is in the final state and win the 
						// game, if so, stop exploring and free all the momery
						// allocated and return 
                        if (won(&(created_node->state))){
							save_solution(created_node);
							remaining_peg = num_pegs(&(created_node->state));
							stack_push(created_node);
							free_linked_list(linked_list);
							free_stack();
							ht_destroy(&table);
							return;
						}

						// Chech if the new node's board is seen first time
						if(ht_contains(&table, &(created_node->state.field)) == HT_NOT_FOUND){
							ht_insert(&table, &(created_node->state.field), &(created_node->state.field));
							stack_push(created_node);
						}
						else{
							free(created_node);
						}
					}
				}
			}
		}

		// When the expanded_nodes has up to the budget value, need to 
		// free all the memory allocated and return
		if (expanded_nodes == budget){
			free_linked_list(linked_list);
			free_stack();
			ht_destroy(&table);
			return;
		}
	}

	// Finally, make free all the memory free
	free_stack();
	free_linked_list(linked_list);
	ht_destroy(&table);
	return;
}
