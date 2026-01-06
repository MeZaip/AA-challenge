#include <bits/stdc++.h>
#include <iostream>
using namespace std;

bool subset_sum_rec(int i, int n, int set[], int targetSum,
					vector<int>& subset)
{
	// targetSum is zero then there exist a subset.
	if (targetSum == 0) {
		cout << "Size: "<<subset.size() << endl;
		cout << "Subset: ";
		for (int i = 0; i < subset.size(); i++) {
			cout << subset[i] << " ";
		}
		cout << endl;
		return true;
	}
	
	if (i == n) {
		// return if we have reached at the end of the array
		return false;
	}
	
	// Not considering current element
	if (subset_sum_rec(i + 1, n, set, targetSum, subset)) {
		return true;
	}

	// push the current element in subset
	subset.push_back(set[i]);

	// Recursive call for consider current element
	if (subset_sum_rec(i + 1, n, set, targetSum - set[i], subset)) {
		return true;
	}

	// pop-back element after recursive call to restore
	// subsets original configuration
	subset.pop_back();

	return false;
}

int main(int argc, char* argv[])
{
	FILE *f = fopen(argv[1], "r");
	int n, sum;
	fscanf(f, "%d %d", &n, &sum);
	int *set = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &set[i]);
	}
	fclose(f);
	vector<int> subset;
	bool found = subset_sum_rec(0, n, set, sum, subset);
	if (!found) {
		cout << "No subset found." << endl;
	} else {
		cout << "Sum: " << n << endl;
	}

	return 0;
}
