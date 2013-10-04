#include<iostream>
#include<cstdlib>
#include<cstring>
#include<map>
#include<stdio.h>

using namespace std;

#define N -1
#define BLOCKSIZE 256

typedef int height_t;

typedef struct node_text
{
        key_t key;
        height_t height;
        struct node_text *left;
        struct node_text *right;
        struct node_text *parent;
} o_t;

map<key_t, o_t*>::iterator it;
map<key_t, o_t*> hashtable;
o_t *first = NULL, *last = NULL;
o_t *currentblock = NULL, *free_list = NULL;
int size_left;
int nodes_taken = 0;
int nodes_returned = 0;


o_t *get_node()
{
        o_t *tmp;
        nodes_taken += 1;
        if (free_list != NULL)
        {
                tmp = free_list;
                free_list = free_list -> right;
        }
        else
        {
                if (currentblock == NULL || size_left == 0)
                {
                        currentblock = (o_t *) malloc(BLOCKSIZE * sizeof(o_t));
                        size_left = BLOCKSIZE;
                }
                tmp = currentblock++;
                size_left -= 1;
        }
        return (tmp);
}


void return_node(o_t *node)
{
        node->right = free_list;
        free_list = node;
        nodes_returned +=1;
}


o_t *create_node()
{
        o_t *tmp_node;
        tmp_node = get_node();
        tmp_node->left = NULL;
        tmp_node->right = NULL;
        tmp_node->parent = NULL;
	tmp_node->key = N;
        tmp_node->height = -1;
        return (tmp_node);
}


/* This function creates an empty linear ordered set */
o_t *create_order()
{
        o_t *tmp_node;
        tmp_node = create_node();
	first = last = tmp_node;
        return (tmp_node);
}


/* This function performs the left rotation of a tree */
void left_rotation(o_t *tree)
{
        o_t *tmp_node;
        key_t tmp_key;
        tmp_node = tree->left;
        tmp_key = tree->key;
        tree->left = tree->right;
        tree->key = tree->right->key;
        tree->right = tree->left->right;
        tree->right->parent = tree;
        tree->left->right = tree->left->left;
        tree->left->left = tmp_node;
        tree->left->key = tmp_key;
        tmp_node->parent = tree->left;
	first = tree;
	while (first->left != NULL)
		first = first->left;
}


/* This function performs the right rotation of a tree */
void right_rotation(o_t *tree)
{
        o_t *tmp_node;
        key_t tmp_key;
        tmp_node = tree->right;
        tmp_key = tree->key;
        tree->right = tree->left;
        tree->key = tree->left->key;
        tree->left = tree->right->left;
        tree->left->parent = tree;
        tree->right->left = tree->right->right;
        tree->right->right = tmp_node;
        tree->right->key = tmp_key;
        tmp_node->parent = tree->right;
	last = tree;
	while (last->right != NULL)
		last = last->right;
}


void balance_tree(o_t *tmp_node)
{
	int finished = 0;
	int tmp_height, old_height;
	while(!finished && tmp_node != NULL)
	{
		old_height = tmp_node->height;
		if (tmp_node->left->height - tmp_node->right->height == 2)
		{ 
			if (tmp_node->left->left->height - tmp_node->right->height == 1)
			{ 
				right_rotation(tmp_node);
				tmp_node->right->height = tmp_node->right->left->height + 1;
				tmp_node->height = tmp_node->right->height + 1;
			}
			else
			{ 
				left_rotation(tmp_node->left);
				right_rotation(tmp_node);
				tmp_height = tmp_node->left->left->height;
				tmp_node->left->height = tmp_height + 1;
				tmp_node->right->height = tmp_height + 1;
				tmp_node->height = tmp_height + 2;
			}
		}
		else if (tmp_node->left->height - tmp_node->right->height == -2)
		{ 
			if( tmp_node->right->right->height - tmp_node->left->height == 1)
			{ 
				left_rotation(tmp_node);
				tmp_node->left->height = tmp_node->left->right->height + 1;
				tmp_node->height = tmp_node->left->height + 1;
			}
			else
			{ 
				right_rotation(tmp_node->right);
				left_rotation(tmp_node);
				tmp_height = tmp_node->right->right->height;
				tmp_node->left->height = tmp_height + 1;
				tmp_node->right->height = tmp_height + 1;
				tmp_node->height = tmp_height + 2;
			}
		}
      		else 
		{ 
			if(tmp_node->left->height > tmp_node->right->height)
			{
				tmp_node->height = tmp_node->left->height + 1;
			}
			else
			{
				tmp_node->height = tmp_node->right->height + 1;
			}
		}
		if (tmp_node->height == old_height)
		{
			finished = 1;
		}
		tmp_node = tmp_node->parent;
	}
}


void node_split(o_t *tmp_node, o_t **old_leaf, o_t **new_leaf, key_t a)
{
        (*old_leaf) = get_node();
        (*new_leaf) = get_node();
        (*old_leaf)->key = tmp_node->key;
        (*old_leaf)->parent = tmp_node;
        (*old_leaf)->height = 0;

        (*new_leaf)->key = a;
        (*new_leaf)->parent = tmp_node;
        (*new_leaf)->height = 0;
 
	tmp_node->key = N;
}


