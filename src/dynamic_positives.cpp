// Top-down DP solution ( works only with positive numbers )
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

// O(n) function to find and print the subset
void findSubset(vector<int>& arr, int n, int sum,
                vector<vector<int>>& memo, vector<int>& result) {
    
    if (sum == 0)
        return;
    
    // If we're at the beginning, return
    if (n <= 0)
        return;
    
    // If current element was NOT included
    if (memo[n-1][sum] == 1) {
        findSubset(arr, n - 1, sum, memo, result);
    }
    // If current element WAS included
    else if (sum >= arr[n-1] && memo[n-1][sum - arr[n-1]] == 1) {
        result.push_back(arr[n - 1]);
        findSubset(arr, n - 1, sum - arr[n - 1], memo, result);
    }
}

// Function to initiate the subset sum check
bool isSubsetSum(vector<int>&arr, int sum, vector<int>& result) {
    int n = arr.size();

    vector<vector<int>> memo(n + 1, vector<int>(sum + 1, -1));
    bool exists = isSubsetSumRec(arr, n, sum, memo);
    
    if (exists) {
        findSubset(arr, n, sum, memo, result);
    }
    
    return exists;
}

int main(int argc, char* argv[]) {
  
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
    int *set = (int *)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
		if (!fscanf(f, "%d", &set[i]) || set[i] < 0) {
			cout << "Wrong numbers in input file.\n";
			return 0;
		}
	}
    fclose(f);

    vector<int> arr(set, set + n);
    vector<int> result;
    
    if (isSubsetSum(arr, sum, result)) {
        cout << "Size: " << result.size() << endl;
        cout << "Subset: ";
        for (int i = 0; i < (int)result.size(); i++) {
            cout << result[i];
            if (i < result.size() - 1) cout << " ";
        }
        cout << endl;
        cout << "Sum: " << sum << endl;
    }
    else {
        cout << "No subset found." << endl;
    }

    free(set);
    return 0;
}