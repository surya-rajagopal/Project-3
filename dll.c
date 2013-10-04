
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define NKEY -1


typedef int key_t;

typedef struct linearNode{
	key_t key;
	linearNode *left;
	linearNode *right;
	linearNode *parent;
	int height;
}o_t;


o_t *maxKey, *minKey;

o_t* addrArray[400000];

/*  Stack Operations -- (Referred from the Text Book)

/*
   structure for implementing the stack
 */

typedef struct stack {
	o_t *tree;
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
void stackPush( o_t *tree, stack *s){
	stack *tmp = (stack*) malloc(sizeof(stack));
	tmp->tree = tree;
	tmp->next = s->next;
	s->next = tmp;
}

/*
   returns the top element of the Stack and deletes the item from the Stack
*/
o_t* stackPop(stack *s){
	stack *tmp; o_t* node;
	tmp = s->next;
	s->next = tmp->next;
	node = tmp->tree;
	free(tmp);
	return node;
}

/*
   return the top element from the stack
*/
o_t* stackTop(stack *s){
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
	}while ( tmp != NULL );
}


/*End of Stack operations*/




o_t* create_order(){
	o_t* tmp = (o_t*) malloc(sizeof(o_t));
	tmp->key = NKEY;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->parent = NULL;
	tmp->height = -1;
	return tmp;
}

o_t* returnOrderNode(key_t a){
	o_t* tmp = (o_t*) malloc(sizeof(o_t));
	tmp->key = a;
	tmp->left = NULL;
	tmp->right = NULL;
	tmp->height = 0;
	return tmp;
}


/*
   Performs Left Rotation on the tree - (Referred from the Text Book)
 */

void leftRotation(o_t *txt){
	o_t *tmp = txt->left;
	int tmpNodeCount;
        key_t tmp_key;
        tmp_key = txt->key;
        txt->left = txt->right;
        txt->key = txt->right->key;
        txt->right = txt->left->right;
        txt->right->parent = txt;
        txt->left->right = txt->left->left;
        txt->left->left = tmp;
        txt->left->key = tmp_key;
        tmp->parent = txt->left;
	//txt->left->nodeCount = txt->left->left->nodeCount + txt->left->right->nodeCount;
}

/*
   Performs Right Rotation on the tree - (Referred from the Text Book)
 */
void rightRotation(o_t *txt){
        o_t *tmp = txt->right;
        key_t tmp_key = txt->key;
        txt->right = txt->left;
        txt->key = txt->left->key;
        txt->left = txt->right->left;
        txt->left->parent = txt;
        txt->right->left = txt->right->right;
        txt->right->right = tmp;
        txt->right->key = tmp_key;
        tmp->parent = txt->right;
	//txt->right->nodeCount = txt->right->left->nodeCount + txt->right->right->nodeCount;
}


void performRotation(o_t* tmp){
	int finished = 1;
	int tmp_height, old_height;

	//Rotation Part	- (Referred from the Text Book)

	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	  while( tmp != NULL && !finished){
		  old_height= tmp->height;

	   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		  if(tmp->left->height - tmp->right->height == 2 )
		    { 
		      if( tmp->left->left->height - tmp->right->height == 1 )
			{ 
			  rightRotation( tmp );
			  tmp->right->height = tmp->right->left->height + 1;
			  tmp->height = tmp->right->height + 1;
			}
		      else
			{ 
			  leftRotation( tmp->left );
			  rightRotation( tmp );
			  tmp_height = tmp->left->left->height;
			  tmp->left->height = tmp_height + 1;
			  tmp->right->height = tmp_height + 1;
			  tmp->height = tmp_height + 2;
			}
		    }
		  else if( tmp->left->height - tmp->right->height == -2 )
		    { 
		      if( tmp->right->right->height - tmp->left->height == 1 )
			{ 
			  leftRotation( tmp );
			  tmp->left->height = tmp->left->right->height + 1;
			  tmp->height = tmp->left->height + 1;
			}
		      else
			{ 
			  rightRotation( tmp->right );
			  leftRotation( tmp );
			  tmp_height = tmp->right->right->height;
			  tmp->left->height = tmp_height + 1;
			  tmp->right->height = tmp_height + 1;
			  tmp->height = tmp_height + 2;
			}
		    }
		  else if( tmp->left != NULL && tmp->right != NULL)
		    { 
		      if( tmp->left->height > tmp->right->height )
			{
			  tmp->height = tmp->left->height + 1;
			}
		      else
			{
			  tmp->height = tmp->right->height + 1;
			}
		    }
		  if( tmp->height == old_height ){
			    finished = 1;
		  }

  		  tmp = tmp->parent;
		}

	   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}
long p(long q){
	return( (1247*q +104729) % 300007 );
}



