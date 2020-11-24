#include "treeMT.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>




Tree* makeEmptyTree()
{
    Tree* newT = malloc(sizeof(Tree));
    pthread_mutex_init(&newT->lock, NULL);
    newT->root = NULL;
    return newT;
    
    //newT->root->left = NULL;
    //newT->root->right = NULL;
    //pthread_mutex_destroy(&Tree->lock);

  /*
    TODO: Create a new Tree, setting the root to NULL. Initialize any necessary mutexes. 

    Return Tree*.
   */

}

void insertIntoTree(Tree* t, int val)
{
    TNode* newNode;
    newNode = malloc(sizeof(TNode));
    newNode->val = val;

    if(t->root == NULL){
        t->root = newNode;
        return;
    }
    
    TNode* curr = t->root;
    pthread_mutex_t* lock1;
    lock1 = &t->lock;
    pthread_mutex_lock(lock1);
    
    
    while(curr){
        pthread_mutex_lock(&curr->lock);
        pthread_mutex_unlock(lock1);
        lock1 = &curr->lock;
        
        if(val > curr->val){
            if(curr->right == NULL) {
                curr->right = newNode;
                break;
            }
            curr = curr->right;
        }
        if(val < curr->val){
            if(curr->left == NULL){
                curr->left = newNode;
                break;
            }
            curr = curr->left;
        }
        if(val == curr->val)
            break;
        
        
    }
    pthread_mutex_unlock(lock1);
}
    
    

void printTreeAux(TNode* root)
{
   if (root == NULL)
      return;
   else {
      printf("(");
      printTreeAux(root->left);
      printf(" %d ",root->val);
      printTreeAux(root->right);
      printf(")");      
   }
}

void printTree(Tree* t)
{
  printTreeAux(t->root);
}

void destroyTreeAux(TNode* root)
{
  if(root != NULL){
    destroyTreeAux(root->left);
    destroyTreeAux(root->right);
    pthread_mutex_destroy(&root->lock);
    free(root);
  }
}

void destroyTree(Tree* t)
{
  destroyTreeAux(t->root);
  pthread_mutex_destroy(&t->lock);
  free(t);
}


