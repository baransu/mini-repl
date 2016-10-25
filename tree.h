struct Leaf {
  char* name;
  double value;
  struct Leaf* left;
  struct Leaf* right;
};
typedef struct Leaf Leaf;

struct Tree {
  Leaf* root;
};
typedef struct Tree Tree;

void init_tree(Tree* tree) {
  tree->root = 0;
}

void add_leaf(Leaf** leaf, char* name, double value) {

  if(*leaf == 0) {
    *leaf = (Leaf*) malloc(sizeof( struct Leaf ));
    (*leaf)->name = malloc(64);
    strcpy((*leaf)->name, name);
    (*leaf)->value = value;
    (*leaf)->left = 0;
    (*leaf)->right = 0;
  } else {
    int names_equality = strcmp(name, (*leaf)->name);

    if(names_equality == 0) {
      (*leaf)->value = value;
    }

    else if (names_equality > 0) {
      add_leaf(&(*leaf)->right, name, value);
    }

    else {
      add_leaf(&(*leaf)->left, name, value);
    }
  }

}


void set(Tree* tree, char* name, double value) {
  add_leaf(&tree->root, name, value);
}

double get_leaf(Leaf* leaf, char* name) {
  if(leaf != 0) {
    int names_equality = strcmp(name, leaf->name);
    if(names_equality == 0) {
      return leaf->value;
    }

    else if (names_equality > 0 && leaf->right != 0) {
      return get_leaf(leaf->right, name);
    }

    else if (leaf->left != 0) {
      return get_leaf(leaf->left, name);
    }

  }

  return 0;
}

double get(Tree* tree, char* name) {

  if(tree->root != 0) {
    return get_leaf(tree->root, name);
  }

  return 0;
}

void clear_leaf(Leaf* leaf) {
  if(leaf->left != 0) clear_leaf(leaf->left);
  if(leaf->right != 0) clear_leaf(leaf->right);
  free(leaf->name);
  free(leaf);
}

void clear_tree(Tree* tree) {
  if(tree->root != 0) clear_leaf(tree->root);
}

void print_leaf(Leaf* leaf, char* parent) {
  if(leaf)
    printf("parent: %s | name: %s | value: %f\n", parent, leaf->name, leaf->value);

  if(leaf->left != 0)
    print_leaf(leaf->left, leaf->name);

  if(leaf->right != 0)
    print_leaf(leaf->right, leaf->name);
}

void print_tree(Tree* tree) {
  if(tree->root != 0) {
    print_leaf(tree->root, "tree");
  }

  else {
    printf("Tree root is NULL\n");
  }
}

