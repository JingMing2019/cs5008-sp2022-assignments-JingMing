/* name: Jing Ming */
/* email: ming.j@northeastern.edu */
/* AVL Tree */
/* balanced Binary search tree in which the heights of the subtrees of a node differ by no more than 1. */

#include<stdio.h>
#include<stdlib.h>
/*----defining the structure for Avl tree node----*/
typedef struct avlnode{
    int data;
    struct avlnode *left;
    struct avlnode *right;
    int height;
}node_t;

/*---defining structure for AVL tree--*/
typedef struct AVL{
    struct avlnode* root;
}Tree;

/* creating a new Avl node*/
node_t* NewNode(int data){

    node_t* temp = (node_t*)malloc(sizeof(node_t));
    if (temp == NULL) {
        printf("Memory is not allocated\n");
        exit(1);
    }
    temp->data = data;
    temp->left = NULL;
    temp->right = NULL;
    temp->height = 0;
    return temp;
}

/*------------Creating a Tree------------------*/
Tree* initTree(){
    Tree* t = (Tree*)malloc(sizeof(Tree));
    if(t == NULL){
        printf("Memory is not allocated\n");
        exit(1);
    }
    t->root = NULL;
    return t;
}

/* calculating maximum of 2 numbers*/
int max(int a,int b){
    if(a > b){
        return a;
    } else {
        return b;
    }
}

/* finding the height of the tree*/
int height(node_t* node){
    if(node == NULL)
        return -1;

    return node->height;
}

/* finding the balance factor of the node*/
int Balance(node_t* node){
    if(node == NULL)
        return 0;

    return height(node->left) - height(node->right);//height of Left subtree-height of right subtree.
}

/* left rotation of the node and updating the height of left and right subtree*/
//  1
//     2
//        3
// old root which is `1`
// new root which is `2`
//      2
//   1      3
node_t* LeftRotate(node_t* oldRoot){

    node_t* newRoot = oldRoot->right;
    node_t* temp = newRoot->left;

    newRoot->left = oldRoot;
    oldRoot->right = temp;

    // update old root oldRoot's height
    oldRoot->height = max(height(oldRoot->left),height(oldRoot->right)) + 1;
    // update new root oldRoot's height
    newRoot->height = max(height(newRoot->left),height(newRoot->right)) + 1;

    return newRoot;
}

/*--- function to perform the Right rotation and updating the height of left and right subtree--*/
//        3
//     2
//  1
// old root which is `3`
// new root which is `2`
//      2
//   1      3
node_t* RightRotate(node_t* oldRoot){

    node_t* newRoot = oldRoot->left;
    node_t* temp = newRoot->right;

    newRoot->right = oldRoot;
    oldRoot->left = temp;

    // update old root oldRoot's height
    oldRoot->height = max(height(oldRoot->left),height(oldRoot->right)) + 1;
    // update new root oldRoot's height
    newRoot->height = max(height(newRoot->left),height(newRoot->right)) + 1;

    return newRoot;
}

/*---------------- function to display the preorder traversal of AVL tree------------*/
void preorder(node_t* temp){
    if (temp == NULL) {
        printf("\\n ");
        return;
    }

    printf("%d ",temp->data);
    preorder(temp->left);
    preorder(temp->right);

}

/*---free the AVL nodes----*/
void freenode(node_t *p){
    if(p != NULL) {
        freenode(p->left);
        freenode(p->right);
        free(p);
    }
}


/* ----------------function to insert a node*---------------------------*/
/* Insert a node like a Binary search tree, then convert it into a AVL tree using four cases*/
node_t* Insert(node_t* root, int data)
{
    //insert your code here
    if (root == NULL)
        return NewNode(data);

    if (data > root->data) {
        root->right = Insert(root->right, data);
    } else {
        root->left = Insert(root->left, data);
    }

    /*updating the height after insertion of the node*/
    root->height = max(height(root->left),height(root->right)) + 1;

    /*checking the balance factor to check the tree is balanced */
    int balance = Balance(root);

    /* left- left case*/
    //        3
    //     2
    //  1
    if(balance > 1 && data < root->left->data)
        return RightRotate(root);

    /* Right Right Case*/
    //  1
    //     2
    //        3
    if(balance < -1 && data > root->right->data)
        return LeftRotate(root);

    /*Left Right Case*/
    //        3
    //     1
    //        2
    if(balance > 1 && data > root->left->data)
    {
        // after left rotatet the root -> left, this becomes left-left case
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    /* Right Left Case*/
    //     1
    //         3
    //     2          
    if(balance < -1 && data < root->right->data)
    {
        // after right rotatet the root -> right, this becomes right-right case
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root;
}


/*------------------main program-------------------------------*/
int main() {
    Tree* T = initTree();
    int n, x, i;
    printf("Enter the number of elements:\n");
    scanf("%d", &n);
    printf("Enter the tree data\n");

    for(i = 0; i < n; i++) {
        scanf("%d", &x);
        T->root =  Insert(T->root, x);
    }
    printf("The output is:\n");
    preorder(T->root);

    freenode(T->root);
    free(T);
    return 0;
}
