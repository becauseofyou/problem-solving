namespace dkr_tree {
	struct node {
		node *lc, *rc;
		int value, sz;
		int64 dfs();
		node () {
			lc = rc = NULL;
		}
	}*root,*memory, pool[N];

	std::stack <node*> stack;

	void insert(int number) {
		if (root == NULL) {
			root = new(memory++) node();
			root->value = number;
			stack.push(root);

		} else {
			node *new_node = new(memory++) node();
			new_node->value = number;
			node *last = NULL;
			while (!stack.empty() && number < stack.top()->value) {
				last = stack.top();
				stack.pop();
			}
			if (stack.empty()) {
				new_node->lc = last;
				root = new_node;
			} else {
				stack.top()->rc = new_node;
				new_node->lc = last;
			}
			stack.push(new_node);
		}
	}

	int64 node::dfs() {
		int64 lvalue = -1, rvalue = -1;
		if (lc) {
			lvalue = lc->dfs();
		}
		if (rc) {
			rvalue = rc->dfs();
		}
		sz = (lc?lc->sz:0) + (rc?rc->sz:0) + 1;
		int64 now_value = 1LL * sz * value;
		return std::max(now_value, std::max(lvalue, rvalue));
	}

	void clear() {
		while (!stack.empty()) {
			stack.pop();
		}
		memory = pool;
		root = NULL;
	}

};