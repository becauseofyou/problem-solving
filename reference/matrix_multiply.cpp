namespace matrix {
	const int MATRIX_SIZE = 4;
	#define sz MATRIX_SIZE
    struct mat {
    	int a[MATRIX_SIZE][MATRIX_SIZE];
    	mat(const int type = 0) {
    		memset(a, 0, sizeof(a));
    		if (type == 1) {
	    		rep (i, sz) {
	    			a[i][i] = 1;
	    		}
    		}
    	}
    	int * operator[] (const int i) {
			return a[i];
		}
    };

    void set_row(mat &a, int row_id, std::vector<int> row) {
    	rep (i, sz) {
    		a[row_id][i] = row[i];
    	}
    }
    int multiply_column(std::vector <int> v, mat &a, int col_id) {
    	int ret = 0;
    	rep (i, sz) {
    		add(ret, mul(v[i], a[i][col_id])); 
    	}
    	return ret;
    }
    mat operator * (mat a, mat b) {
    	mat ret(0);
    	rep (i, sz) {
    		rep (j, sz) {
    			rep (k, sz) {
                    add(ret[i][j], mul(a[i][k], b[k][j]));
                }
    		}
    	}
    	return ret;
    }
    mat power(const mat a, int64 n) {
    	mat ret(1);
    	for (int i = 60; i >= 0; i--) {
    		ret = ret * ret;
    		if (n >> i & 1) {
    			ret = ret * a;
    		}
    	}
    	return ret;
    }
}
