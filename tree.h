struct Leaf {
  char* name;
  char* data;
  struct Leaf* left;
  struct Leaf* right;
};
typedef struct Leaf Leaf;

struct Tree {
  Leaf* root;
  unsigned int count;
};
typedef struct Tree Tree;

void init_tree(Tree* tree) {
  tree->count = 0;
}

void add_leaf(Leaf* leaf, Leaf* new_leaf) {
  int names_equality = strcmp(leaf->name, new_leaf->name);
  if(names_equality == 0) {
    leaf->data = new_leaf->data;
  }

  else if (names_equality > 0) {
    if(leaf->right) {
      add_leaf(leaf->right, new_leaf);
    } else {
      leaf->right = new_leaf;
    }
  }

  else if (leaf->left) {
    add_leaf(leaf->left, new_leaf);
  }

  else {
    leaf->left = new_leaf;
  }

}

void add_to_tree(Tree* tree, Leaf* leaf) {
  if(!tree->root) {
    tree->root = leaf;
  }

  else {
    add_leaf(tree->root, leaf);
  }
}

void set(Tree* tree, char* name, char* data) {
  Leaf* leaf = malloc(sizeof(Leaf));
  leaf->name = name;
  leaf->data = data;
  leaf->right = NULL;
  leaf->left = NULL;
  add_to_tree(tree, leaf);
}

char* get_leaf(Leaf* leaf, char* name) {
  int names_equality = strcmp(leaf->name, name);

  if(names_equality == 0) {
    return leaf->data;
  }

  else if (names_equality > 0 && leaf->right) {
    return get_leaf(leaf->right, name);
  }

  else if (leaf->left) {
    return get_leaf(leaf->left, name);
  }

  return NULL;
}

char* get(Tree* tree, char* name) {
  if(tree->root) {
    return get_leaf(tree->root, name);
  }

  return NULL;
}

void clear_leaf(Leaf* leaf) {
  if(leaf->left) clear_leaf(leaf->left);
  if(leaf->right) clear_leaf(leaf->right);
  free(leaf);
}

void clear_tree(Tree* tree) {
  if(tree->root) clear_leaf(tree->root);
}

