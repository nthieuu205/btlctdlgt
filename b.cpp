#include"bits/stdc++.h"
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    bool red;
    bool blue;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr), red(false), blue(false) {}
};

class BinaryTree {
public:
    TreeNode* root;
    BinaryTree(int rootValue) {
        root = new TreeNode(rootValue);
    }

    void addNode(int parentValue, int childValue, bool isLeft) {
        TreeNode* parent = findNode(root, parentValue);
        if (parent != nullptr) {
            if (isLeft) {
                parent->left = new TreeNode(childValue);
            } else {
                parent->right = new TreeNode(childValue);
            }
        }
    }

    TreeNode* findNode(TreeNode* node, int value) {
        if (node == nullptr) return nullptr;
        if (node->val == value) return node;
        TreeNode* leftResult = findNode(node->left, value);
        if (leftResult != nullptr) return leftResult;
        return findNode(node->right, value);
    }

    bool canSecondPlayerWin(int x, int y, int n) {
        TreeNode* firstNode = findNode(root, x);
        TreeNode* secondNode = findNode(root, y);

        firstNode->red = true;
        secondNode->blue = true;

        int redCount = 1, blueCount = 1;
        while (true) {
            bool redMove = makeMove(firstNode, true);
            bool blueMove = makeMove(secondNode, false);
            if (!redMove && !blueMove) break;

            if (redMove) redCount++;
            if (blueMove) blueCount++;
        }

        return blueCount > redCount;
    }

private:
    bool makeMove(TreeNode* node, bool isRed) {
        queue<TreeNode*> q;
        q.push(node);
        while (!q.empty()) {
            TreeNode* current = q.front();
            q.pop();
            if (isRed && !current->red) continue;
            if (!isRed && !current->blue) continue;

            if (current->left != nullptr && !current->left->red && !current->left->blue) {
                if (isRed) current->left->red = true;
                else current->left->blue = true;
                return true;
            }

            if (current->right != nullptr && !current->right->red && !current->right->blue) {
                if (isRed) current->right->red = true;
                else current->right->blue = true;
                return true;
            }

            if (current == root) continue;

            if (root->left != nullptr && root->left == current && !root->red && !root->blue) {
                if (isRed) root->red = true;
                else root->blue = true;
                return true;
            }

            if (root->right != nullptr && root->right == current && !root->red && !root->blue) {
                if (isRed) root->red = true;
                else root->blue = true;
                return true;
            }

            if (current->left != nullptr) q.push(current->left);
            if (current->right != nullptr) q.push(current->right);
        }
        return false;
    }
};

int main() {
    int n = 11; // Số nút trên cây
    BinaryTree tree(1);
    tree.addNode(1, 2, true);
    tree.addNode(1, 3, false);
    tree.addNode(2, 4, true);
    tree.addNode(2, 5, false);
    tree.addNode(3, 6, true);
    tree.addNode(3, 7, false);
    tree.addNode(4, 8, true);
    tree.addNode(4, 9, false);
    tree.addNode(5, 10, true);
    tree.addNode(5, 11, false);

    int x = 3; // Đấu thủ 1 chọn nút x
    int y = 2; // Đấu thủ 2 chọn nút y
    if (tree.canSecondPlayerWin(x, y, n)) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }

    return 0;
}
