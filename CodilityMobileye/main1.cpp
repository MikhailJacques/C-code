
#include <iostream>
#include <vector>

using namespace std;

int solution(vector<int>& A, vector<int>& B) 
{
    int sum_A = 0, sum_B = 0;
    int temp_A = A[0];
    int temp_B = B[0];
    int num_of_fair_indices_cnt = 0;

    for (size_t i = 0; i < A.size(); i++) 
    {
        sum_A += A[i];
        sum_B += B[i];
    }

    for (size_t ii = 1; ii < A.size(); ii++)
    {
        if ((ii != 1) && (temp_A == temp_B) && (2 * temp_A == sum_A) && (2 * temp_B == sum_B))
            num_of_fair_indices_cnt++;

        temp_A += A[ii];
        temp_B += B[ii];
    }

    return num_of_fair_indices_cnt;
}

int main()
{
    //vector<int> a = { 1, 2, 3, 4, 5 };
    //vector<int> b = { 6, 2, 1, 5, 4 };

    vector<int> a = { 0, 4, -1, 0, 3 };
    vector<int> b = { 0, -2, 5, 0, 3 };

    cout << "Number of fair indices: " << solution(a, b) << endl;
}