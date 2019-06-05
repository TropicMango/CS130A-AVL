#include "Tree.h"
#include <fstream>
#include <iostream>
using namespace std;

bool strstart(string str, string targetstr) {
  return str.substr(0, targetstr.length()) == targetstr;
}

int main(int argc, char** argv) {
  if(argc < 1) exit(0);
  
  AVLTree main_tree;
  
  string readfile = argv[1];
  // Insert lines from storefile
  ifstream store(readfile);
  if(store.fail()) {
    cerr << "Unable to open file: " << readfile << '\n';
    exit(1);
  }

  string line;
  while(getline(store, line)) {
    
    if(strstart(line, "#")) {
    
    } else if(strstart(line, "insert")) {
      string mod_string = line.substr(7, line.length());
      // by using 7 we clear out the "insert ", for easier splice
      
      int pos = mod_string.find(' ');
      int i = 0;
      string chunk;
      
      while(true){
        pos = mod_string.find(' ');
        chunk = mod_string.substr(0, pos);
      	main_tree.insert(stoi(chunk)); 
      	
      	i++;
      	mod_string.erase(0, pos + 1);
      	if(pos == int(string::npos)) break;
      }
      
      cout << "Added " << main_tree.nodes_added << " of " << i << " nodes.\n";
      float NV = main_tree.nodes_visited;
      cout << "Visited " << NV << " (" << NV/i << ") nodes and performed ";
      float RP = main_tree.rotaions_performed;
      cout << RP << " (" << RP/i << ") rotations.\n";
      main_tree.stat_reset();
      
    } else if(strstart(line, "lookup")) {
      cout << "lookup" << '\n';
      
    } else if(strstart(line, "print")) {
      string mod_string = line.substr(6, line.length());
      if(strstart(mod_string, "tree")) {
        cout << main_tree.string();
      } else if(strstart(mod_string, "left-left")) {
        cout << main_tree.get_L_L();
      } else if(strstart(mod_string, "left-right")) {
        cout << main_tree.get_L_R();
      } else if(strstart(mod_string, "right-left")) {
        cout << main_tree.get_R_L();
      } else if(strstart(mod_string, "right-right")) {
        cout << main_tree.get_R_R();
      }
    }
    cout << '\n';
  }

  cout << '\n';
  store.close();
}