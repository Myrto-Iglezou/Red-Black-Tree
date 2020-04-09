#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RBT.h"

void LeftRotate(Treenode **root,Treenode * x){
	
	Treenode * y = x->right;		
	x->right = y->left;				 
									// left child of y becomes the right child of x
	if(y->left!=guard)
		y->left->parent = x;
								// y becomes the root of the subtree
	y->parent = x->parent;
	
	if(x->parent==guard)		// if x was root now y is the root
		*root = y;
	else if(x==x->parent->left)		// if x was in the left of the parent
		x->parent->left = y;
	else x->parent->right = y;		// if x was in the right of the parent
	y->left = x;				// x becomes the left child of y
	x->parent = y;
}

void RightRotate(Treenode **root,Treenode * x){
    
	Treenode * y = x->left;
	x->left = y->right;
		
	if(y->right!=guard)
		y->right->parent = x;

	y->parent = x->parent;
	
	if(x->parent==guard)
		*root = y;
	else if(x==x->parent->right)
		x->parent->right = y;
	else x->parent->left = y;
	y->right = x;
	x->parent = y;
}

void insertion(Treenode ** root,voterptr voter){
	Treenode * z = malloc(sizeof(Treenode));
	z->constituent = voter;
	z->left = guard;
	z->right = guard;
	z->parent = guard;
	if(*root == guard){
		z->color = 'B';
		*root = z;
		return;
	}
	Treenode * y = guard;
	Treenode * x = *root;
		
	while(x!=guard){			// stop when x finds the last node and save it at y, x becomes guard
		y = x;
		if(strcmp(z->constituent->id, x->constituent->id)<0)
			x = x->left;
		else x = x->right;
	}
	z->parent = y;
	
	if(strcmp(z->constituent->id, y->constituent->id)<0) //put z right or left,depends on the id
		y->left = z;
	else 
		y->right = z;

	z->color = 'R';
	Fixedinsertion(root,z);
}

void Fixedinsertion(Treenode **root,Treenode * z){	// we insert z in this function with color red
	Treenode * y;
	while(z->parent->color == 'R'){		// if both child and parent are red
		if(z->parent == z->parent->parent->left){
			y = z->parent->parent->right;		// y is the uncle
			if(y->color == 'R'){			// if uncle is red, then all three are red
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				z = z->parent->parent;
			}else{							// if uncle is black
				if(z == z->parent->right){	// if we have a triangle form
					z = z->parent;
					LeftRotate(root,z);		// we make it a line
				}
				z->parent->color = 'B';		//we fix the colors in the line, z is the left last node of the subtree
				z->parent->parent->color = 'R';
				RightRotate(root,z->parent->parent);
			}
		}else if(z->parent == z->parent->parent->right){	// same thing in the right side 
			y = z->parent->parent->left;
			if(y->color == 'R'){
				z->parent->color = 'B';
				y->color = 'B';
				z->parent->parent->color = 'R';
				z = z->parent->parent;
			}else{
				if(z == z->parent->left){
					z = z->parent;
					RightRotate(root,z);
				}
				z->parent->color = 'B';
				z->parent->parent->color = 'R';
				LeftRotate(root,z->parent->parent);
			}
		}
	}
	(*root)->color = 'B'; //root has to be always black
}

Treenode* CheckVoter(Treenode *root,char* id){	// check
	Treenode *temp  = root;			

	if(temp==guard || !strcmp(temp->constituent->id,id))
		return temp;
	if(strcmp(temp->constituent->id,id)>0){
		temp = temp->left;
		CheckVoter(temp,id);
	}
	else if(strcmp(temp->constituent->id,id)<0){
		temp = temp->right;
		CheckVoter(temp,id);
	}
}

