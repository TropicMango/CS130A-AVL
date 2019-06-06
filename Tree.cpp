#include "Tree.h"
#include <cstddef>
#include <iostream>

Node* AVLTree::createNode(const int key) {
  Node* node = new Node(); 
  node->key = key;  
  node->left = NULL;  
  node->right = NULL;  
  node->height = 1; // 1 step to NULL
  return(node);  
}

AVLTree::AVLTree() {
  root = NULL;
  nodes_added = 0;
  nodes_visited = 0;
  rotaions_performed = 0;
}

AVLTree::~AVLTree() {
  destroy_helper(root);
}

int AVLTree::get_height(Node* node) {
  return (node != NULL) ? node->height : 0;
}

Node* AVLTree::rotateRight(Node *L0) {
  Node *L1 = L0->left;  
  Node *L2 = L1->right;  
  
  L1->right = L0;  
  L0->left = L2;  
  
  int L0_height_L = get_height(L0->left);
  int L0_height_R = get_height(L0->right);
  int L0_height = (L0_height_L > L0_height_R) ? L0_height_L : L0_height_R;
  L0->height = L0_height + 1;  
  
  int L1_height_L = get_height(L1->left);
  int L1_height_R = get_height(L1->right);
  int L1_height = (L1_height_L > L1_height_R) ? L1_height_L : L1_height_R;
  L1->height = L1_height + 1;  
  
  rotaions_performed++;
  return L1;  
}  

Node* AVLTree::rotateLeft(Node *L0)  
{  
  Node *L1 = L0->right;  
  Node *L2 = L1->left;  
  
  L1->left = L0;  
  L0->right = L2;  
  
  int L0_height_L = get_height(L0->left);
  int L0_height_R = get_height(L0->right);
  int L0_height = (L0_height_L > L0_height_R) ? L0_height_L : L0_height_R;
  L0->height = L0_height + 1;  
  
  int L1_height_L = get_height(L1->left);
  int L1_height_R = get_height(L1->right);
  int L1_height = (L1_height_L > L1_height_R) ? L1_height_L : L1_height_R;
  L1->height = L1_height + 1;  
  
  rotaions_performed++;
  return L1;  
}  

Node* AVLTree::insertHelper(Node* node, int value) {
  
  // if empty we are able to place the new node in
  // return statement only returns the root of the selected node
  if (node == NULL)
    return(createNode(value));
    
  nodes_visited++;
  
  if (value < node->key)  // if smaller goes on the left side
    node->left = insertHelper(node->left, value);  
  else if (value > node->key)  // if bigger goes on the right side
    node->right = insertHelper(node->right, value);  
  else // if equal.... we can't have this
    throw value;
    
  // after insertion we update the height
  int leftH = get_height(node->left);
  int rightH = get_height(node->right);
  int highest = (leftH > rightH) ? leftH : rightH;
  node->height = 1 + highest;
  
  // using updated height we balance the tree
  
  int tilt = 0;
  if(node != NULL)
  	tilt = get_height(node->left) - get_height(node->right);
  
  // left left
  if (tilt > 1 && value < node->left->key)  
	return rotateRight(node); 
	
  // right right  
  if (tilt < -1 && value > node->right->key)  
    return rotateLeft(node);   
    
  // left right  
  if (tilt > 1 && value > node->left->key) {  
    node->left = rotateLeft(node->left);  
    return rotateRight(node);  
  }  
  
  // right left
  if (tilt < -1 && value < node->right->key) {  
    node->right = rotateRight(node->right);  
    return rotateLeft(node);  
  }  
  
  /* return the (unchanged) node pointer */
  return node;  
}

bool AVLTree::insert(const int value) {
  try {
	root = insertHelper(root, value);
  } catch(int v) {
  	return false;
  }
  nodes_added++;
  return true;
}

bool AVLTree::lookup(const int value) {
  Node* n = root;
  
  while(n != NULL){
    nodes_visited++;
  	if(n->key > value){
  	  n = n->left;
  	} else if(n->key < value){
  	  n = n->right;
  	} else {
  	  return true;
  	}
  }
  return false;
}

void AVLTree::stat_reset() {
  nodes_added = 0;
  rotaions_performed = 0;
  nodes_visited = 0;
}

int AVLTree::get_max() {
  Node* n = root;
  while(n->right != NULL){
	n = n->right;
  }
  return n->key;
}

int AVLTree::get_min() {
  Node* n = root;
  while(n->left != NULL){
	n = n->left;
  }
  return n->key;
}

std::string AVLTree::to_string_helper(Node* n, int level) {
  std::string r = "";
  
  for(int i=0; i<level; i++) {
  	 r += "  ";
  }
  if(n == NULL) {
    r += "Null\n";
    return r;
  }
  
  if(n->left != NULL || n->right != NULL) {
  	r += "Node(" + std::to_string(n->key);
  	r += ", h=" + std::to_string(n->height - 1) + "):\n"; 
  	r += to_string_helper(n->left, level + 1) ;
  	r += to_string_helper(n->right, level + 1);
  } else {
    r += "Leaf(" + std::to_string(n->key) + ")\n";
  }
  
  return r;
}