void insert_top(o_t *ord, key_t a){

	if(!ord){
		return;
	}

	o_t* tmp = ord;

	if(tmp->left == NULL && tmp->right == NULL && tmp->key == -1){

		tmp->key = a;
		tmp->left = NULL;
		tmp->right = NULL;
		tmp->height = 0;
		maxKey = tmp;
		minKey = tmp;
		addrArray[a] = tmp; 
		return;
	}

	else{
		tmp = maxKey;
		o_t* new_leaf = create_order();
		new_leaf->key = a;
		new_leaf->left = tmp;
		new_leaf->right = NULL;
		tmp->right = new_leaf;
		maxKey = new_leaf;
		addrArray[a] = new_leaf; 
		performRotation(tmp);
	}

}

void insert_bottom(o_t *ord, key_t a){


	if(!ord){
		return;
	}
	o_t* tmp = ord;

	if(tmp->left == NULL && tmp->right == NULL && tmp->key == -1){

		tmp->key = a;
		tmp->left = NULL;
		tmp->right = NULL;
		tmp->height = 0;
		maxKey = tmp;
		minKey = tmp;
		addrArray[a] = tmp; 
		return;
	}

	else{
		tmp = minKey;
		o_t* new_leaf = create_order();
		new_leaf->key = a;
		new_leaf->left = NULL;
		new_leaf->right = tmp;
		tmp->left = new_leaf;
		minKey = new_leaf;
		addrArray[a] = new_leaf; 
		performRotation(tmp);
	
	}
}



void insert_before(o_t *ord, key_t a, key_t b){


	o_t* tmp = addrArray[b];
	o_t* new_leaf, *prev_leaf;
	if(tmp == minKey){
		new_leaf =  create_order();
		new_leaf->key = a;
		new_leaf->left = NULL;
		new_leaf->right	= tmp;
		minKey = new_leaf;
		addrArray[a] = new_leaf;
		performRotation(tmp);
		return;
	}

	new_leaf =  create_order();
	new_leaf->key = a;

	prev_leaf = tmp->left;
	prev_leaf->right = new_leaf;
	new_leaf->right = tmp;
	new_leaf->left = prev_leaf;
	tmp->left = new_leaf;
	addrArray[a] = new_leaf;
	performRotation(tmp);
}


void insert_after(o_t *ord, key_t a, key_t b){

	o_t* tmp = addrArray[b];
	o_t* new_leaf, *next_leaf;
	if(tmp == maxKey){
		new_leaf =  create_order();
		new_leaf->key = a;
		new_leaf->right = NULL;
		new_leaf->left	= tmp;
		maxKey = new_leaf;
		addrArray[a] = new_leaf;
		performRotation(tmp);
		return;
	}

	new_leaf =  create_order();
	new_leaf->key = a;

	next_leaf = tmp->right;
	next_leaf->left = new_leaf;
	new_leaf->right = next_leaf;
	new_leaf->left = tmp;
	tmp->right = new_leaf;
	addrArray[a] = new_leaf;
	performRotation(tmp);
}

void delete_o(o_t *ord, key_t a){

	if(!ord){
		return;
	}
	o_t* tmp = addrArray[a];
	o_t* prev_leaf, *next_leaf;

	
	if(tmp == minKey){
		minKey = tmp->right;
		tmp->right->left == NULL;
		return;
	}


	if(tmp == maxKey){
		maxKey = tmp->left;
		tmp->left->right == NULL;
		return;
	}
	
	prev_leaf = tmp->left;
	next_leaf = tmp->right;
	prev_leaf->right = next_leaf;
	next_leaf->left = prev_leaf;
	addrArray[a] = 	NULL;
}

int is_before(o_t *ord, key_t a, key_t b){
	o_t *aNode, *bNode, *left, *right;
	int key = 0;
	aNode = addrArray[a];
	bNode = addrArray[b];
	left = aNode->left;	
	while(left != NULL){
		left = left->left;
		if(left == bNode){
			return 0;	
		}
	}

	return 1;
}


int main()
{ 
   long i; o_t *o; 
   printf("starting \n");
   o = create_order();
   for(i=100000; i>=0; i-- ){
// 	printf("\n");
     insert_bottom( o, p(i) );
//	structure(o,0);
   }	
   //printf("First Insert Bottom\n");	
   for(i=100001; i< 300007; i+=2 )
   {	
      insert_after(o, p(i+1), p(i-1) );//printf("SS0 %d\n",i);
      insert_before( o, p(i), p(i+1) );
   }
   
   printf("inserted 300000 elements. ");
   for(i = 250000; i < 300006; i++ )
      delete_o( o, p(i) );
   printf("deleted 50000 elements. ");
   insert_top( o, p(300006) );
   for(i = 250000; i < 300005; i++ )
      insert_before( o, p(i) , p(300006) );
   printf("reinserted. now testing order\n");
  

   for( i=0; i < 299000; i +=42 )
   {  if( is_before( o, p(i), p(i+23) ) != 1 )
      {  
	 printf(" found error (1) \n"); exit(0);
      }
   }
   for( i=300006; i >57; i -=119 )
   {  if( is_before( o, p(i), p(i-57) ) != 0 )
      {  printf(" found error (0) :\n"); exit(0);
      }
   }
   printf("finished. no problem found.\n");
} 
