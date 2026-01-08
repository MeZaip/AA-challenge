#include <bits/stdc++.h>
using namespace std;

// DP top-down with offset for negative numbers
bool subsetSumRec(vector<int>& a, int n, int sum,
				  vector<vector<int>>& memo,
				  int offset) {

	int idx = sum + offset;

	if (idx < 0 || idx >= (int)memo[0].size())
		return false;

	if (n == 0)
		return (sum == 0);

	if (memo[n][idx] != -1)
		return memo[n][idx];

	bool res =
		subsetSumRec(a, n - 1, sum, memo, offset) ||
		subsetSumRec(a, n - 1, sum - a[n - 1], memo, offset);

	memo[n][idx] = res;
	return res;
}

// Reconstruct the subset from the memo table
void buildSubset(vector<int>& a, int n, int sum,
				 vector<vector<int>>& memo,
				 int offset, vector<int>& res) {

	if (sum == 0 || n == 0) return;

	int includeIdx = sum - a[n - 1] + offset;

	if (includeIdx >= 0 && includeIdx < (int)memo[0].size() &&
		memo[n - 1][includeIdx] == 1) {

		res.push_back(a[n - 1]);
		buildSubset(a, n - 1, sum - a[n - 1], memo, offset, res);
	} else {
		buildSubset(a, n - 1, sum, memo, offset, res);
	}
}

bool subsetSum(vector<int>& a, int target, vector<int>& result) {
	int n = a.size();

	// Calculate the offset
	int minSum = 0, maxSum = 0;
	for (int x : a) {
		if (x < 0) minSum += x;
		else maxSum += x;
	}

	if (target < minSum || target > maxSum)
		return false;

	int offset = -minSum;
	int range = maxSum - minSum + 1;

	vector<vector<int>> memo(n + 1, vector<int>(range, -1));

	memo[0][offset] = 1;

	bool ok = subsetSumRec(a, n, target, memo, offset);

	if (ok)
		buildSubset(a, n, target, memo, offset, result);

	return ok;
}

int main(int argc, char* argv[])
{
	if (argc < 2) {
		cout << "Usage: " << argv[0] << " input.txt\n";
		return 0;
	}

	FILE* f = fopen(argv[1], "r");
	int n, sum;
	if (!fscanf(f, "%d %d", &n, &sum)) {
		cout << "Could not read input file.\n";
		return 0;
	}
	vector<int> a(n);
	for (int i = 0; i < n; i++) {
		if (!fscanf(f, "%d", &a[i])) {
			cout << "Could not read input file.\n";
			return 0;
		}
	}
	fclose(f);

	vector<int> res;

	if (subsetSum(a, sum, res)) {
		cout << "Size: " << res.size() << "\n";
		cout << "Subset: ";
		for (int x : res)
			cout << x << " ";
		cout << "\n";
		cout << "T: " << sum << endl;
	} else {
		cout << "No subset found\n";
	}

	return 0;
}