void DeleteVoter(Treenode **root,char* id){

	Treenode * z = CheckVoter(*root,id);
	Treenode * y = z;
	Treenode * x;
	if(z==guard)	//if voter doesn't exist return
		return;
	delete_v(z->constituent);  //delete the voter node
	char fcolor = y->color;
	if(z->left == guard){		// if z has one child(on the right)
		x = z->right;
		transplant(root,z,z->right);	// the right child takes place of z
	}else if(z->right == guard){	// if z has one child(on the left)
		x = z->left;
		transplant(root,z,z->left);		// the left child takes place of z
	}else{								// z has 2 children 
		while (y->right != guard)	// y will be the max of the smaller ids of z
	 	 	y = y->right;
	 	fcolor = y->color;			// save the color before any change 
	 	x = y->right;
	 	if(y->parent == z)	// if z is one node from the end
	 		x->parent = y;	// x->parent was guard, now is y
	 	else{
	 		transplant(root,y,y->right);	// fix the subtree in the right of z with y as root
	 		y->right = z->right;
	 		y->right->parent = y;
		}
		transplant(root,z,y); // y takes place of z, coonect the subtree with the left side
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}

	free(z);	// delete z
	if(fcolor == 'B')
		FixedDelete(root,x);
}

void transplant(Treenode **root,Treenode * x,Treenode* y){
	if(x->parent == guard)
		*root = y;
	else if(x == x->parent->left)
		x->parent->left = y;
	else x->parent->right = y;
	y->parent = x->parent; 
}

void FixedDelete(Treenode **root,Treenode * x){
	Treenode *w;
	while(x != *root && x->color == 'B'){
		if(x == x->parent->left){
			w = x->parent->right;	// w is the sibling
			if(w->color == 'R'){	// if sibling is red, his children have to be black
				w->color = 'B';		// we reverse the colors of w and x->parent
				x->parent->color = 'R';
				LeftRotate(root,x->parent);
				w = x->parent->right;	// now sibling of x is one of his sibling's child
			}
			if(w->left->color == 'B' && w->right->color == 'B'){	// his sibling and both sibling's children are black
				w->color = 'R'; // then sibling is red
				x = x->parent;
			}else{
				if(w->right->color == 'B'){  // sibling is black, his left child is red and the right is black
					w->left->color = 'B';	// reverse the colors of w and w->left child
					w->color = 'R';
					RightRotate(root,w);	
					w = x->parent->right;	// now the sibling is the black node with a red right child
				}
				w->color = x->parent->color;	// fix the colors
				x->parent->color = 'B';
				w->right->color = 'B';
				LeftRotate(root,x->parent);
				x = *root;
			}

		}
		else{							// same thing on the right side
			w = x->parent->left;
			if(w->color == 'R'){
				w->color = 'B';
				x->parent->color = 'R';
				RightRotate(root,x->parent);
				w = x->parent->left;
			}
			if(w->right->color == 'B' && w->left->color == 'B'){
				w->color = 'R';
				x = x->parent;
			}else if(w->left->color == 'B'){
				w->right->color = 'B';
				w->color = 'R';
				LeftRotate(root,w);
				w = x->parent->left;
			}
			w->color = x->parent->color;
			x->parent->color = 'B';
			w->left->color = 'B';
			RightRotate(root,x->parent);
			x = *root;
		}
	}
	x->color = 'B';
}

void deleteTree(Treenode * root){
	if(root==guard)
		return;
	deleteTree(root->left);
	deleteTree(root->right);
	delete_v(root->constituent);
	free(root);	
}



void printTree(FILE * f,Treenode * root){	//print tree in the outfile
	if(root==guard)
		return;
	printTree(f,root->left);
	fprintf(f, "%s %s %s %d %s %d \n", root->constituent->id,root->constituent->name,root->constituent->surname, root->constituent->age,root->constituent->gender,root->constituent->PostalCode);
	printTree(f,root->right);	
}

Treenode* createGuard(){
	Treenode * guard = malloc(sizeof(Treenode));
	guard->left = guard;
	guard->right = guard;
	guard->parent = guard;
	guard->constituent = NULL;
	guard->color = 'B';
	return guard;
}
