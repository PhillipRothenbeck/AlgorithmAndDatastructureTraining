// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <iostream>
#include <stack>

using namespace std;

struct Binary_Tree_Node {
    int data;
    Binary_Tree_Node *left;
    Binary_Tree_Node *right;
};

/************** begin assignment **************/
// Implement a function to check if a binary tree is a binary search tree (BST).
// A binary search tree satisfies the condition:
// left->data <= current->data < right->data.
// More precisely, the condition is that all left nodes must be less than or
// equal to the current node, which must be less than all the right nodes.
//
// Let's state again clearly the properties for a binary search tree:
// - The left subtree of a node contains only nodes with keys lesser than the
//   node's key.
// - The right subtree of a node contains only nodes with keys greater than the
//   node's key.
// - The left and right subtree each must also be a binary search tree.
//
// Be careful with duplicate values:
//    20                  20
//   /    valid BST         \    invalid BST
// 20                       20
//
// Optimal: O(n) time, if binary tree is balanced O(log n) space,
// worst case O(n) space
// --> It's challenging to do it optimal although there is not much code ...
// Try to solve it somehow.
//
// Before you start coding the function "is_binary_search_tree", write test
// cases in the main function to test the "is_binary_search_tree" function.
// Start with simple tests (like nullptr, one node, two nodes, three nodes)
// before writing more complicated tests.
// The style of writing tests before actual coding is called "Test-driven
// development" (TDD). You have indirectly familiarized yourself with it in the
// first exercises of this course, now you can try TDD yourself.
// (If you need an idea how to start writing tests, take a look at the main
// function in "is_symmetric.cpp".)

// write a helper function if you need to
// TODO: write code here

int get_max(const Binary_Tree_Node *node) {
    int left_max = get_max(node->left);
    int right_max = get_max(node->right);
    return max(node->data, max(left_max, right_max));
}

int get_min(const Binary_Tree_Node *node) {
    int left_min = get_min(node->left);
    int right_min = get_min(node->right);
    return min(node->data, min(left_min, right_min));
}

bool is_binary_search_tree(const Binary_Tree_Node *node) {
    // TODO: write code here
    std::cout << node->data << std::endl;
    if (node == nullptr) return true;

    if (node->left != nullptr & get_max(node->left) > node->data) return false;

    std::cout << "left tree is ok" << std::endl;

    if (node->right != nullptr & get_min(node->right) < node->data) return false;

    std::cout << "right tree is ok" << std::endl;

    if (!is_binary_search_tree(node->left) | !is_binary_search_tree(node->left)) return false;

    return true;
}

int main() {
    // TODO: Thoroughly test function "is_binary_search_tree"
    // (include also duplicate values in the tests).
    {
        std::cout << "test 1" << std::endl;
        Binary_Tree_Node *root = nullptr;
        assert(is_binary_search_tree(root) == false);
    }
    {
        std::cout << "test 2" << std::endl;
        Binary_Tree_Node root = {1, nullptr, nullptr};
        assert(is_binary_search_tree(&root) == true);
    }
    {
        std::cout << "test 3" << std::endl;
        Binary_Tree_Node node1 = {1, nullptr, nullptr};
        Binary_Tree_Node root = {2, &node1, nullptr};
        assert(is_binary_search_tree(&root) == true);
    }
    {
        std::cout << "test 4" << std::endl;
        Binary_Tree_Node node1 = {3, nullptr, nullptr};
        Binary_Tree_Node root = {2, &node1, nullptr};
        assert(is_binary_search_tree(&root) == false);
    }
    {
        std::cout << "test 5" << std::endl;
        Binary_Tree_Node node1 = {2, nullptr, nullptr};
        Binary_Tree_Node root = {1, nullptr, &node1};
        assert(is_binary_search_tree(&root) == true);
    }
    {
        std::cout << "test 6" << std::endl;
        Binary_Tree_Node node5 = {5, nullptr, nullptr};
        Binary_Tree_Node node4 = {1, nullptr, nullptr};
        Binary_Tree_Node node3 = {2, nullptr, nullptr};
        Binary_Tree_Node node2 = {3, &node4, &node3};
        Binary_Tree_Node root = {4, &node2, &node5};
        assert(is_binary_search_tree(&root) == false);
    }
    {
        std::cout << "test 7" << std::endl;
        Binary_Tree_Node node5 = {5, nullptr, nullptr};
        Binary_Tree_Node node4 = {1, nullptr, nullptr};
        Binary_Tree_Node node2 = {3, nullptr, nullptr};
        Binary_Tree_Node node3 = {2, &node4, &node2};
        Binary_Tree_Node root = {4, &node3, &node5};
        assert(is_binary_search_tree(&root) == true);
    }
    {
        std::cout << "test 8" << std::endl;
        Binary_Tree_Node node5 = {5, nullptr, nullptr};
        Binary_Tree_Node node4 = {1, nullptr, nullptr};
        Binary_Tree_Node node2 = {5, nullptr, nullptr};
        Binary_Tree_Node node3 = {2, &node4, &node2};
        Binary_Tree_Node root = {4, &node3, &node5};
        assert(is_binary_search_tree(&root) == false);
    }
    std::cout << "all tests passed" << std::endl;
}

/*************** end assignment ***************/
