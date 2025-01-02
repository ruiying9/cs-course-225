/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    Node* & nodef = find(root, key);
    if (nodef) {
        return nodef->value;
    }
    return V();
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    if (subtree == nullptr || subtree->key == key) {
        return subtree;
    } else if (subtree->key > key) {
        return find(subtree->left, key);
    } else {
        return find(subtree->right, key);
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    insert(root,key,value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if (!subtree) {
        subtree = new Node(key, value);
    } else if (key < subtree->key) {
        insert(subtree->left, key, value);
    } else if (key > subtree->key) {
        insert(subtree->right, key, value);
    }
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    std::swap(first->key, second->key);
    std::swap(first->value, second->value);
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    remove(root,key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    if (!subtree) {
        return;
    } else if (key==subtree->key){
        Node** node = &subtree;
        if ((*node)->left) {
            Node** next = &((*node)->left);
            if((*next)->right){
                while ((*next)->right) {
                    next = &((*next)->right);
                }
                swap(*node, *next);
                *next=nullptr;
                clear(*next);
            }else{
                swap(*node, *next);
                (*node)->left=(*next)->left; 
            }
        } else if ((*node)->right) {
            Node** next = &((*node)->right);
            if((*next)->right){
                while ((*next)->right) {
                    next = &((*next)->right);
                }
            } else{
                if((*next)->left){
                    while ((*next)->left) {
                        next = &((*next)->left);
                    }
                }
            }
            swap(*node, *next);
            *next=nullptr;
            clear(*next);
        } else {
            *node=nullptr;
            clear(*node);
        }
    } else if (key < subtree->key) {
        if(subtree->right){
            if(subtree->right->key==key){
                remove(subtree->right, key);
            }
        }
        remove(subtree->left, key);//false becuase for remove 1 child, after the first remove 9, 12-subtree->key>(key,10) but it should go right instead of left
    } else if (key > subtree->key) {
        remove(subtree->right, key);
    }
    //-----------------------
    // Node** node = &find(subtree, key); use find cause the problem that even though subtree's return is right but node is nullptr after the first remove
    // if (!*node) return;
    // if ((*node)->left && (*node)->right) {
    //     Node** next = &((*node)->left);
    //     while ((*next)->right) {
    //         next = &((*next)->right);
    //     }
    //     swap(*node, *next);
    //     *next=nullptr;
    //     clear(*next);
    // }else {
    //     if ((*node)->left) {
    //         Node** next = &((*node)->left);
    //         if((*next)->right){
    //             while ((*next)->right) {
    //                 next = &((*next)->right);
    //             }
    //         } else{
    //             if((*next)->left){
    //                 while ((*next)->left) {
    //                     next = &((*next)->left);
    //                 }
    //             }
    //         }
    //         swap(*node, *next);
    //         *next=nullptr;
    //         clear(*next);
    //     } else if ((*node)->right) {
    //         Node** next = &((*node)->right);
    //         if((*next)->right){
    //             while ((*next)->right) {
    //                 next = &((*next)->right);
    //             }
    //         } else{
    //             if((*next)->left){
    //                 while ((*next)->left) {
    //                     next = &((*next)->left);
    //                 }
    //             }
    //         }
    //         swap(*node, *next);
    //         *next=nullptr;
    //         clear(*next);
    //     } else {
    //         *node=nullptr;
    //         clear(*node);
    //     }
    // }
    // -------------------------
    // if (!subtree) {
    //     return;
    // } else if (key < subtree->key) {
    //     remove(subtree->left, key);
    // } else if (key > subtree->key) {
    //     remove(subtree->right, key);
    // } else {
    //     Node* node = subtree;
    //     if (node->left && node->right) {
    //         Node* next = node->left;
    //         while (next->right) {
    //             next = next->right;
    //         }
    //         swap(node, next);
    //         next=nullptr;
    //         clear(next);
    //     }else {
    //         if (node->left) {
    //             Node* next = node->left;
    //             if(next->right){
    //                 while (next->right) {
    //                     next = next->right;
    //                 }
    //             } else{
    //                 if(next->left){
    //                     while (next->left) {
    //                         next = next->left;
    //                     }
    //                 }
    //             }
    //             swap(node, next);
    //             next=nullptr;
    //             clear(next);
    //         } else if (node->right) {
    //             Node* next = node->right;
    //             if(next->right){
    //                 while (next->right) {
    //                     next = next->right;
    //                 }
    //             } else{
    //                 if(next->left){
    //                     while (next->left) {
    //                         next = next->left;
    //                     }
    //                 }
    //             }
    //             swap(node, next);
    //             next=nullptr;
    //             clear(next);
    //         } else {
    //             node=nullptr;
    //             clear(node);
    //         }
    //     }
        // -------------------------
        // if (subtree->left && subtree->right) {
        //     Node* next = subtree->left;
        //     while (next->right) {
        //         next = next->right;
        //     }
        //     swap(node, next);
        //     next=nullptr;
        //     clear(next);
        // } else {
        //     if (subtree->left) {
        //         Node* next = subtree->left;
        //         if(next->right){
        //             while (next->right) {
        //                 next = next->right;
        //             }
        //         } else{
        //             if(next->left){
        //                 while (next->left) {
        //                     next = next->left;
        //                 }
        //             }
        //         }
        //         swap(node, next);
        //         next=nullptr;
        //         clear(next);
        //     } else if (subtree->right) {
        //         Node* next = subtree->right;
        //         if(next->right){
        //             while (next->right) {
        //                 next = next->right;
        //             }
        //         } else{
        //             if(next->left){
        //                 while (next->left) {
        //                     next = next->left;
        //                 }
        //             }
        //         }
        //         swap(node, next);
        //         next=nullptr;
        //         clear(next);
        //     }
        // }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K, V> tree;
    for (std::pair<K, V> p : inList) {
        tree.insert(p.first, p.second);
    }
    return tree;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    std::vector<int> tree(inList.size());
    std::sort(inList.begin(), inList.end());
    int height;
    while (true) {
        BST<K, V> subtree;
        for (std::pair<K, V> element : inList) {
            subtree.insert(element.first, element.second);
        }
        height = subtree.height();
        tree[height]+=1;
        if (!std::next_permutation(inList.begin(), inList.end())) {
            break;
        }
    }
    return tree;
}