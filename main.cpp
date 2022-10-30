#include <iostream>
#include <unordered_set>
#include <memory>

class Node {
  public:
    Node(char c, int openLeft, int closeLeft)
    : c(c)
    , openLeft(openLeft)
    , closeLeft(closeLeft)
    {}

    const char c = 0;
    const int openLeft = 0;
    const int closeLeft = 0;

    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
};


void makeTree(std::unique_ptr<Node>& root) {
    if (root->openLeft > 0) {
        auto newLeftNode = std::make_unique<Node>('(',
                                                  root->openLeft - 1,
                                                  root->closeLeft + 1);
        root->left = std::move(newLeftNode);
        makeTree(root->left);
    }
    if (root->closeLeft > 0) {
        auto newRightNode = std::make_unique<Node>(')',
                                                  root->openLeft,
                                                  root->closeLeft - 1);
        root->right = std::move(newRightNode);
        makeTree(root->right);
    }

}

bool viewTree(std::unique_ptr<Node>& root)
{
    std::cout << root->c;
    if (root->left) {
        if (!viewTree(root->left)) {
            root->left.reset();
        }
    } else if (root->right) {
        if (!viewTree(root->right)) {
            root->right.reset();
        }
    }
    return (root->left != nullptr || root->right != nullptr);
}

int main() {
    int size = 0;
    std::cin >> size;

    std::unique_ptr<Node> root;

    if (size <= 0) {
        return 0;
    } else {
        root = std::make_unique<Node>('(', size - 1, 1);
    }

    makeTree(root);
    while (viewTree(root)) {
        std::cout << '\n';
    }
    std::cout.flush();

    return 0;
}