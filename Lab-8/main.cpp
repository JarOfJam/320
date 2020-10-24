//Jordan Welch - Cosc 320 - Lab 8 - 10/31/19

#include <iostream>
#include <iomanip>
#include <chrono>

struct TreeNode {
        int key;
        TreeNode* left;
        TreeNode* right;
	TreeNode* parent;
	TreeNode() {
		left = NULL;
		right = NULL;
		parent = NULL;
		key = 0;
	}
	TreeNode(int n) {
		left = NULL;
		right = NULL;
		parent = NULL;
		key = n;
	}
};

class BinaryTree {
	private:
		TreeNode* root;
		void transplant(TreeNode*, TreeNode*);
	public:
		void insert(int);
		TreeNode* searchCall(int);
		TreeNode* search(TreeNode*, int);
		TreeNode* minimum();
		TreeNode* maximum();
		TreeNode* successor();
		void inorderCall();
		void inorder(TreeNode*);
		void Delete(int);
		void printCall();
		void print(TreeNode*);
		BinaryTree(int n);
};

int main() {
	BinaryTree a(1337);
	a.insert(420);
	a.insert(6969);
	a.insert(69);
	TreeNode* min = a.minimum();
	TreeNode* max = a.maximum();
	TreeNode* s = a.searchCall(69);
	TreeNode* succ = a.successor();
	if(s->key == 69) {
		std::cout << s->key << " found in search" << std::endl;
	}
	std::cout << "Min: " << min->key << std::endl;
	std::cout << "Max: " << max->key << std::endl;
	std::cout << "Successor: " << succ->key << std::endl;
	std::cout << "Printed (pre-order):" << std::endl;
	a.printCall();
	std::cout << "In order: " << std::endl;
	a.inorderCall();
	a.Delete(420);
	std::cout << "Deleted 420: " << std::endl;
	a.printCall();

	auto begin = std::chrono::system_clock::now();
	for(int i = 0; i < 1000; i++) {
		a.insert(i/9 + i%6);
	}
	auto finish = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = finish-begin;
	std::time_t end_time = std::chrono::system_clock::to_time_t(finish);
	std::cout << "Time taken Insert(1000): " << elapsed_seconds.count() << std::endl << std::endl;

	begin = std::chrono::system_clock::now();
	for(int i = 0; i < 2000; i++) {
                a.insert(i/4 + i%10);
        }
	finish = std::chrono::system_clock::now();
	elapsed_seconds = finish-begin;
	end_time = std::chrono::system_clock::to_time_t(finish);
	std::cout << "Time taken Insert(2000): " << elapsed_seconds.count() << std::endl << std::endl;

	begin = std::chrono::system_clock::now();
	for(int i = 0; i < 3000; i++) {
                a.insert(i/6 + i%18);
        }
	finish = std::chrono::system_clock::now();
	elapsed_seconds = finish-begin;
	end_time = std::chrono::system_clock::to_time_t(finish);
	std::cout << "Time taken Insert(3000): " << elapsed_seconds.count() << std::endl << std::endl;
	
	begin = std::chrono::system_clock::now();
        for(int i = 0; i < 1000; i++) {
                a.searchCall(i/9 + i%6);
        }
	finish = std::chrono::system_clock::now();
        elapsed_seconds = finish-begin;
        end_time = std::chrono::system_clock::to_time_t(finish);
        std::cout << "Time taken Search(1000): " << elapsed_seconds.count() << std::endl << std::endl;

        begin = std::chrono::system_clock::now();
        for(int i = 0; i < 2000; i++) {
                a.searchCall(i/4 + i%10);
        }
        finish = std::chrono::system_clock::now();
        elapsed_seconds = finish-begin;
        end_time = std::chrono::system_clock::to_time_t(finish);
        std::cout << "Time taken Search(2000): " << elapsed_seconds.count() << std::endl << std::endl;

        begin = std::chrono::system_clock::now();
        for(int i = 0; i < 3000; i++) {
                a.searchCall(i/6 + i%18);
        }
        finish = std::chrono::system_clock::now();
        elapsed_seconds = finish-begin;
        end_time = std::chrono::system_clock::to_time_t(finish);
        std::cout << "Time taken Search(3000): " << elapsed_seconds.count() << std::endl << std::endl;

	return 0;
}

void BinaryTree::transplant(TreeNode* u, TreeNode* v) {
	if(u == root) {
		root = v;
		return;
	}
	if(u == u->parent->left) {
		u->parent->left = v;
	}
	else {
		u->parent->right = v;
	}
	if(v != NULL) {
		v->parent = u->parent;
	}
}

void BinaryTree::insert(int n) {
	TreeNode* x = new TreeNode(n);
	TreeNode* tmp = root;
	TreeNode* prev = root;
	while(tmp != NULL) {
		prev = tmp;
		if(x->key <= tmp->key) {
			tmp = tmp->left;
		}
		else {
			tmp = tmp->right;
		}
	}
	if(x->key <= prev->key) {
		prev->left = x;
	}
	else {
		prev->right = x;
	}
	x->parent = prev;
}

TreeNode* BinaryTree::searchCall(int n) {
	return search(root, n);
}

TreeNode* BinaryTree::search(TreeNode* x, int n) {
	if(x == NULL || x->key == n) {
		return x;
	}
	else if(n < x->key) {
		return search(x->left, n);
	}
	else {
		return search(x->right, n);
	}
}

TreeNode* BinaryTree::minimum() {
	TreeNode* tmp = root;
	TreeNode* y = NULL;
	while(tmp != NULL) {
		y = tmp;
		tmp = tmp->left;
	}
	return y;
}

TreeNode* BinaryTree::maximum() {
	TreeNode* tmp = root;
	TreeNode* y = NULL;
	while(tmp != NULL) {
		y = tmp;
		tmp = tmp->right;
	}
	return y;
}

TreeNode* BinaryTree::successor() {
	TreeNode* x = root;
	if(x->right != NULL) {
		return minimum();
	}
	TreeNode* y = x->parent;
	while(y != NULL && x == y->right) {
		x = y;
		y = y->parent;
	}
}

void BinaryTree::inorderCall() {
	inorder(root);
	std::cout << std::endl;
}

void BinaryTree::inorder(TreeNode* x) {
	if(x != NULL) {
		inorder(x->left);
		std::cout << x->key << " ";
		inorder(x->right);
	}
}

void BinaryTree::Delete(int n) {
	TreeNode* x = searchCall(n);
    	if(x != NULL) {
        	if(x->left == NULL) {
            		transplant(x, x->right);
        	}
        	else if(x->right == NULL) {
            		transplant(x, x->left);
        	}
        	else {
            		TreeNode* y = searchCall(minimum()->key);
            		if(y->parent != x) {
                		transplant(x, x->right);
                		y->right = x->right;
                		y->right->parent = y;
            		}
            		transplant(x, y);
            		y->left = x->left;
            		y->left->parent = y;
        	}
    	}
}

void BinaryTree::printCall() {
        print(root);
        std::cout << std::endl;
}

void BinaryTree::print(TreeNode* x) {
        if(x != NULL) {
                std::cout << x->key << " ";
		print(x->left);
                print(x->right);
        }
}

BinaryTree::BinaryTree(int n) {
	root = new TreeNode(n);
}
