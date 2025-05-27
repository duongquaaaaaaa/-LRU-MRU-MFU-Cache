#include <bits/stdc++.h>

using namespace std;

struct Node {
    int key;
    Node *prev;
    Node *next;
    string value;

    Node(int k, string val) : key(k), next(nullptr), prev(nullptr) {
        value = val;
    }
};

struct LRU_Cache {
    unordered_map<int, Node*> cacheMap;
    int sz;
    int lim;
    Node *head;
    Node *tail;

    LRU_Cache(int LIM) :sz(0), lim(LIM), head(nullptr), tail(nullptr) {
    }

    void removeNode(Node* node) {
        if (node->prev) node->prev->next = node->next;
        else head = node->next;

        if (node->next) node->next->prev = node->prev;
        else tail = node->prev;

        sz--;
    }

    void addNodeToHead(Node* node) {
        node->next = head;
        node->prev = nullptr;
        if (head) head->prev = node;
        head = node;
        if (!tail) tail = node;
        sz++;
    }

    void moveNodeToHead(Node* node) {
        removeNode(node);
        addNodeToHead(node);
    }

    void del_tail() {
            if(!tail)return;
            cacheMap.erase(tail->key);
            removeNode(tail);
    }

    void putCache(int key, string value) {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            Node *node = (*it).second;
            moveNodeToHead(node);
        } else {
            if (sz == lim) {
                del_tail();
            }
            Node* node = new Node(key, value);
            addNodeToHead(node);
            cacheMap[key] = node;
        }
    }

    void getCache(int key) {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            Node *node = (*it).second;
            moveNodeToHead(node);
        }
    }

    void printCache() {
        Node* cur = head;
        cout << "Cache: ";
        while (cur) {
            cout << "(" << cur->key << "," << cur->value << ") ";
            cur = cur->next;
        }
        cout << '\n';
    }
};

LRU_Cache* initCache(int lim) {
    return new LRU_Cache(lim);
}

void put(LRU_Cache* cache, int key, const string value) {
    cache->putCache(key, value);
}

void get(LRU_Cache* cache, int key) {
    cache->getCache(key);
}

void printCache(LRU_Cache* cache) {
    cache->printCache();
}

int main() {
    int CACHE_SIZE = 3;
    LRU_Cache* cache = initCache(CACHE_SIZE);
    put(cache, 1, "Value 1");
    put(cache, 2, "Value 2");
    put(cache, 3, "Value 3");
    printCache(cache);

    get(cache, 2);  // Truy cập 2 -> Đưa 2 lên đầu
    printCache(cache);

    put(cache, 4, "Value 4");
    printCache(cache);

    get(cache, 1);
    return 0;
}
