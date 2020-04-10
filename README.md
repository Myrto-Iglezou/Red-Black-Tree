# Red-Black-Tree

A red–black tree is a self-balancing binary search tree. Each node of the binary tree has an extra bit, and that bit is interpreted as the color (red or black) of the node. These color bits are used to ensure the tree remains balanced during insertions and deletions.

# How it works

Balance is preserved by painting each node of the tree with one of two colors in a way that satisfies certain properties, which collectively constrain how unbalanced the tree can become in the worst case. When the tree is modified, the new tree is subsequently rearranged and repainted to restore the coloring properties. The properties are designed in such a way that this rearranging and recoloring can be performed efficiently.

Every node follows following rules:
* Every node has a color either red or black
* Root of tree is always black
* A red node cannot have a red parent or red child
* Every path from a node (including root) to any of its descendant NULL node has the same number of black nodes

# Complexity

If n is the total number of elements in the tree:
 
 Algorithm  | Average | Worst case
 ---------- | ------- | ----------
  Space		   | O(n)	    |O(n)
  Search	   |	O(log n)	|O(log n)
  Insert	  	| O(log n)	|O(log n)
  Delete	  	| O(log n)	|O(log n)
  
  # The files
  
  The Insertion, Deletion and Rotation functions are based on
corresponding functions in Thomas H. Cormen's book (pp. 313-326):
https://github.com/walkccc/CLRS.
In place of T.empty, a guard tree node has been created, which always points to
guard and has a black color, so that the color of non-existent nodes is always considered
black.
