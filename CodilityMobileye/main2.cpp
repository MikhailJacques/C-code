//
//#include <iostream>
//#include <vector>
//
//using namespace std;
//
//int solution1(string& S)
//{
//    int num_operations = 0;
//    long long number = 0;
//
//    for (int i = 0; i < S.length(); i++)
//    {
//        number <<= 1;
//
//        if (S[i] == '1')
//            number += 1;
//    }
//
//    while (number > 0)
//    {
//        if (number % 2 == 0)
//            number /= 2;
//        else
//            number -= 1;
//
//        num_operations += 1;
//    }
//
//    return num_operations;
//}
//
//int solution2(std::string& S)
//{
//    int ones_cnt = std::count(S.begin(), S.end(), '1');
//    
//    if (ones_cnt == 0) 
//    {
//        return 0;
//    }
//
//    return ones_cnt * 2 + (S.size() - ones_cnt - 1);
//}
//
//int solution3(string S)
//{
//    if (S.size() == 0)
//        return 0;
//
//    int counter = 0;
//
//    for (int i = S.length() - 1; i > 0;) 
//    {
//        if (S[i] == '0') 
//        {
//            counter++;
//            i--;
//        }
//        else 
//        {
//            counter++;
//
//            while (S[i] == '1' && i > 0) 
//            {
//                counter++;
//                i--;
//            }
//
//            if (i == 0)
//                counter++;
//
//            S[i] = '1';
//        }
//    }
//
//    return counter;
//}
//
//int main()
//{
//    string s1 = "10000100000";
//    string s2 = "011100";
//    string s3 = "111";
//    string s4 = "11110101111";
//
//    cout << solution1(s1) << endl;
//    cout << solution1(s2) << endl;
//    cout << solution1(s3) << endl;
//    cout << solution1(s4) << endl << endl;
//
//    cout << solution2(s1) << endl;
//    cout << solution2(s2) << endl;
//    cout << solution2(s3) << endl;
//    cout << solution2(s4) << endl << endl;
//
//    cout << solution3(s1) << endl;
//    cout << solution3(s2) << endl;
//    cout << solution3(s3) << endl;
//    cout << solution3(s4) << endl;
//
//    return 0;
//}