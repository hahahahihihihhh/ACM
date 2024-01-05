/*
    bitset用法
*/
#include<bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
const int SIZE = 31;
const int ALL = (1 << SIZE) - 1;     //num.set()
#define tmp template<class T>

tmp inline void showBit(T num) {
    bitset<SIZE + 1> bit(num);
    cout << bit << endl;
}
tmp inline void insert(T &num, int n) {//将num第n+1位设置成1
    num |= 1 << n;
    // bitset<[size]> Num(num);
    // num.set(n);
}
tmp inline void erase(T &num, int n) {//将第n+1位设置为0
    num &= ~(1 << n);
    // num.reset(n)
}
tmp inline void empty(T &num) {//转换为空集
    num = 0;
    // num.reset()
}
tmp inline T lowbit(T num) {//显示为1的最低位， 如  lowbit of 110100 == 000100
    return num & (-num);
}
tmp inline T highbit(T num) {//显示为1的最高位， 如  highbit of 0010100 == 10000
    int p = lowbit(num);
    while (p != num) num -= p, p = lowbit(num); //一个一个的移除低位，剩下的便是高位
    return num;
}
tmp inline bool powerOf2(T num) {
    return num && (!(num & (num - 1)));
}
tmp inline T intersection(T num1, T num2) {//交集
    return num1 & num2;
}
tmp inline T tunion(T num1, T num2) {//并集
    return num1 | num2;
}
tmp inline T complementary(T num) {//补集
    return ALL ^ num;
}
tmp bool isSubset(T num1, T num2) {//判断num2是不是num1的子集
    return (num1 & num2) == num2;
}
tmp void enumerate(T num) {//枚举num的子集（包括0和num）
    int subset = num;
    do {
        showBit(subset);
        subset = (subset - 1) & num;
    } while (subset != num);
    // for (int i=0;i<=ALL;i++)
    // {//穷举所有子集
    //     showBit(i);
    // }
}
tmp T tcount(T num) {//数num中的元素个数
    T cnt = 0;
    for (T i = num; i; i >>= 1)
        cnt += i & 1;
    return cnt;
}

int main() {
    // enumerate(ALL);
    bitset<5> num(10);
    cout << num.size() << endl;
    bitset<SIZE> n1("001101100");
    bitset<SIZE> n2("011101000");
    ull a1 = n1.to_ullong();
    ull a2 = n2.to_ullong();
    showBit(a1);
    showBit(a2);
    showBit(highbit(a1));
    showBit(highbit(a2));
    showBit(lowbit(a1));
    showBit(lowbit(a2));
    cout << powerOf2(0) << endl;
    cout << 0x7fffffff << endl;
    return 0;
}