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
            else {return stream << " (" << t->child[0] << "[" << t->key <<  "]" << t->child[1] << ") ";}       
        }
    } *root; 
    Node *search(Node *&t, Key key) {
        if (!t) {return nullptr;}
        if (t->key == key) {return t;}
        return search(t->child[key > t->key], key); 
    }
    Node *insert(Node *&t, Key key, bool rnd_flag = true, unsigned priority = 0) {
        if (!t) {return new Node(key, rnd_flag ? rnd.random() : priority);}
        int b = key > t->key;
        t->child[b] = insert(t->child[b], key);
        if (t->child[b]->priority > t->priority) {
            Node *s = t->child[b];
            t->child[b] = s->child[1-b];
            s->child[1-b] = t;
            t = s;
        }
        return t;
    }
    bool erase(Node *&t, Key key) {
        if (!t) {return false;}
        if (key != t->key) {return erase(t->child[key > t->key], key);}
        if (!t->child[0] && !t->child[1]) {
            t = nullptr;
            return true;
        }
        int b = (bool)(t->child[1]);
        Node *s = t->child[b];
        t->child[b] = s->child[1-b];
        s->child[1-b] = t;
        t = s;        
        return erase(s->child[1-b], key);
    }
    void split(Node *t, Key key, Node *&l, Node *&r) {
        root = insert(root, key, false, (unsigned)-1);
        l = root->child[0];
        r = root->child[1];
    }
    void merge(Node *&t, Node *l, Node *r) {
        Key x;
        if (!l || !r) {x = (l) ? max(l) + 1 : min(r) + 1;}
        else {x = (max(l) + min(r)) / 2;}
        t->key = x;
        t->priority = (unsigned)-1;
        t->child[0] = l;
        t->child[1] = r;
        erase(t, x);
    }
public:
    Treap(unsigned seed = 1) : rnd(seed), root(nullptr) {}
    Node *search(Key key) {return search(root, key);}
    void insert(Key key) {root = insert(root, key);}
    bool erase(Key key) {return erase(root, key);}
    Key min(Node *t) {return (t->child[0]) ? min(t->child[0]) : t->key;}
    Key max(Node *t) {return (t->child[1]) ? max(t->child[1]) : t->key;}

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
    t.insert(2);
    t.insert(7);
    t.insert(4);
    t.insert(9);
    t.insert(0);
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