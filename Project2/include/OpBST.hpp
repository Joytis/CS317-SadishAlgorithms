#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <climits>

#include "includes.hpp"

using table_type = std::vector<std::vector<int>>;

struct bt_node {
	int val;
	bt_node* left;
	bt_node* right;
};

class OpBST {
private:
	bt_node* head_;
	std::vector<int> data_;
	table_type prob_table_;
	table_type key_table_;
	int num_elems;
	int table_size;

	int numDigits(int32_t x);
	void calcTable();
	void clearTree(bt_node* node);
	bt_node* calcTree(int row, int col);
	void printTable();
	void printTree();
	void printTree(bt_node* node, int layer);
	void printData();

public:
	OpBST();
	void readFromFile(std::string path);
	void printAll();
	void calculate();

};