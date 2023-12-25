#include<iostream>
template<typename Key>
struct Node {
    Key value;
    Node<Key> *ch[2];
    Node<Key>(Key value) : value(value) {ch[0] = ch[1] = NULL;}
    friend std::ostream &operator<<(std::ostream &stream, const Node<Key> &t) {
        if (!(&t)) {stream << "";}
        else {stream << " (" << *t.ch[0] << "[" << t.value << "]" << *t.ch[1] << ") ";}       
        return stream;
    }
};
template<typename Key>
struct BST {
    Node<Key> *root;
    BST() {root = NULL;}
    Node<Key> *insert(Node<Key> *t, Key value) {
        if (!t) {return new Node<Key>(value);}
        t->ch[value>t->value] = insert(t->ch[value>t->value], value);
        return t;
    }
    void insert(Key value) {root = insert(root, value);}
    Node<Key> *search(Node<Key> *t, Key value) {
        if (!t) {return NULL;}
        if (t->value == value) {return t;}
        return search(t->ch[value>t->value], value); 
    }
    Node<Key> *search(Key value) {return search(root, value);}
    bool erase(Node<Key> *t, Key value) {
        if (!t) {return false;}
        Node<Key> *c = t->ch[value>t->value];
        if (!c) {return false;}
        if (c->value != value) {return erase(c, value);}
        if (!c->ch[0] || !c->ch[1]) {
            t->ch[value>t->value] = c->ch[!(c->ch[0])];
            delete c;
        } else {
            Node<Key> *s = c->ch[1], *p = c;
            while (s->ch[0]) {
                p = s;
                s = s->ch[0];
            }
            Key s_value = s->value;
            erase(c,s->value);
            c->value = s_value;
        }
        return true;
    }
    bool erase(Key value) {return erase(root, value);}
    ~BST() {
        free_memory(root);
        root = NULL;
    }
    friend std::ostream &operator<<(std::ostream &stream, const BST &tree) {
        stream << *tree.root;
        return stream;
    }
    private:
    void free_memory(Node<Key> *t) {
        if (!t) return;
        free_memory(t->ch[0]);
        free_memory(t->ch[1]);
        delete t;
    }
};
void test() {
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
    std::cout << t << std::endl;
    t.erase(3); // 葉
    t.erase(7); // 右の子のみ
    t.erase(8); // 存在しないキー
    std::cout << t << std::endl;
    t.insert(8);
    t.insert(10);
    t.insert(11);
    std::cout << t << std::endl;
    t.erase(9); // 左右の子, 右の子は左の子を持たない
    std::cout << t << std::endl;
    t.erase(5); // 左右の子, 右の子は左の子を持たない
    std::cout << t << std::endl;
    t.erase(6); // 左右の子, 右の子は左の子を持つ
    std::cout << t << std::endl;
    t.~BST();
}

int main() {
    test();
    return 0;
}