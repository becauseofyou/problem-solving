//in most case T is a pair, T.first is value, T.second is index 
template<typename T>
class dan{
    public :
        dan(int n) : fr(0), ed(0){
            q.resize(n);
            fr = 0;
            ed = 0;
        }
        vector<T> q;
        int fr, ed;
        bool empty() {
            return fr >= ed;
        }
        T back() {
            return q[ed - 1];
        }
        T front() {
            return q[fr];
        }
        void pop_back() {
            ed--;
        }
        void pop_front() {
            fr++;
        }
        void push_back(T ele) {
            q[ed++] = ele;
        }
        void insert(T ele) {
            while (!empty() && back().first <= ele.first) {
                pop_back();
            }
            push_back(ele);
        }
};
