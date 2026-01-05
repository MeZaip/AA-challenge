// Top-down DP solution.
#include <bits/stdc++.h>
using namespace std;

// Recursive function to check if a subset 
// with the given sum exists
bool isSubsetSumRec(vector<int>& arr, int n, int sum,
				   vector<vector<int>> &memo) {
  
	// If the sum is zero, we found a subset
	if (sum == 0)
		return 1;

	// If no elements are left
	if (n <= 0)
		return 0;

	// If the value is already computed, return it
	if (memo[n][sum] != -1)
		return memo[n][sum];

	// If the last element is greater than the sum, ignore it
	if (arr[n - 1] > sum)
		return memo[n][sum] = isSubsetSumRec(arr, n - 1, sum, memo);
	else {
	  
		// Include or exclude the last element
		return memo[n][sum] = isSubsetSumRec(arr, n - 1, sum, memo) ||
							  isSubsetSumRec(arr, n - 1, sum - arr[n - 1], memo);
	}
}

// Function to initiate the subset sum check
bool isSubsetSum(vector<int>&arr, int sum) {
   int n = arr.size();

	vector<vector<int>> memo(n + 1, vector<int>(sum + 1, -1));
	return isSubsetSumRec(arr, n, sum, memo);
}

int main(int argc, char* argv[]) {
  
	FILE *f = fopen(argv[1], "r");
	int n, sum;
	fscanf(f, "%d %d", &n, &sum);
	int *set = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		fscanf(f, "%d", &set[i]);
	}
	fclose(f);

	vector<int> arr(set, set + n);
	if (isSubsetSum(arr, sum)) {
		cout << "True" << endl;
	}
	else {
		cout << "False" << endl;
	}

	return 0;
}