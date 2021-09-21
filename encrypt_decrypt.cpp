// encrypt_decrypt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdlib.h>
#include <string>
#include <iostream>
int ch_to_index(char ch) {
    if (ch >= 'A' && ch <= 'Z')
        return ch - 'A';
    if (ch >= 'a' && ch <= 'z')
        return ch - 'a' + 26;
    if (ch >= '0' && ch <= '9')
        return ch - '0' + 52;
    if (ch == ' ')
        return 62;
    return 63;
}
char index_to_ch(int index) {
    std::string arr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 .";
    return arr[index];
}
int* index_to_bin(int index) {
    int* res = (int*)malloc(sizeof(int) * 6);
    int i = 5;
    while (i >= 0) {
        res[i] = index % 2;
        index /= 2;
        i--;
    }
    return  res;
}
int bin_to_index(int* arr) {
    int i, mul, sum = 0;
    for (mul = 1, i = 5; i >= 0; i--, mul *= 2)
        sum += arr[i] * mul;
    return sum;
}
std::string encrypt(std::string text)
{
    if (text.empty())
        return text;
    int** arr = new int* [text.length()];
    int i, t, r, j;
    std::string res = "";
    for (i = 0; i < text.length(); i++)
        if (!(text[i] >= 'a' && text[i] <= 'z' || text[i] >= 'A' && text[i] <= 'Z' ||
            text[i] >= '0' && text[i] <= '9' || text[i] == ' ' || text[i] == '.'))
            throw std::exception();
    for (i = 0; i < text.length(); i++)
        arr[i] = index_to_bin(ch_to_index(text[i]));
    for (i = 0; i < text.length(); i++) {
        if (i < text.length() - 1) {
            t = arr[i][4];
            arr[i][4] = arr[i + 1][0];
            arr[i + 1][0] = t;
        }
        arr[i][1] = (arr[i][1] + 1) % 2;
        arr[i][3] = (arr[i][3] + 1) % 2;
        for (r = 0; r < 3; r++) {
            t = arr[i][r];
            arr[i][r] = arr[i][r + 3];
            arr[i][r + 3] = t;
        }
        for (r = 0; r < 5; r += 2) {
            t = arr[i][r];
            arr[i][r] = arr[i][r + 1];
            arr[i][r + 1] = t;
        }
        for (r = 0, j = 5; r < j; r++, j--) {
            t = arr[i][r];
            arr[i][r] = arr[i][j];
            arr[i][j] = t;
        }
        t = arr[i][0];
        arr[i][0] = arr[i][2];
        arr[i][2] = t;
    }

    for (i = 0; i < text.length(); i++) {
        res += index_to_ch(bin_to_index(arr[i]));
        free(arr[i]);
    }
    delete[]arr;
    return res;
}

std::string decrypt(std::string text)
{
    if (text.empty())
        return text;
    int** arr= new int* [text.length()];
    int i, t, r, j;
    std::string res = "";
    for (i = 0; i < text.length(); i++)
        if (!(text[i] >= 'a' && text[i] <= 'z' || text[i] >= 'A' && text[i] <= 'Z' ||
            text[i] >= '0' && text[i] <= '9' || text[i] == ' ' || text[i] == '.'))
            throw std::exception();
    for (i = 0; i < text.length(); i++)
        arr[i] = index_to_bin(ch_to_index(text[i]));
    for (i = text.length() - 1; i >= 0; i--) {
        t = arr[i][0];
        arr[i][0] = arr[i][2];
        arr[i][2] = t;
        for (r = 0, j = 5; r < j; r++, j--) {
            t = arr[i][r];
            arr[i][r] = arr[i][j];
            arr[i][j] = t;
        }
        for (r = 0; r < 5; r += 2) {
            t = arr[i][r];
            arr[i][r] = arr[i][r + 1];
            arr[i][r + 1] = t;
        }
        for (r = 0; r < 3; r++) {
            t = arr[i][r];
            arr[i][r] = arr[i][r + 3];
            arr[i][r + 3] = t;
        }
        arr[i][1] = (arr[i][1] + 1) % 2;
        arr[i][3] = (arr[i][3] + 1) % 2;
    }
    for (i = text.length() - 1; i > 0; i--) {
        t = arr[i - 1][4];
        arr[i - 1][4] = arr[i][0];
        arr[i][0] = t;
    }
    for (i = 0; i < text.length(); i++) {
        res += index_to_ch(bin_to_index(arr[i]));
        free(arr[i]);
    }
    delete[]arr;
    return res;
}
using namespace std;
int main()
{
    int c;
    std::string str="";
    while(true){
        std::cout << "1 encrypt\n2 decrypt\nother exit\n";
        std::cin >> c;
        if (c > 2 || c < 1)
            break;
        std::cout << "Enter text\n";
        cin.ignore();
        getline(cin,str);
        switch (c) {
            case 1:
                std::cout << "encrypted: " << encrypt(str) << endl << endl;
                break;
            case 2:
                std::cout << "decrypted: " << decrypt(str)<< endl << endl;
                break;
        }
    };
    std::cout << "Good bye\n";
    std::cin >> c;
}

