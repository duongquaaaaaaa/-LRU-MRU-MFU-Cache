#include <bits/stdc++.h>

using namespace std;

struct Node {
    int key;
    int cnt;
    Node *prev;
    Node *next;
    string value;

    Node(int k, string val) : key(k), cnt(0), next(nullptr), prev(nullptr) {
        value = val;
    }
};

struct MFU_Cache {
    unordered_map<int, Node*> cacheMap;
    int sz;
    int lim;
    Node *head;
    Node *tail;

    MFU_Cache(int LIM) : sz(0), lim(LIM), head(nullptr), tail(nullptr) {
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

    void del_Max() {
        Node *cur=head;
        Node *Max=head;
        while(cur)
        {
        if(Max->cnt<=cur->cnt)Max=cur;
        cur=cur->next;
        }
        cacheMap.erase(Max->key);
        removeNode(Max);
    }

    void putCache(int key, string value) {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            Node *node = (*it).second;
            node->cnt++;
            moveNodeToHead(node);
        } else {
            if (sz == lim) {
                del_Max();
            }
            Node* node = new Node(key, value);
            addNodeToHead(node);
            cacheMap[key] = node;
            node->cnt = 1;
        }
    }

    void getCache(int key) {
        auto it = cacheMap.find(key);
        if (it != cacheMap.end()) {
            Node *node = (*it).second;
            node->cnt++;
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

MFU_Cache* initCache(int lim) {
    return new MFU_Cache(lim);
}

void put(MFU_Cache* cache, int key, const string value) {
    cache->putCache(key, value);
}

void get(MFU_Cache* cache, int key) {
    cache->getCache(key);
}

void printCache(MFU_Cache* cache) {
    cache->printCache();
}

int main() {
    int CACHE_SIZE = 3;
    MFU_Cache* cache = initCache(CACHE_SIZE);
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