/* This function inserts the key a as largest element in the ordered set */
void insert_top(o_t *ord, key_t a)
{
        o_t *old_leaf, *new_leaf;
        node_split(last, &old_leaf, &new_leaf, a);
	last->left = old_leaf;
        last->right = new_leaf;
	if (last == first)
	{
		first = last->left;
	}       
	last = new_leaf;
	hashtable[new_leaf->key] = new_leaf;
        if (old_leaf->key != N)
        {
                hashtable[old_leaf->key] = old_leaf;
        }
	balance_tree(new_leaf->parent);
}


/* This function inserts the key a as smallest element in the ordered set */
void insert_bottom(o_t *ord, key_t a) 
{
        o_t *old_leaf, *new_leaf;
        node_split(first, &old_leaf, &new_leaf, a);
        first->left = new_leaf;
        first->right = old_leaf;
	if (first == last)
	{
		last = first->right;
	}
        first = new_leaf;
        hashtable[new_leaf->key] = new_leaf;
	if (old_leaf->key != N)
	{
		hashtable[old_leaf->key] = old_leaf;
	}
	balance_tree(new_leaf->parent);
}


/* This function inserts the key a immediately before key b in the ordered set */
void insert_before(o_t *ord, key_t a, key_t b) 
{
        o_t *old_leaf, *new_leaf, *tmp_node;
	it = hashtable.find(b);
	tmp_node = it->second;
        node_split(tmp_node, &old_leaf, &new_leaf, a);
        tmp_node->left = new_leaf;
        tmp_node->right = old_leaf;
        if (first == tmp_node)
        {
                first = tmp_node->left;
        }
	else if (last == tmp_node)
	{
		last = tmp_node->right;
	}
        hashtable[new_leaf->key] = new_leaf;
        if (old_leaf->key != N)
        {
                hashtable[old_leaf->key] = old_leaf;
        }
	balance_tree(new_leaf->parent);
}


/* This function inserts the key a immediately after key b in the ordered set */
void insert_after(o_t *ord, key_t a, key_t b)  
{
        o_t *old_leaf, *new_leaf, *tmp_node;
        it = hashtable.find(b);
        tmp_node = it->second;
        node_split(tmp_node, &old_leaf, &new_leaf, a);
        tmp_node->right = new_leaf;
        tmp_node->left = old_leaf;
        if (first == tmp_node)
        {
                first = tmp_node->left;
        }
        else if (last == tmp_node)
        {
                last = tmp_node->right;
        }
        hashtable[new_leaf->key] = new_leaf;
        if (old_leaf->key != N)
        {
                hashtable[old_leaf->key] = old_leaf;
        }

	balance_tree(new_leaf->parent);
}


/* This function deletes the key a from the ordered set */
void delete_o(o_t *ord, key_t a)
{
        o_t *upper_node, *other_node, *tmp_node;
        it = hashtable.find(a);
        tmp_node = it->second;

	upper_node = tmp_node->parent;
	if (upper_node->right->key == tmp_node->key)
	{
		other_node = upper_node->left;
	}
	else
	{
		other_node = upper_node->right;
	}

        upper_node->key   = other_node->key;
        upper_node->left  = other_node->left;
        upper_node->right = other_node->right;
        upper_node->height = other_node->height;
	if (first == tmp_node || first == other_node)
        {
                first = upper_node;
        }
        else if (last == tmp_node || last == other_node)
        {
                last = upper_node;
        }

        return_node(tmp_node);
        return_node(other_node);
        hashtable.erase(it);
        if (upper_node->key != N)
        {
                hashtable[upper_node->key] = upper_node;
        }
   	balance_tree(upper_node->parent);
}


/* This function returns 1 if key a occurs before key b in the ordered set, 0 else */
int is_before(o_t *ord, key_t a, key_t b) 
{
        o_t *left_node, *right_node;
	int leftcount = 0, rightcount = 0;
	o_t *left_prev = NULL, *right_prev = NULL;
        it = hashtable.find(a);
        left_node = it->second;
        it = hashtable.find(b);
        right_node = it->second;
	while (left_node != NULL)
	{
		left_node = left_node->parent;
		leftcount++;
	}
	while (right_node != NULL)
	{
		right_node = right_node->parent;
		rightcount++;
	}
	it = hashtable.find(a);
        left_node = it->second;
        it = hashtable.find(b);
        right_node = it->second;
	if (leftcount < rightcount)
	{
		right_node = right_node->parent;
	}
	else if (leftcount > rightcount)
	{
		left_node = left_node->parent;
	}
	while (left_node != right_node)
	{
		left_prev = left_node;
		left_node = left_node->parent;
		right_prev = right_node;
		right_node = right_node->parent;
	}
	if (left_node->left == left_prev)
		return 1;
	else
		return 0;	
}


void inorder(o_t *tree)
{
        if (tree == NULL)
        {
                return;
        }
        else 
        {
                inorder(tree->left);
                cout<<"************************"<<endl;
                cout<<"The key is "<<tree->key<<endl;
                cout<<"The height is "<<tree->height<<endl;
                cout<<"The node address is "<<tree<<endl;
                cout<<"The parent address is "<<tree->parent<<endl;
                cout<<"************************"<<endl;
                inorder(tree->right);
        }
}

long p(long q)
{ return( (1247*q +104729) % 300007 );
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
