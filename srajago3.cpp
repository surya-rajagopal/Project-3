#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <map>
#define NKEY -1


map<int,o_t*> hashmap;
map<int,o_t*>::iterator it;

typedef int key_t;

key_t maxKey, minKey;


typedef struct linearNode{
	key_t key;
	linearNode *left;
	linearNode *right;
	int height;
}o_t;


/*  Stack Operations -- (Referred from the Text Book)

/*
   structure for implementing the stack
 */

typedef struct stack {
	m_tree_t *tree;
	struct stack *next; 
} stack;


/*
   Creates an Empty Stack
*/
stack *createStack(void){
	stack *s = (stack*) malloc(sizeof(stack));
	s->next = NULL;
	return s;
}

/*
   returns 1 if Stack is empty, else 0
 */
int stackEmpty(stack *s){
	if(s->next == NULL){
		return 1;
	}	
	else{
		return 0;
	}
}

/*
   Pushes the object into the Stack
 */
void stackPush( m_tree_t *tree, stack *s){
	stack *tmp = (stack*) malloc(sizeof(stack));
	tmp->tree = tree;
	tmp->next = s->next;
	s->next = tmp;
}

/*
   returns the top element of the Stack and deletes the item from the Stack
*/
m_tree_t* stackPop(stack *s){
	stack *tmp; m_tree_t* node;
	tmp = s->next;
	s->next = tmp->next;
	node = tmp->tree;
	free(tmp);
	return node;
}

/*
   return the top element from the stack
*/
m_tree_t* stackTop(stack *s){
	if( s->next != NULL){
		return( s->next->tree );
	}
	else{
		NULL;
	}
}

void removeStack(stack *s)
{
	stack *tmp;
	do{
		tmp = s->next;
		free(s);
		s = tmp;
	}
	while ( tmp != NULL );
}


/*End of Stack operations*/




o_t* create_order(){
	o_t* tmp = (o_t*) malloc(sizeof(o_t));
	tmp->key = NKEY;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}

o_t* returnOrderNode(key_t a){
	o_t* tmp = (o_t*) malloc(sizeof(o_t));
	tmp->key = a;
	tmp->left = NULL;
	tmp->right = NULL;
	return tmp;
}


long p(long q){
	return( (1247*q +104729) % 300007 );
}

void insert_before(o_t *ord, key_t a, key_t b){
	stack *rotateStack = createStack();

        removeStack(rotateStack);
}

void insert_after(o_t *ord, key_t a, key_t b){
	stack *rotateStack = createStack();

        removeStack(rotateStack);
}

void insert_top(o_t *ord, key_t a){

	stack *rotateStack = createStack();

	if(ord == NULL){
		return;
	}
	o_t *tmp = ord;
	maxKey = a;
	o_t *insertElement = returnOrderNode(a);
	if(ord->left == NULL){
		//insertElement->key = a;
		ord->right = insertElement;
		hashmap[maxkey] = ord->right;
		return;
	}	
	else{
		while(tmp->right != NULL){
			tmp = tmp->right; 
		}

		 o_t *old_leaf;
		 old_leaf = create_order();
		 old_leaf->left = tmp->left; 
		 old_leaf->key = tmp->key;
		 old_leaf->right  = NULL;
		 
		 tmp->left = old_leaf;
		 tmp->right = insertElement;	
   		 hashmap[maxkey] = ord->right;

	}
}

void insert_bottom(o_t *ord, key_t a){
	if(ord == NULL){
		return;
	}
	o_t *tmp = ord;
	minKey = a;
	o_t *insertElement = returnOrderNode(a);
	if(ord->left == NULL){
		//insertElement->key = a;

		ord->left = insertElement;
		//hashmap[minkey] = ord->left;
		return;
	}	
	else{
		while(tmp->left != NULL){
			tmp = tmp->right; 
		}

		 o_t *old_leaf;
		 old_leaf = create_order();
		 old_leaf->left = tmp->left; 
		 old_leaf->key = tmp->key;
		 old_leaf->right  = NULL;
		 
		 tmp->left = insertElement;
		 tmp->right = old_leaf;	
		 //hashmap[minkey] = ord->left;
	}

}

void delete_o(o_t *ord, key_t a){
	stack *rotateStack = createStack();

        removeStack(rotateStack);
}

int is_before(o_t *ord, key_t a, key_t b){
	return 0;
} 



int main()
{ 
   /*long i; o_t *o; 
   printf("starting \n");
   o = create_order();
   for(i=100000; i>=0; i-- )
      insert_bottom( o, p(i) );
   for(i=100001; i< 300007; i+=2 )
   {  insert_after(o, p(i+1), p(i-1) );
      insert_before( o, p(i), p(i+1) );
   }
   printf("inserted 300000 elements. ");
   for(i = 250000; i < 300007; i++ )
      delete_o( o, p(i) );
   printf("deleted 50000 elements. ");
   insert_top( o, p(300006) );
   for(i = 250000; i < 300006; i++ )
      insert_before( o, p(i) , p(300006) );
   printf("reinserted. now testing order\n");
   for( i=0; i < 299000; i +=42 )
   {  if( is_before( o, p(i), p(i+23) ) != 1 )
      {  printf(" found error (1) \n"); exit(0);
      }
   }
   for( i=300006; i >57; i -=119 )
   {  if( is_before( o, p(i), p(i-57) ) != 0 )
      {  printf(" found error (0) \n"); exit(0);
      }
   }
   printf("finished. no problem found.\n");*/
} 
