#ifndef TREE_H
#define TREE_H
#include <string>

class Node  
{  
  public: 
    int key;
    Node *left;
    Node *right;
    int height;
};

class AVLTree {
  Node* root;

  Node* createNode(const int key);
  Node* insertHelper(Node* selectedNode, int key);
  int get_height(Node* node);
  
  Node *rotateRight(Node *L0);
  Node *rotateLeft(Node *L0);
  
  std::string to_string_helper(Node* n, int level);
  
  std::string get_L_L_helper(Node* n);
  std::string get_L_R_helper(Node* n);
  std::string get_R_L_helper(Node* n);
  std::string get_R_R_helper(Node* n);

public:
  int nodes_added;
  int nodes_visited;
  int rotaions_performed;

  AVLTree();
  ~AVLTree();
  
  int get_max();
  int get_min();
  std::string string();
  std::string get_L_L();
  std::string get_L_R();
  std::string get_R_L();
  std::string get_R_R();

  bool insert(const int value);
  bool lookup(const int value) const;
  void stat_reset();
};

#endif
