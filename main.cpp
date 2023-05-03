#include <iostream>
#include <fstream>
using namespace std;
ofstream f ("abce.out");
ifstream in ("abce.in");
struct node
{
    int key;
    node *left, *right;
};
node* node1;
int op,key,stop;
void Afisare6(node *r)
{
    if(r != NULL)
    {
        Afisare6(r->left);
        if(r->key>=key && r->key<=stop)
        f << r->key << " ";
        Afisare6(r->right);
    }
}
void Afisare(node *r)
{
    if(r != NULL)
    {
        Afisare(r->left);
        cout << r->key << " ";
        Afisare(r->right);
    }
}

node* zigRotation(node* x)
{
    node* y = x->left;
    x->left = y->right;
    y->right = x;
    return y;

}
node* zagRotation(node* x)
{
    node* y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}


node* splay(node* root, int key)
{
    if (root == NULL || root->key == key)
        return root;

    if (root->key > key) /// se duce in stanga
    {
        if (root->left == NULL) ///  e liber copilul , facem doar o rotatie ca sa ajunga noul copil parinte
            return root;
        if (root->left->key>key) /// mergem inca un copil mai jos si apelam recursiv de la nepot , facand o zig-zig rotation
        {
            root->left->left = splay(root->left->left, key);
            if(root->left->left!= NULL)
                root->left= zigRotation(root->left);
        }
        else if (root->left->key < key) /// mergem inca un copil mai jos si apelam recursiv de la nepot , facand o zig-zag rotation
        {
            root->left->right= splay(root->left->right, key);
            if (root->left->right != NULL)
                root->left = zagRotation(root->left);
        }
        if(root->left==NULL)
            return root;
        return zigRotation(root);

    }
    else /// se duce in dreapta
    {
        if (root->right == NULL) /// e liber copilul , facem doar o rotatie ca sa ajunga noul copil parinte
            return root;
        if (root->right->key > key) /// mergem inca un copil mai jos si apelam recursiv de la nepot , facand o zag-zig rotation
        {
            root->right->left=splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = zigRotation(root->right);
        }
        else if (root->right->key<key) /// mergem inca un copil mai jos si apelam recursiv de la nepot , facand o zag-zag rotation
        {
            root->right->right= splay(root->right->right, key);
            if(root->right->right!= NULL)
                root->right = zagRotation(root->right);
        }
        if(root->right == NULL)
            return root;
        return zagRotation(root);

    }
}


bool search1(node *root, int key)
{
    if(root==NULL)
        return false;
    if (root->key == key)
        return true;
    if(root->key>key)
        return search1(root->left,key);
    return search1(root->right,key);
}

struct node* deletion(struct node* root, int key)
{
    struct node* aux;
    if (root==NULL)
        return NULL;

    if(search1(root,key))/// daca valoarea e in tree
        root = splay(root, key);
    else
        return root;


    if (root->left==NULL)/// daca nu am copil stang
    {
        return root->right;
    }


    else /// daca am fiu stang, il duc in varf si inlocuiesc noul fiu drept cu fostul fiu drept, asa practic elimin vechiul varf
    {
        aux = root->right;
        root = splay(root->left, key);
        root->right = aux;
    }

    return root;
}

node* insert(node* root, int key)
{
    node* aux = new node;
    aux->key = key;
    aux->left = aux->right = NULL;

    if (root == NULL)
        return aux;

    root = splay(root, key);

    if (root->key == key)
        return root;

    if (root->key > key)
    {
        aux->right = root;
        aux->left = root->left;
        root->left = NULL;
    }
    else
    {
        aux->left = root;
        aux->right = root->right;
        root->right = NULL;
    }
    return aux;
}

int Smallest(node* root, int key)
{
    node* aux;

    if(search1(root,key))
        return key;
    root=insert(root,key);
    if(root->left==NULL)
    {
        node1=deletion(root,key);
        return 0;
    }
    aux=root->left;

    while(aux->right!=NULL)
        aux=aux->right;
    node1=deletion(root,key);
    return aux->key;

}

int Biggest(node* root,int key)
{
    node* aux;
    if(search1(root,key))
        return key;
    root=insert(root,key);
    if(root->right==NULL)
    {
        node1=deletion(root,key);
        return 0;
    }
    aux=root->right;

    while(aux->left)
        aux=aux->left;
    node1=deletion(root,key);
    return aux->key;
}


int main()
{
    node* root = NULL;
//    root = insert(root, 100);
//    root = insert(root, 50);
//    root = insert(root, 200);
//    root = insert(root, 40);
//    root = insert(root, 60);
//    root = insert(root, 312);
//    root = insert(root, 10);
//    root = insert(root, 502);
//    root = insert(root, 21200);
//    root = insert(root, 403);
//    root = insert(root, 6);
//    root = insert(root, 32);


//    cout << "Inorder traversal of the modified Splay tree: \n";
//    Afisare(root);
//    cout<<endl; root=deletion(root,100);
//    root=deletion(root,50);
//    root=deletion(root,10);
//    root=deletion(root,10);
    node1=root;
//    cout<<endl<<Smallest(node1,55)<<endl;
//    cout<<Smallest(node1,4)<<endl;
//    cout<<Smallest(node1,3)<<endl;
//    cout<<Smallest(node1,78)<<endl;
//    cout<<Smallest(node1,15)<<endl;
//    cout<<Smallest(node1,50)<<endl;
//    cout<<Smallest(node1,784)<<endl;
//    cout<<Biggest(node1,10)<<endl;
//    cout<<Biggest(node1,101)<<endl;
//    cout<<Biggest(node1,2440)<<endl;

    int q;
    in>>q;
    for(int i=0;i<q;++i)
    {
        in>>op>>key;
        if(op==1)
        {
            node1 = insert(node1, key);
        }
         if(op==2)
        {
            node1=deletion(node1,key);
        }
         if(op==3)
        {
            f<<search1(node1,key)<<endl;
        }
         if(op==4)
        {
            f<<Smallest(node1,key)<<endl;
        }
         if(op==5)
        {
            f<<Biggest(node1,key)<<endl;
        }
         if(op==6)
        {
            in>>stop;
            Afisare6(node1);
            f<<endl;

        }

    }
     //Afisare(node1);
    return 0;
}
