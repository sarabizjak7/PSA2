// Naloga 3: Izstevanka
// Sara Bizjak, 27161075
// Matematika, PSA2


#include <iostream>
#include <climits>
#include <vector>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

struct Node {
    int data;
    Node *left, *right;
    int height;
    int size;
    int flag; // flag = 0, če zbrisan; 1, če ni
};

///

Node* newNode(int key) {
    Node* node = new Node;
    node->data = key;
    node->left = node->right = nullptr;
    node->height = 1;
    node->flag = 1;
    node->size = 1;
    return node;
}

///

void inorder(Node* root) {
    if (root == nullptr)
        return;

    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

///

int height(Node* root) {
    if (root == NULL) {
        return 0;
    } else {
        return root->height;
    }
}

///

Node* findMin(Node* root) {
    if (root == NULL) {
        return NULL;
    }
    else if(root->left == NULL) {
        return root;
    }
    else {
        return findMin(root->left);
    }
}

///

int sizeFromNode(Node* node) {
	return node != nullptr ? node->size : 0;
}

////////////////////////////////////////////////////////////////////////////////

// ROTACIJE

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;

    y->left = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    x->size = sizeFromNode(x->left) + sizeFromNode(x->right) + x->flag;
    y->height = max(height(y->left), height(y->right)) + 1;
    y->size = sizeFromNode(y->left) + sizeFromNode(y->right) + y->flag;

    return x;
}

///

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y-> left;

    y->left = x;

    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    x->size = sizeFromNode(x->left) + sizeFromNode(x->right) + x->flag;
    y->height = max(height(y->left), height(y->right)) + 1;
    y->size = sizeFromNode(y->left) + sizeFromNode(y->right) + y->flag;

    return y;
}

///

Node* doubleLeftRotate(Node* t) {
    t->right = rightRotate(t->right);
    t->size = sizeFromNode(t->left) + sizeFromNode(t->right) + t->flag;
    return leftRotate(t);
}

///

Node* doubleRightRotate(Node* t) {
    t->left = leftRotate(t->left);
    t->size = sizeFromNode(t->left) + sizeFromNode(t->right) + t->flag;
		return rightRotate(t);
}

///

int getBalance(Node *root) {
    if (root == NULL) {
        return 0;
    }
    else {
        return (height(root->left) - height(root->right));
    }
}

////////////////////////////////////////////////////////////////////////////////

int remove(Node* root, int key) {
    Node* temp;
    if (root == NULL) {
        return 0;
    }
    else if (key == root->data) {
	      const int old_flag = root->flag;
        root->flag = 0;
	      root->size -= old_flag;
	      return old_flag;
    }
    else if (key < root->data) {
        int res = remove(root->left, key);
	      root->size -= res;
	      return res;
    }
    else if (key > root->data) {
        int res = remove(root->right, key);
	      root->size -= res;
	      return res;
    }
}

///

int kthSmallest(Node* root, int k) {
    if (root == nullptr) {
        return INT_MAX;
    }

    if (k-1 == sizeFromNode(root->left) && root->flag == 1) {
        return root->data;
    }
    else if (root->left != nullptr && root->left->size >= k) {
        return kthSmallest(root->left, k);
    }
    else {
	      const int leftSize = root->left != nullptr ? root->left->size : 0;
        return kthSmallest(root->right, k - leftSize - root->flag);
    }
}

///

int max(int a, int b);

int max(int a, int b) {
    return (a > b) ? a : b;
}

///

Node* insert(Node* t, int key) {
  	if (t == NULL) {
  		  t = newNode(key);
  	}
  	else if (key < t->data) {
    		t->left = insert(t->left, key);
    		if (height(t->left) - height(t->right) == 2) {
      			if (key < t->left->data) {
      				  t = rightRotate(t);
      			}
    			  else {
    				    t = doubleRightRotate(t);
    			  }
    		}
  	}
  	else if(key > t->data) {
  		  t->right = insert(t->right, key);
  		  if (height(t->right) - height(t->left) == 2) {
  			     if (key > t->right->data) {
  				       t = leftRotate(t);
  			     }
  			     else {
  				       t = doubleLeftRotate(t);
  			     }
  		  }
  	}
    else if (key == t->data && t->flag == 0) {
		    t->flag = 1;
	  }
	  t->size = sizeFromNode(t->left) + sizeFromNode(t->right) + t->flag;
	  t->height = max(height(t->left), height(t->right)) + 1;
  	return t;
}

int getSize(Node* root) {
	return root == nullptr ? 0 : root->flag + getSize(root->left) + getSize(root->right);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

const int M = 1000000001;

int main() {

	// vhodni podatki
	/*
	N: stevilo dogodkov
	+: prihod otroka (tip)
	-: odhod otroka (tip)
	x: stevilo
	tip je od stevila x locen s presledkom

	visina novega igralca: (x + visina_zadnje_izlocenega_otroka) mod 1000000001
	pred prvim izlocanjem predpostavimo, da je visina zadnje izlocenega otroka enaka 0
	*/

    int prejsnja_visina = 0;

    Node* root = nullptr;

    int N;
    int x;
    char znak;

    scanf(" %d", &N);

    for (int i = 0; i < N; ++i) {
        scanf(" %c %d", &znak, &x);

        x = (x + prejsnja_visina) % M;

        if (znak == '+') {
            root = insert(root, x);
        }
        else {
            prejsnja_visina = kthSmallest(root, x);
            remove(root, prejsnja_visina);
            cout << prejsnja_visina << endl;
        }
    }
    return 0;
}