std::string AVLTree::string() {
  std::string r = to_string_helper(root, 0);
  return r;
}

std::string AVLTree::get_L_L() { 
  std::string r = "";
  r += "The following inserts would cause a left-left rotation:\n";
  r += get_L_L_helper(root, -2147483648);
  r = r.substr(0, r.length() - 2);
  r += "\n";
  return r; // gets rid of the extra comma at the end
}

std::string AVLTree::get_L_L_helper(Node* n, int lower_bound) {
  std::string r = "";
  
  if(n == NULL)
    return r;
  if(n->left == NULL)
    return get_L_L_helper(n->right, n->key);
  
    
  int tilt = get_height(n->left) - get_height(n->right);
  int L_tilt = get_height(n->left->left) - get_height(n->left->right);
  
  if (tilt > 0 && L_tilt <= 0) { // left heavy and the left is not left heavy
    int lower = lower_bound + 1;
    int upper = n->left->key - 1;
    if(lower != upper)
      r += std::to_string(lower) + " to " + std::to_string(upper) + ", ";
    else
      r += std::to_string(lower) + ", ";
  } else {
    r += get_L_L_helper(n->left, lower_bound);
  }
  
  r += get_L_L_helper(n->right, n->key);
  return  r;
}

std::string AVLTree::get_L_R() { 
  std::string r = "";
  r += "The following inserts would cause a left-right rotation:\n";
  r += get_L_R_helper(root);
  r = r.substr(0, r.length() - 2);
  r += "\n";
  return r; // gets rid of the extra comma at the end
}

std::string AVLTree::get_L_R_helper(Node* n) {
  std::string r = "";
  
  if(n == NULL)
    return r;
  if(n->left == NULL)
    return get_L_R_helper(n->right);
  
    
  int tilt = get_height(n->left) - get_height(n->right);
  int L_tilt = get_height(n->left->left) - get_height(n->left->right);
  
  if (tilt > 0 && L_tilt >= 0) { // left heavy and the left is not right heavy
    int lower = n->left->key + 1;
    int upper = n->key - 1;
    if(lower != upper)
      r += std::to_string(lower) + " to " + std::to_string(upper) + ", ";
    else
      r += std::to_string(lower) + ", ";
  } else {
    r += get_L_R_helper(n->left);
  }
  
  r += get_L_R_helper(n->right);
  return  r;
}

std::string AVLTree::get_R_L() { 
  std::string r = "";
  r += "The following inserts would cause a right-left rotation:\n";
  r += get_R_L_helper(root);
  r = r.substr(0, r.length() - 2);
  r += "\n";
  return r; // gets rid of the extra comma at the end
}

std::string AVLTree::get_R_L_helper(Node* n) {
  std::string r = "";
  
  if(n == NULL)
    return r;
  if(n->right == NULL)
    return get_R_L_helper(n->left);
  
  r += get_R_L_helper(n->left);
    
  int tilt = get_height(n->left) - get_height(n->right);
  int R_tilt = get_height(n->right->left) - get_height(n->right->right);
  if (tilt < 0 && R_tilt >= 0) { // right heavy and right is not left heavy
      int lower = n->key + 1;
      int upper = n->right->key - 1;
      if(lower != upper)
        r += std::to_string(lower) + " to " + std::to_string(upper) + ", ";
      else
        r += std::to_string(lower) + ", ";
  } else {
      r += get_R_L_helper(n->right);
  }
  return  r;
}

std::string AVLTree::get_R_R() { 
  std::string r = "";
  r += "The following inserts would cause a right-right rotation:\n";
  r += get_R_R_helper(root, 2147483647);
  r = r.substr(0, r.length() - 2);
  r += "\n";
  return r; // gets rid of the extra comma at the end
}

std::string AVLTree::get_R_R_helper(Node* n, int upper_bound) {
  std::string r = "";
  
  if(n == NULL)
    return r;
  if(n->right == NULL)
    return get_R_R_helper(n->left, upper_bound);
  
  r += get_R_R_helper(n->left, n->key);
    
  int tilt = get_height(n->left) - get_height(n->right);
  int R_tilt = get_height(n->right->left) - get_height(n->right->right);
  if (tilt < 0 && R_tilt >= 0) { // right heavy and right is not right heavy
      int lower = n->right->key + 1;
      int upper = upper_bound - 1;
      if(lower != upper)
        r += std::to_string(lower) + " to " + std::to_string(upper) + ", ";
      else
        r += std::to_string(lower) + ", ";
  } else {
      r += get_R_R_helper(n->right, n->key);
  }
  return  r;
}

void AVLTree::destroy_helper(Node* n) {
  if(n == NULL)
    return;
  destroy_helper(n->left);
  destroy_helper(n->right);
  delete(n);
}