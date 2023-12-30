#include<iostream>

template<typename Key>
class BST{
    struct Node {
        Key value;
        Node *child[2];
        Node(Key value) : value(value) {child[0] = child[1] = NULL;}
        friend std::ostream &operator<<(std::ostream &stream, const Node *t) {
            if (!t) {return stream << "";} 
            else {return stream << " (" << t->child[0] << "[" << t->value << "]" << t->child[1] << ") ";}       
        }
    } *root; 
    Key Key_INF;
    Node *search(Node *&t, Key value) {
        if (!t) {return NULL;}
        if (t->value == value) {return t;}
        return search(t->child[value>t->value], value); 
    }
    Node *insert(Node *t, Key value) {
        if (!t) {return new Node(value);}
        t->child[value>t->value] = insert(t->child[value>t->value], value);
        return t;
    }
    bool erase(Node *t, Key value) {
        if (!t) {return false;}
        Node *c = t->child[value>t->value];
        if (!c) {return false;}
        if (c->value != value) {return erase(c, value);}
        if (!c->child[0] || !c->child[1]) {
            t->child[value>t->value] = c->child[!(c->child[0])];
            delete c;
        } else {
            Node *s = c->child[1], *p = c;
            while (s->child[0]) {
                p = s;
                s = s->child[0];
            }
            Key s_value = s->value;
            erase(p, s_value);
            c->value = s_value;
        }
        return true;
    }
    void free_memory(Node *t) {
        if (!t) return;
        free_memory(t->child[0]);
        free_memory(t->child[1]);
        delete t;
    }
public:
    BST(Key Key_INF = 1<<30) : Key_INF(Key_INF) {root = new Node(Key_INF);}
    void insert(Key value) {root = insert(root, value);}
    Node *search(Key value) {return search(root->child[0], value);}
    bool erase(Key value) {return erase(root, value);}
    friend std::ostream &operator<<(std::ostream &stream, const BST &tree) {
        return stream << tree.root->child[0];
    }
    ~BST() {
        free_memory(root);
        root = NULL;
    }
};
void test() {
    using namespace std;
    BST<int> t{};
    t.insert(1);
    t.insert(5);
    t.insert(6);
    t.insert(2);
    t.insert(7);
    t.insert(4);
    t.insert(9);
    t.insert(0);
    t.insert(3);
    cout << t << endl;
    t.erase(3); // 葉
    t.erase(7); // 右の子のみ
    t.erase(8); // 存在しないキー
    cout << t << endl;
    t.insert(8);
    t.insert(10);
    t.insert(11);
    cout << t << endl;
    t.erase(9); // 左右の子, 右の子は左の子を持たない
    cout << t << endl;
    t.erase(5); // 左右の子, 右の子は左の子を持たない
    cout << t << endl;
    t.erase(6); // 左右の子, 右の子は左の子を持つ
    cout << t << endl;
    t.erase(1); // 根
    cout << t << endl;
    cout << t.search(5) << endl;
    cout << t.search(4) << endl;
    cout << t.search(8) << endl;
}

int main() {
    test();
    return 0;
}