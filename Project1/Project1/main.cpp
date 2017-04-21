#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <math.h>
#include <algorithm>
#include <time.h>

using namespace std;

class Tree {
private:
	struct tree_node{
		tree_node* link1;
		tree_node* link2;
		tree_node* link3;
		tree_node* link4;
		tree_node* parent;
		vector<int> state;
		int cost;
		int index;
		int distance;
	};
	vector<int> initial, final;
	vector<tree_node*> stack;
	tree_node* root;
	int heuristic;
	bool success;

public:
	Tree() {
		root = NULL;
	}

	bool isEmpty() const { return root == NULL; }
	void populate(tree_node*);
	void createRoot(vector<int>);
	void make();
	void view();
	void makeMove(tree_node*, tree_node*, char);
	void print(tree_node*);
	void pv(tree_node*);
	void testSuccess(tree_node*);
	int h1(tree_node*);
	void arrange();
};

void Tree::make() {
	view();
	createRoot(initial);
	success = false;
	tree_node* current;
	heuristic = 1;

	int count = 0;
	while (stack.size() > 0) {
		current = stack.front();
		stack.erase(stack.begin());
		populate(current);

		if (current->distance > count) {
			count = current->distance;
			cout << "n = " << count << endl;
		}
	}
}
void Tree::view() {
	ifstream inFile("in.txt");
	string line, item;
	int	itemnum = 0;

	while (getline(inFile, line)) {
		istringstream linestream(line);
		while (getline(linestream, item, ' ')) {
			itemnum++;
			if (itemnum <= 9) {
				initial.push_back(atoi(item.c_str()));
			}
			else {
				final.push_back(atoi(item.c_str()));
			}
		}
	}
}

