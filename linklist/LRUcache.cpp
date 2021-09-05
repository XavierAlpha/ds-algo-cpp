/**
 *  LRU缓存实现原理: HashTable + 双链表
 * 
 **/

#include <unordered_map>
#include <iostream>
// 双链表

template<typename Tk, typename Tv>
class Double_linked_node
{
public:
    Tk key;
    Tv value;
    Double_linked_node* next;
    Double_linked_node* prev;

    Double_linked_node() : key{0}, value{0}, next{nullptr}, prev{nullptr} { }
    Double_linked_node(Tk _key, Tv _val) : key{_key}, value{_val}, next{nullptr}, prev{nullptr} { }
    Double_linked_node(Tk _key, Tv _val, Double_linked_node* _n, Double_linked_node* _p) : key{_key}, value{_val}, next{_n}, prev{_p} { }
};

template<typename Tk, typename Tv>
class Lru_cache
{
public:
    Lru_cache(unsigned int _capacity) : capacity{_capacity}, size{0}
    {
        head = new Double_linked_node<Tk, Tv>();
        tail = new Double_linked_node<Tk, Tv>();
        head->next = tail;
        tail->prev = head;
    }

    int get(Tk key)
    {
        if (!cache.count(key)) return -1;
        auto node = cache[key];
        move_to_head(node);
        return node->value;
    }

    void put(Tk key, Tv value)
    {
        if (!cache.count(key))
        {
            // 缓存中不存在, 创建结点
            auto node = new Double_linked_node(key, value);
            // 添加进 cache
            cache[key] = node;
            // 该结点位于双链表头,移至最近处
            add_to_head(node);
            ++size;
            if (size > capacity)
            {
                // 超出容量
                auto removed = tail->prev;
                remove_tail();
                cache.erase(removed->key);
                delete removed;
                --size;
            }
        }
        else
        {
            // key 存在, 哈希表定位
            auto node = cache[key];
            node->value = value;
            move_to_head(node);
        }
    }

    void move_to_head(Double_linked_node<Tk, Tv>* node)
    {
        remove_node(node);
        add_to_head(node);
    }

    void remove_node(Double_linked_node<Tk, Tv>* node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    Double_linked_node<Tk, Tv>* remove_tail()
    {
        auto removed = tail->prev;
        remove_node(removed);
        return removed;
    }

    void add_to_head(Double_linked_node<Tk, Tv>* node)
    {
        node->next = head->next;
        node->prev = head;
        node->next->prev = node;
        head->next = node;
    }

    Double_linked_node<Tk, Tv>* get_double_linked_head()
    {
        return head;
    }
    Double_linked_node<Tk, Tv>* get_double_linked_tail()
    {
        return tail;
    }

private:
    std::unordered_map<Tk, Double_linked_node<Tk, Tv>*> cache;
    Double_linked_node<Tk, Tv>* head;
    Double_linked_node<Tk, Tv>* tail;
    unsigned long size;
    unsigned long capacity;
    
};


int main()
{
    unsigned int capcaity = 3;
    Lru_cache<int, int> cache(capcaity);
    cache.put(1,1);
    cache.put(2,2);
    cache.put(3,3);

    auto p = cache.get_double_linked_head()->next;
    while(p!=cache.get_double_linked_tail())
    {
        printf("%d ", p->value);
        
        p = p->next;
    }
    printf("\n");

    cache.get(2); // should reverse 1,2
    p = cache.get_double_linked_head()->next;
    while(p!=cache.get_double_linked_tail())
    {
        printf("%d ", p->value);
        
        p = p->next;
    }
    printf("\n");
    //cache.get(1);
    
    return 0;
}
