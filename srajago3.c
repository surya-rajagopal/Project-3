
/*


*/



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
	int finished = 0;
	int dummy = 0;
	int tmp_height, old_height;

	//Rotation Part	- (Referred from the Text Book)
	//printf("In Rotation\n");
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 	  while( tmp != NULL && !finished){
		  old_height= tmp->height;
				dummy++;
	   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		  if(tmp->left->height - tmp->right->height == 2 )
		    { 
			//printf("Left Height greater\n");		
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
			//printf("Right Height greater\n");		
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
		  else 
		    { 
			//printf("Height not differing by 2\n");		
		      if( tmp->left->height > tmp->right->height )
			{
			  tmp->height = tmp->left->height + 1;
			}
		      else
			{
			  tmp->height = tmp->right->height + 1;
			}
		    }
		  if( tmp->height == old_height || tmp->parent == tmp){
			    finished = 1;
		  }
		//printf("DUmmy %d\n", dummy);		
		
		//printf("assigning tmp\n");		
  		  tmp = tmp->parent;
		  //print	
		//printf("assigned tmp: %p\n", tmp);		
		}
		//printf("Rotation Ended\n" );
	   ////////////////////////////////////////////////////////////////////////////////////////////////////////////////


}
long p(long q){
	return( (1247*q +104729) % 300007 );
	//return q;
}

void insert_before(o_t *ord, key_t a, key_t b){

	//printf("Entering I/B?!\n");
        int finished = 0;

	if(ord == NULL || ord->left == NULL || addrArray[b] == NULL){
		return;
	}

	o_t* tmp = addrArray[b];
	o_t *old_leaf, *new_leaf;
	old_leaf = create_order();
	old_leaf->key = tmp->key;
	old_leaf->left = tmp->left;
	old_leaf->parent = tmp;
	old_leaf->height = 0;
	old_leaf->right = NULL;
	
	new_leaf = create_order();
	new_leaf->key = a;
	new_leaf->left = (o_t *)a;
	new_leaf->parent = tmp;
	new_leaf->height = 0;
	new_leaf->right = NULL;
	tmp->left = new_leaf;
	tmp->right = old_leaf;
	tmp->key = NKEY;
	//tmp->height = 1;

	addrArray[a] = tmp->left;

        addrArray[old_leaf->key] = old_leaf;

	if(tmp == maxKey){
		maxKey = old_leaf;
	}


	performRotation(tmp->parent);
}

void insert_after(o_t *ord, key_t a, key_t b){


	//printf("Entering I/A?!\n");

	stack *rotateStack = createStack();
        int finished = 0;

	if(ord == NULL || ord->left == NULL|| addrArray[b] == NULL){
		return;
	}
	
	o_t* tmp = addrArray[b];

	//printf("ADDr B?!\n");

	o_t *old_leaf, *new_leaf;
	old_leaf = create_order();
	old_leaf->key = tmp->key;
	old_leaf->parent = tmp;
	old_leaf->left = tmp->left;

	new_leaf = create_order();
	new_leaf->key = a;
	new_leaf->parent = tmp;
	new_leaf->left = (o_t*)a;

	tmp->left = old_leaf;
	tmp->right = new_leaf;
	tmp->key = NKEY;
	//tmp->height = 1;

	addrArray[a] = tmp->right;

        addrArray[old_leaf->key] = old_leaf;

	if(tmp == maxKey){
		maxKey = new_leaf;
	}

	//printf("ROTATION N/E?!\n");

	performRotation(tmp->parent);
}

void insert_top(o_t *ord, key_t a){

	if(ord == NULL){
		return;
	}
	o_t *tmp = ord;
	//minKey = a;
	o_t *insertElement = returnOrderNode(a);
	if(ord->left == NULL){
	 	ord->left = (o_t*) a;
		ord->right = NULL;
		ord->parent = NULL;
		ord->height = 0;
		addrArray[a] = tmp;
		ord->key = a;
		minKey = tmp;
		maxKey = tmp;
		return;
	}	
	else if(ord->right == NULL){
		 o_t *old_leaf;
		 old_leaf = create_order();
		 old_leaf->left = tmp->left; 
		 old_leaf->key = tmp->key;
		 old_leaf->right  = NULL;
 		 old_leaf->parent = tmp;		 
  		 addrArray[tmp->key] = old_leaf;
		 old_leaf->height = 0;
  		 //addrArray[tmp->key] = tmp->left;
		 insertElement->parent = tmp;
		 insertElement->left = (o_t*) a;

		 tmp->left = old_leaf;
		 tmp->right = insertElement;	
		 tmp->key = NKEY;	
		 //tmp->height = 1;

  		 addrArray[a] = tmp->right;

		 minKey = tmp->left;
		 maxKey = insertElement;
		
	      }

	      else{
		 tmp = maxKey;
		 //printf("Max Key before mod %d", maxKey->key);
		 o_t *old_leaf;
		 old_leaf = create_order();
		 old_leaf->left = tmp->left; 
		 old_leaf->key = tmp->key;
		 old_leaf->right  = NULL;
 		 old_leaf->parent = tmp;		 
  		 addrArray[tmp->key] = old_leaf;
		 old_leaf->height = 0;

		 insertElement->parent = tmp;
		 insertElement->left = (o_t*) a;

		 tmp->left = old_leaf;
		 tmp->right = insertElement;	
		 tmp->key = NKEY;	
		 //tmp->height = 1;

  		 addrArray[a] = tmp->right;

		 maxKey = insertElement;

		
		 //performRotation(tmp->parent);

	      } 	

}