void Tree::createRoot(vector<int> state) {
	tree_node* t1 = new tree_node;
	for (int i = 0; i<(signed)state.size(); i++)
		t1->state.push_back(state[i]);
	t1->cost = h1(t1);
	t1->distance = 1;
	t1->link1 = NULL; t1->link2 = NULL; t1->link3 = NULL; t1->link4 = NULL;
	t1->parent = NULL;

	for (int i = 0; i<(signed)state.size(); i++) {
		if (state[i] == 0) {
			t1->index = i;
		}
	}

	if (isEmpty()) {
		root = t1;
		stack.push_back(root);
	}
}
int Tree::h1(tree_node* t) {
	int cost = 0;

	for (int i = 0; i<(signed)t->state.size(); i++) {
		if (t->state[i] != final[i]) {
			cost++;
		}
	}

	return cost;
}
void Tree::makeMove(tree_node* current, tree_node* t, char dir) {
	int temp, index;
	bool badMove = false;

	for (int i = 0; i<(signed)current->state.size(); i++) {
		if (current->state[i] == 0) {
			index = i;
		}
		t->state.push_back(current->state[i]);
	}
	t->index = index;

	if (current->distance > 2) {
		if (index == current->parent->index) {
			badMove = true;
		}
	}

	switch (dir) {
	case 'u':
		if ((index > 2) && (!badMove)) {
			temp = t->state[index];
			t->state[index] = t->state[index - 3];
			t->state[index - 3] = temp;
		}
		else
			t->state.erase(t->state.begin(), t->state.end());
		break;
	case 'r':
		if ((index % 3 != 2) && (!badMove)) {
			temp = t->state[index];
			t->state[index] = t->state[index + 1];
			t->state[index + 1] = temp;
		}
		else
			t->state.erase(t->state.begin(), t->state.end());
		break;
	case 'd':
		if ((index < 6) && (!badMove)) {
			temp = t->state[index];
			t->state[index] = t->state[index + 3];
			t->state[index + 3] = temp;
		}
		else
			t->state.erase(t->state.begin(), t->state.end());
		break;
	case 'l':
		if ((index % 3 != 0) && (!badMove)) {
			temp = t->state[index];
			t->state[index] = t->state[index - 1];
			t->state[index - 1] = temp;
		}
		else
			t->state.erase(t->state.begin(), t->state.end());
		break;
	}
}
void Tree::populate(tree_node* current) {
	tree_node* t1 = new tree_node;
	makeMove(current, t1, 'u');
	t1->distance = current->distance + 1;
	t1->cost = h1(t1) + t1->distance;
	t1->link1 = NULL; t1->link2 = NULL; t1->link3 = NULL; t1->link4 = NULL;
	t1->parent = current;

	tree_node* t2 = new tree_node;
	makeMove(current, t2, 'r');
	t2->distance = current->distance + 1;
	t2->cost = h1(t2) + t2->distance;
	t2->link1 = NULL; t2->link2 = NULL; t2->link3 = NULL; t2->link4 = NULL;
	t2->parent = current;

	tree_node* t3 = new tree_node;
	makeMove(current, t3, 'd');
	t3->distance = current->distance + 1;
	t3->cost = h1(t3) + t3->distance;
	t3->link1 = NULL; t3->link2 = NULL; t3->link3 = NULL; t3->link4 = NULL;
	t3->parent = current;

	tree_node* t4 = new tree_node;
	makeMove(current, t4, 'l');
	t4->distance = current->distance + 1;
	t4->cost = h1(t4) + t4->distance;
	t4->link1 = NULL; t4->link2 = NULL; t4->link3 = NULL; t4->link4 = NULL;
	t4->parent = current;

	if ((current->link1 == NULL) && (t1->state.size() > 0)) {
		current->link1 = t1;
		if (!success) stack.push_back(current->link1);
	}
	else
		delete t1;
	if ((current->link2 == NULL) && (t2->state.size() > 0)) {
		current->link2 = t2;
		if (!success) stack.push_back(current->link2);
	}
	else
		delete t2;
	if ((current->link3 == NULL) && (t3->state.size() > 0)) {
		current->link3 = t3;
		if (!success) stack.push_back(current->link3);
	}
	else
		delete t3;
	if ((current->link4 == NULL) && (t4->state.size() > 0)) {
		current->link4 = t4;
		if (!success) stack.push_back(current->link4);
	}
	else
		delete t4;

	arrange();
	testSuccess(current);
}
void Tree::arrange() {
	tree_node* temp;

	for (int i = 0; i<(signed)stack.size() - 1; i++) {
		for (int j = 0; j<(signed)stack.size() - 1; j++) {
			if (stack[j]->cost > stack[j + 1]->cost) {
				temp = stack[j];
				stack[j] = stack[j + 1];
				stack[j + 1] = temp;
			}
		}
	}
}
void Tree::testSuccess(tree_node* current) {
	bool	pass1 = true,
		pass2 = true,
		pass3 = true,
		pass4 = true;

	for (int i = 0; i<(signed)final.size(); i++) {
		if (current->link1 != NULL){
			if (current->link1->state[i] != final[i])
				pass1 = false;
		}
		else
			pass1 = false;
		if (current->link2 != NULL) {
			if (current->link2->state[i] != final[i])
				pass2 = false;
		}
		else
			pass2 = false;
		if (current->link3 != NULL) {
			if (current->link3->state[i] != final[i])
				pass3 = false;
		}
		else
			pass3 = false;
		if (current->link4 != NULL) {
			if (current->link4->state[i] != final[i])
				pass4 = false;
		}
		else
			pass4 = false;
	}
	if (pass1) {
		success = true;
		cout << "Success!" << endl;
		print(current->link1);
	}
	else if (pass2) {
		success = true;
		cout << "Success!" << endl;
		print(current->link2);
	}
	else if (pass3) {
		success = true;
		cout << "Success!" << endl;
		print(current->link3);
	}
	else if (pass4) {
		success = true;
		cout << "Success!" << endl;
		print(current->link4);
	}

	if (success) {
		while (!stack.empty())
			stack.erase(stack.begin());
	}
}
void Tree::pv(tree_node* t) {
	for (int i = 0; i<(signed)t->state.size(); i++) {
		cout << t->state[i] << " ";
		if (i % 3 == 2) cout << endl;
	}
	cout << t->cost << " " << t->distance << endl;
	cout << endl;
}
void Tree::print(tree_node* t) {
	ofstream fout("out.txt");
	vector<tree_node*> v;
	while (t != NULL) {
		v.push_back(t);
		t = t->parent;
	}
	fout << "Initial State" << endl;
	for (int j = v.size() - 1; j >= 0; j--) {
		for (int i = 0; i<(signed)v[j]->state.size(); i++) {
			if (v[j]->state[i] == 0)
				fout << "B ";
			else
				fout << v[j]->state[i] << " ";
			if (i % 3 == 2) fout << endl;
		}
		fout << endl;
	}
	fout << "Goal State" << endl;
	fout.close();
}
int main() {
	clock_t start, finish, total;
	start = clock();

	Tree b;
	b.make();

	finish = clock();
	total = finish - start;
	cout << "time: " << total << " msecs" << endl;
}