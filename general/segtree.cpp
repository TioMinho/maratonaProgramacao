#include <iostream>
#include <vector>

class SegmentTree {
private:
	vector<int> st, A;
	int n;
	int left(int p) { return p << 1; }
	int right(int p) { return (p << 1)+1; }

	void build(int p, int L, int R) {  // O(n)
		if (L==R) st[p] = L;
		else {
			build(left(p) ,  L         , (L+R)/2);
			build(right(p), (L+R)/2 + 1, R      );

			int p1 = st[left(p)], p2 = st[right(p)];

			// CHANGE TO THE DESIRED TREE
			st[p] =    (A[p1] <= A[p2]) ? p1 : p2;
					// (A[p1] >= A[p2]) ? p1 : p2;
					//  p1 + p2;
					//  p1 * p2;
					//  ...
	}}

	int rmq(int p, int L, int R, int i, int j) { // O(lg n)
		if (i >  R || j <  L) return -1;		// Out of query range
		if (L >= i && R <= j) return st[p];		// Inside query range

		int p1 = rmq(left(p) ,  L        , (L+R)/2 , i , j);
		int p2 = rmq(right(p), (L+R)/2 +1, R       , i , j);

		// CHANGE TO THE DESIRED TREE
		return (A[p1] <= A[p2]) ? p1 : p2;
			// (A[p1] >= A[p2]) ? p1 : p2;
			//  p1 + p2;
			//  p1 * p2;
			//  ...
	}

public:
	SegmentTree(const vector<int> &_A) {
		A = _A; n = (int)A.size();
		st.assign(4*n, 0);
		build(1, 0, n-1);
	}

	int rmq(int i, int j) { return rmq(1, 0, n-1, i, j); }
};

int main() {
	int arr[] = { 18, 17, 13, 19, 15, 11, 20 };
	vector<int> A(arr, arr+7);

	SegmentTree st(A);

	printf("RMQ(1,3) = %d\n", st.rmq(1, 3));
	printf("RMQ(4,6) = %d\n", st.rmq(4, 6));

	return 0;
}