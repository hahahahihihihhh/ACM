/*
    【模板】双向链表
*/
#include <bits/stdc++.h>

const int MAXN = 100005;

using namespace std;

struct Node {
    int data;
    Node *pre;
    Node *nex;

    Node(int data = -1, Node *pre = NULL, Node *nex = NULL)
            : data(data), pre(pre), nex(nex) {}
};

void link(Node *a, Node *b) {
    a->nex = b;
    b->pre = a;
}

void delink(Node *a, Node *b) {
    a->nex = NULL;
    b->pre = NULL;
}

int main() {//链表 - 数据结构
    Node *head = new Node();
    Node *tail = new Node();
    link(head, tail);
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        Node *node = new Node();
        int num;
        cin >> num;
        node->data = num;
        link(tail->pre, node);
        link(node, tail);
    }
    for (Node *cur = head->nex; cur != tail; cur = cur->nex)
        cout << cur->data << endl;
    return 0;
}