#include<iostream>

template<typename Key>
struct Treap {
    struct xorshift {
        unsigned state;
        xorshift(unsigned seed): state(seed) {}
        unsigned random() {
            state ^= state << 13;
            state ^= state >> 17;
            state ^= state << 5;
            return state;
        }
    } rnd;
    struct Node {
        Key key;
        unsigned priority;
        Node *child[2];
        Node(Key key, unsigned priority) : key(key), priority(priority) {child[0] = child[1] = nullptr;}
        friend std::ostream &operator<<(std::ostream &stream, const Node *t) {
            if (!t) {return stream << "";} 
            else {return stream << " (" << t->child[0] << "[" << t->key << /*"," << t->priority <<*/  "]" << t->child[1] << ") ";}       
        }
    } *root; 
    Node *search(Node *&t, Key key) {
        if (!t) {return nullptr;}
        if (t->key == key) {return t;}
        return search(t->child[key > t->key], key); 
    }
    Node *insert(Node *t, Node *item) {
        if (!t) {return item;}
        if (item->priority < t->priority) {
            t->child[item->key > t->key] = insert(t->child[item->key > t->key], item);
            return t;
        }
        split(t, item->key, item->child[0], item->child[1]);
        return item;
    }
    bool erase(Node *&t, Key key) {
        if (!t) {return false;}
        if (key == t->key) {
            merge(t, t->child[0], t->child[1]);
            return true;
        }
        return erase(t->child[key > t->key], key);
    }
    void split(Node *t, Key key, Node *&l, Node *&r) {
        if (!t) {l = r = nullptr;} 
        else if (key > t->key) {
            l = t; 
            split(t->child[1], key, l->child[1], r);
        } else {
            r = t; 
            split(t->child[0], key, l, r->child[0]);
        }
    }
    void merge(Node *&t, Node *l, Node *r) {
        if (!l || !r) {t = l ? l : r;}
        else if (l->priority > r->priority) {
            t = l; 
            merge(t->child[1], l->child[1], r);
        } else {
            t = r; 
            merge(t->child[0], l, r->child[0]);
        }
    }
public:
    Treap(unsigned seed = 1) : rnd(seed), root(nullptr) {}
    Node *search(Key key) {return search(root, key);}
    void insert(Key key) {root = insert(root, new Node(key, rnd.random()));}
    bool erase(Key key) {return erase(root, key);}

    friend std::ostream &operator<<(std::ostream &stream, const Treap &tree) {
        return stream << tree.root;
    }
};
void test() {
    using namespace std;
    Treap<int> t=Treap<int>();
    t.insert(1);
    t.insert(5);
    t.insert(6);
    cout << t << endl;
    t.insert(2);
    t.insert(7);
    t.insert(4);
    cout << t << endl;
    t.insert(9);
    cout << t << endl;
    t.insert(0);
    cout << t << endl;
    t.insert(3);
    cout << t << endl;
    t.erase(3); 
    cout << t << endl;
    t.erase(7); 
    t.erase(8); // 存在しないキー
    cout << t << endl;
    t.insert(8);
    t.insert(10);
    t.insert(11);
    cout << t << endl;
    t.erase(9); 
    cout << t << endl;
    t.erase(5); 
    cout << t << endl;
    t.erase(6); 
    cout << t << endl;
    t.erase(1); 
    cout << t << endl;
    cout << t.search(5) << endl;
    cout << t.search(4) << endl;
    cout << t.search(8) << endl;
}

int main() {
    test();
    return 0;
}