//#include <stdio.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
////#ifdef _MSC_VER
////#define _CRT_SECURE_NO_WARNINGS
////#endif
//
//void ReverseStr1(char *str)
//{
//    size_t len = strlen(str);
//
//    // Calculate string length
//    while (str[len] != '\0')
//        len++;
//
//    for (int ii = 0; ii < len / 2; ii++)
//    {
//        char ch = str[ii];
//        str[ii] = str[len - ii - 1];
//        str[len - ii - 1] = ch;
//    }
//}
//
//void ReverseStr2(char *str)
//{
//    int ii, jj, len = 0;
//
//    // Calculate string length
//    while (str[len] != '\0')
//        len++;
//
//    char* rev_str = (char*) calloc(len, sizeof(char));
//    //char* rev_str = (char*)malloc(len); calloc(len, sizeof(char));
//
//    jj = len - 1;
//
//    if (rev_str != nullptr)
//    {
//        for (ii = 0; ii < len; ii++)
//        {
//            rev_str[ii] = str[jj--];
//        }
//
//        rev_str[ii] = '\0';
//
//        strcpy(str, rev_str);
//    }
//}
//
//void ReverseStr3(char* str)
//{
//    char *rev_str;
//    int begin, end, cnt = 0;
//
//    // Calculate string length
//    while (str[cnt] != '\0')
//        cnt++;
//
//    end = cnt - 1;
//
//    rev_str = (char*)malloc(cnt);
//
//    for (begin = 0; begin < cnt; begin++) 
//    {
//        rev_str[begin] = str[end--];
//    }
//
//    rev_str[begin] = '\0';
//
//    strcpy(str, rev_str);
//}
//
//int main()
//{
//    char str[1000];
//
//    //printf("Input a string:");
//    //int ret_val = scanf("%s", str);
//
//    strcpy(str, "Shalom");
//
//    printf("\nString Before Reverse: %s", str);
//
//    ReverseStr1(str);
//    printf("\nString After Reverse1: %s", str);
//
//    ReverseStr2(str);
//    printf("\nString After Reverse2: %s", str);
//
//    ReverseStr3(str);
//    printf("\nString After Reverse3: %s", str);
//
//    return 0;
//}