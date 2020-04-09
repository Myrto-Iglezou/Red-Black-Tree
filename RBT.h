#include <stdio.h>
#include <stdlib.h>

typedef struct Treenode{
    void* data;
    char color;
    struct Treenode* left;
    struct Treenode* right;
    struct Treenode* parent;
    
}Treenode;

Treenode * guard;

void LeftRotate(Treenode **root,Treenode* x);

void RightRotate(Treenode **root,Treenode* y);

void insertion(Treenode **root,voterptr voter);

void Fixedinsertion(Treenode **root,Treenode* z);

void deleteTree(Treenode * root);

Treenode* FindData(Treenode *root,void* data);

void DeleteVoter(Treenode **root,char* id);

void FixedDelete(Treenode **root,Treenode* x);

void transplant(Treenode **root,Treenode * x,Treenode* y);

void voted(Treenode *root,int *count);

void printTree(FILE* f,Treenode * root);