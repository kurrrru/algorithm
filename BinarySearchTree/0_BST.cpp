#include<iostream>
struct Node {
    int val;
    Node *ch[2];
    Node(int val) : val(val) {ch[0] = ch[1] = NULL;}
    friend std::ostream &operator<<(std::ostream &stream, const Node &t) {
        if (!(&t)) {stream << "";}
        else {stream << " (" << *t.ch[0] << "[" << t.val << "]" << *t.ch[1] << ") ";}       
        return stream;
    }
};
struct BST {
    Node *root;
    BST() {root = NULL;}
    Node *insert(Node *t, int val) {
        if (!t) {return new Node(val);}
        t->ch[val>t->val] = insert(t->ch[val>t->val], val);
        return t;
    }
    void insert(int val) {root = insert(root, val);}
    Node *search(Node *t, int val) {
        if (!t) {return NULL;}
        if (t->val == val) {return t;}
        return search(t->ch[val>t->val], val); 
    }
    Node* search(int val) {return search(root, val);}
    bool erase(Node *t, int val) {
        if (!t) {return false;}
        Node *c = t->ch[val>t->val];
        if (!c) {return false;}
        if (c->val != val) {return erase(c, val);}
        if (!c->ch[0] || !c->ch[1]) {
            t->ch[val>t->val] = c->ch[!(c->ch[0])];
            delete c;
        } else {
            Node *s = c->ch[1], *p = c;
            while (s->ch[0]) {
                p = s;
                s = s->ch[0];
            }
            int s_val = s->val;
            erase(c,s->val);
            c->val = s_val;


            // p->ch[s->val>p->val] = s->ch[1];
            // t->ch[val>t->val] = s;
            // s->ch[0] = c->ch[0];
            // s->ch[1] = c->ch[1];
            // delete c;
        }
        return true;
    }
    bool erase(int val) {return erase(root, val);}
    ~BST() {
        free_memory(root);
        root = NULL;
    }
    friend std::ostream &operator<<(std::ostream &stream, const BST &T) {
        stream << *T.root;
        return stream;
    }
    private:
    void free_memory(Node *t) {
        if (!t) return;
        free_memory(t->ch[0]);
        free_memory(t->ch[1]);
        delete t;
    }
};
void test() {
    BST t = BST();
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