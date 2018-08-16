#include "OpBST.hpp"

OpBST::OpBST() :
	head_(NULL)
{}

void OpBST::readFromFile(std::string path)
{
	std::fstream file(path, std::ios_base::in);

	if(file.is_open()) {
		file >> num_elems;
		table_size = num_elems + 1;

		data_.clear();
		prob_table_.clear();
		key_table_.clear();

		// Resize all the vectors to store some of dis
		data_.resize(num_elems);
		key_table_.resize(table_size);
		prob_table_.resize(table_size);
		for(int i = 0; i < table_size; i++) {
			key_table_[i].resize(table_size);
			prob_table_[i].resize(table_size);
		}

		int temp;
		for (int i = 0; i < num_elems; i++){
	  		file >> temp;
	  		data_[i] = temp;
	  	}
	}

	file.close();
}

void OpBST::printData() 
{
	printf("// DATA // \n");
	for(int i = 0; i < num_elems; i++) {
		printf("%d ", data_[i]);
	}
	printf("\n\n");
}

void OpBST::printTable()
{
	// Determine max digits for int32 var
	int max = 0;
	int dig = 0;
	for (int i = 1; i < table_size; ++i) {
		for (int j = i; j < table_size; ++j) {
			dig = numDigits(prob_table_[i][j]);
			if(dig > max) 
				max = dig;
		}
	}
	if(max < 3)
		max = 3;

	printf("// VALUE TABLE // \n");

	printf("    | ");
	for(int i = 0; i < table_size; i++ ) {
		printf("%*d ", max, i);
	}

	printf("\n");
	for(int i = 0; i < (table_size + 2) * (max + 1); i++ ) {
		printf("-");
	}
	printf("\n");

	for(int i = 0; i < table_size; i++) {
		printf(" %2d | ",  i);
		for(int j = 0; j < table_size; j++) {
			if(prob_table_[i][j] == -1) {
				printf("%*s ", max, "---");
			}
			else{
				printf("%*d ", max, prob_table_[i][j]);
			}
		}
		printf("\n");
	}

	printf("// KEY TABLE // \n");

	printf("    | ");
	for(int i = 0; i < table_size; i++ ) {
		printf("%*d ", max, i);
	}

	printf("\n");
	for(int i = 0; i < (table_size + 2) * (max + 1); i++ ) {
		printf("-");
	}
	printf("\n");

	for(int i = 0; i < table_size; i++) {
		printf(" %2d | ",  i);
		for(int j = 0; j < table_size; j++) {
			if(key_table_[i][j] == -1) {
				printf("%*s ", max, "---");
			}
			else{
				printf("%*d ", max, key_table_[i][j] + 1);
			}
		}
		printf("\n");
	}
}

void OpBST::printTree() 
{
	printf("// OPTIMAL BST //\n");
	printTree(head_, 0);
}

void OpBST::printTree(bt_node* node, int layer)
{
	for(int i = 0; i < layer; i++) {
		printf("  ");
	}

	if(node != NULL) {
		printf("%d\n", node->val + 1);
		if(node->left != NULL || node->right != NULL) {
			printTree(node->left, layer + 1);
			printTree(node->right, layer + 1);
		}
	}
	else {
		printf("-\n");
	}
}

void OpBST::printAll()
{
	printData();
	printTable();
	printTree();
}

void OpBST::calculate()
{
	calcTable();
	clearTree(head_);
	head_ = calcTree(0, table_size - 1);
}

void OpBST::calcTable()
{
	for(int i = 0; i < table_size; i++) {
		for(int j = 0; j < table_size; j++) {
			key_table_[i][j] = -1;
			prob_table_[i][j] = -1;
		}		
	}

	// Initialize
	for(int i = 0; i < table_size; i++) {
		prob_table_[i][i] = 0;
	}

	for(int i = 0; i < num_elems; i++) {
		prob_table_[i][i+1] = data_[i];
		key_table_[i][i+1] = i;
	}

	// Calculate the rest
	for(int d = 0; d < table_size; d++) {
		for(int i = 0; i < (table_size - d - 2); i++) {


			int j = i + d + 2;

			int sum_p = 0;
			int min_value = INT_MAX;
			int min_root = 0;
			for(int k = i; k < j; k++) {
				sum_p += data_[k];
				int value = prob_table_[i][k] + prob_table_[k+1][j];
				if(value < min_value) {
					min_value = value;
					min_root = k;
				}
			}
			prob_table_[i][j] = sum_p + min_value;
			key_table_[i][j] = min_root;
		}
	}
}

void OpBST::clearTree(bt_node* node) {
	if(node != NULL) {
		clearTree(node->left);
		clearTree(node->right);
		delete node;
	}
}

bt_node* OpBST::calcTree(int row, int col)
{
	bt_node* new_node = NULL;
	if(row != col) {
		new_node = new bt_node;
	 	new_node->val = key_table_[row][col];
		new_node->left = calcTree(row, key_table_[row][col]); //left subtree
 		new_node->right = calcTree(key_table_[row][col] + 1, col); //right subtree 
 	}
 	return new_node;
}

int OpBST::numDigits(int32_t x) {
    if (x == INT_MIN) return 10 + 1;
    if (x < 0) return numDigits(-x) + 1;

    if (x >= 10000) {
        if (x >= 10000000) {
            if (x >= 100000000) {
                if (x >= 1000000000)
                    return 10;
                return 9;
            }
            return 8;
        }
        if (x >= 100000) {
            if (x >= 1000000)
                return 7;
            return 6;
        }
        return 5;
    }
    if (x >= 100) {
        if (x >= 1000)
            return 4;
        return 3;
    }
    if (x >= 10)
        return 2;
    return 1;
}

