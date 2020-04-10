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

void insertion(Treenode **root,void* data,int (*comparator)(const void*,const void*));

void Fixedinsertion(Treenode **root,Treenode* z);

void deleteTree(Treenode * root);

Treenode* FindData(Treenode *root,void* data,int (*comparator)(const void*,const void*));

void DeleteData(Treenode **root,void* data,int (*comparator)(const void*,const void*)){

void FixedDelete(Treenode **root,Treenode* x);

void transplant(Treenode **root,Treenode * x,Treenode* y);

void printTree(FILE* f,Treenode * root);

int comparator(const void* p1, const void* p2);
// Return value meaning
// <0 The element pointed by p1 goes before the element pointed by p2
// 0  The element pointed by p1 is equivalent to the element pointed by p2
// >0 The element pointed by p1 goes after the element pointed by p2
//Source: http://www.cplusplus.com/reference/cstdlib/qsort/