void insert_bottom(o_t *ord, key_t a){

	if(ord == NULL){
		return;
	}
	o_t *tmp = ord;
	//minKey = a;
	o_t *insertElement = returnOrderNode(a);
	if(ord->left == NULL){
	 	ord->left = (o_t*) a;
		ord->right = NULL;
		ord->parent = NULL;
		ord->height = 0;
		addrArray[a] = tmp;
		ord->key = a;
		minKey = tmp;
		maxKey = tmp;
		return;
	}	
	else if(ord->right == NULL){
		 o_t *old_leaf;
		 old_leaf = create_order();
		 old_leaf->left = tmp->left; 
		 old_leaf->key = tmp->key;
		 old_leaf->right  = NULL;
 		 old_leaf->parent = tmp;		 
  		 addrArray[tmp->key] = old_leaf;
		 old_leaf->height = 0;

		 tmp->left = insertElement;
		 tmp->right = old_leaf;	
		 tmp->key = NKEY;	
		 //tmp->height = 1;

		 insertElement->parent = tmp;
		 insertElement->left = (o_t*) a;
  		 addrArray[a] = tmp->left;

		 minKey = insertElement;
		 maxKey = old_leaf;
		
	      }

	      else{
		 tmp = minKey;
		 o_t *old_leaf;
		 old_leaf = create_order();
		 old_leaf->left = tmp->left; 
		 old_leaf->key = tmp->key;
		 old_leaf->right  = NULL;
 		 old_leaf->parent = tmp;		 
  		 addrArray[tmp->key] = old_leaf;
		 old_leaf->height = 0;

		 tmp->left = insertElement;
		 tmp->right = old_leaf;	
		 tmp->key = NKEY;	
		 //tmp->height = 1;

		 insertElement->parent = tmp;
		 insertElement->left = (o_t*) a;
  		 addrArray[a] = tmp->left;

		 minKey = insertElement;

		 performRotation(tmp->parent);

	      } 	
}

void delete_o(o_t *ord, key_t a){
        int finished = 0, flag;
	o_t* parent, *tmp, *grandParent;
	//printf("Enter Delete\n");
	if(ord == NULL || addrArray[a] == NULL){
		return;
	}


	o_t* delNode = addrArray[a];
	parent = delNode->parent;
	grandParent = parent->parent;
	
	if(grandParent->left == parent){
		//printf("Grand Paren Left\n");

		if(parent->left==delNode){
			grandParent->left = parent->right;
			//addrArray[grandParent->left->key] = parent->right;		
		}else if(parent->right==delNode){
			grandParent->left = parent->left;
			//addrArray[grandParent->left->key] = parent->left;		
		}	
		grandParent->left->parent = grandParent;
		if(delNode == maxKey)
			maxKey = grandParent->left;
		free(delNode);
		free(parent);

	}
	else if(grandParent->right == parent){
		//printf("Grand Paren Right\n");
		if(parent->left == delNode){
			grandParent->right = parent->right;
			//addrArray[grandParent->right->key] = parent->right;		
		}
		else if(parent->right == delNode){
			grandParent->right = parent->left;
			//addrArray[grandParent->right->key] = parent->left;		

		}
		if(delNode == maxKey)
			maxKey = grandParent->right;
		grandParent->right->parent=grandParent;
		free(delNode);
		free(parent);

	}

	

	addrArray[a]=NULL;
		//printf("Delete Rotation\n");
	performRotation(grandParent->parent);
		//printf("After rot\n");


}

int is_before(o_t *ord, key_t a, key_t b){
        o_t *aNode, *bNode, *aTmp, *bTmp, *left_prev = NULL, *right_prev = NULL;;

	if(a == 42)
		printf("break point\n");
	int aCount = 0, bCount = 0, diff;
	aNode = addrArray[a];
	bNode = addrArray[b];
	aTmp = aNode;
	bTmp = bNode;
	while (aTmp != NULL){
		aTmp = aTmp->parent;
		aCount++;
	}
	while (bTmp != NULL){
		bTmp = bTmp->parent;
		bCount++;
	}

	if (aCount < bCount){
		diff = bCount - aCount;
		while(diff>0){
			bNode = bNode->parent;
			diff--;
		}
	}
	else if (aCount > bCount){
		diff = aCount - bCount;
		while(diff>0){
			aNode = aNode->parent;
			diff--;
		}
	}

	while ((aNode != NULL && bNode != NULL) && aNode->parent != bNode->parent )
	{
		//left_prev = aNode;
		aNode = aNode->parent;
		//right_prev = bNode;
		bNode = bNode->parent;
		//if(aNode == bNode){
		//break;		
		//}
	}
	if (aNode->parent->left == aNode)
		return 1;
	else //if(aNode->left == right_prev)
		return 0;	
	//else 
	//	return -1;
} 
void padding ( char ch, int n )
{
  int i;
  for ( i = 0; i < n; i++ )
    putchar ( ch );
}


void structure (o_t *root, int level )
{
  int i;
  if ( root->right == NULL ) 
    {
      padding ( '\t', level );
      printf ( "%d ", root->key);
      printf("\n");
    }
  else 
    {
      structure ( root->right, level + 1 );
      padding ( '\t', level );
      printf ( "%d ", root->key);
      printf("\n");
      structure ( root->left, level + 1 );
    }
}


int main()
{  long i; o_t *o; 
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
   printf("finished. no problem found.\n");
} 
