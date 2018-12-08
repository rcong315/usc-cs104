#include "bst.h"

#include <stack>
#include <queue>
#include <set>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <climits>

using namespace std;

bool isBSTHelper(Node* root, int min, int max)  
{  
  if (root == NULL)  
     return true; 
         
  if (root -> key < min || root -> key > max)  
     return false;  
  
  return isBSTHelper(root -> left, min, root -> key - 1) && isBSTHelper(root -> right, root -> key + 1, max);  
}  

//Helper functions?
bool isBST(Node* root) {
  return(isBSTHelper(root, INT_MIN, INT_MAX)); 
} 

int max(int a, int b) 
{ 
  if (a >= b) {
  	return a;
  }
  return b;
}     
  
int height(Node* root) 
{ 
   if(root == nullptr) 
       return 0; 
  
   return 1 + max(height(root -> left), height(root -> right)); 
}  

bool isBalanced(Node* root) 
{ 
   int lh, rh; 
  
   if(root == nullptr) 
    return true;  
  
   lh = height(root -> left); 
   rh = height(root -> right); 
  
   if(abs(lh - rh) <= 1 && isBalanced(root -> left) && isBalanced(root -> right)) 
     return true; 
  
   return false; 
}