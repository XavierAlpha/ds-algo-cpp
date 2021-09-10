#include <cmath>
#include <vector>
#include <queue>
#include <memory>
#include <cstdio>
#include <stack>
#include <string>
#include <map>

template<typename Tv>
class Tree_node
{
public:
    Tv val;
    Tree_node* left;
    Tree_node* right;
    
    Tree_node() : val {0}, left {nullptr}, right {nullptr} { }
    Tree_node(Tv val) : val {val}, left {nullptr}, right {nullptr} { }
    Tree_node(Tv val, Tree_node<Tv>* l, Tree_node<Tv>* r) : val {val}, left {l}, right {r} { }
};

template<typename Tv>
class Binary_tree
{
private:
    struct property
    {
        enum degree { n_0 = 0, n_1 = 0, n_2 = 0 };
        unsigned int node_count;
        unsigned int depth;
    }pt;
    
    std::vector<Tv> vec;
public:
    Tree_node<Tv>* root;

    Binary_tree()
    {
        root = new Tree_node<Tv>();
    }
    // Binary_tree(Tree_node<Tv>* root) : Tree_node(), root {root} { }
    template<typename Tc = std::vector<Tv>>
    Binary_tree(Tc& pre_order, Tc& in_order, const int & which_)
    {
        root = create_tree<Tc>(pre_order, in_order, which_);
    }

    property& get_property() { return pt; }
    std::vector<Tv>& get_vec() { return vec; }
    Tree_node<Tv>*& get_root() { return root; }

    /* ===============遍历树====================*/
    int pre_order(Tree_node<Tv>*&);
    int in_order(Tree_node<Tv>*&);
    int post_order(Tree_node<Tv>*&);
    int layer_order(Tree_node<Tv>*&);

    /* ===============创建树====================*/
    //静态声明, 需类外定义, 或者像第一个在传参时定义临时量 Default_pre_in {}
    //区分创建参数所额外使用的标签
    static struct Default_pre_in { } pre_order_in;
    static struct Default_in_post { } post_order_in;

    // which_ 0或1选择创建方法
    template<typename Tc = std::vector<int>>
    static Tree_node<Tv>* create_tree(Tc& tc, Tc& td, const int & which_)
    {
        if (which_ == 0)
            return create_tree_internal<Tc>(tc, td, Default_pre_in { });
        if (which_ == 1)
            return create_tree_internal<Tc>(tc, td, post_order_in);
        return nullptr;
    }
    // 0
    template<typename Tc = std::vector<int>>
    static Tree_node<Tv>* create_tree_internal(Tc&, Tc&, Default_pre_in);
    // 1
    template<typename Tc = std::vector<int>>
    static Tree_node<Tv>* create_tree_internal(Tc&, Tc&, Default_in_post);

    /* ===============销毁树====================*/
    template<typename Tc = std::vector<int>>
    int delete_tree(Tree_node<Tv>* root) noexcept
    {
        if (!root)
            return 0;
        std::queue<Tree_node<Tv>*> q;
        q.push(root);
        while (!q.empty())
        {
            auto td = q.front();
            if (td->left)
                q.push(td->left);
            if (td->right)
                q.push(td->right);
            q.pop();
            printf("delete %d\n", td->val);
            delete(td);
        }
        return 0;
    }

    // PARENT
    Tree_node<Tv>* parent(Tree_node<Tv>* root, Tree_node<Tv>* node);

    /* ===============二叉搜索树BST查询操作====================*/
    //SEARCH
    Tree_node<Tv>* search(Tree_node<Tv>* root, Tv val);

    //SUCCESSOR
    Tree_node<Tv>* minimum(Tree_node<Tv>* node);
    Tree_node<Tv>* successor(Tree_node<Tv>* node);

    //PREDECESSOR
    Tree_node<Tv>* maximum(Tree_node<Tv>* node);
    Tree_node<Tv>* predecessor(Tree_node<Tv>* node);

    //INSERTION
    int insertion(Tree_node<Tv>* root, Tree_node<Tv>* node);
    
    //DELEETION
    Tree_node<Tv>* replace(Tree_node<Tv>* &root, Tree_node<Tv>* u, Tree_node<Tv>* v);
    int deletion(Tree_node<Tv>* &root, Tv val);

    virtual ~Binary_tree() noexcept {
        delete_tree(root);
        printf("Exit correctly!\n");
    }
};

// -------------------------AVL---------------------------------------
template<typename Tv>
class Avl_node : public Tree_node<Tv>
{
public:
    Tv val;
    int hg; //height
    int bf; //balance factor
    Avl_node<Tv>* left;
    Avl_node<Tv>* right;

    Avl_node() :  val{0}, hg{0}, bf{0}, left{nullptr}, right{nullptr}  { }
    Avl_node(Tv _val) : val{_val}, hg{0}, bf{0}, left{nullptr}, right{nullptr}  { }
    Avl_node(int _hg, int _bf, Tv _val) : val{_val}, hg{_hg}, bf{_bf}, left{nullptr}, right{nullptr} { }
    Avl_node(int _hg, int _bf, Tv _val, Avl_node<Tv>* l, Avl_node<Tv>* r) : val{_val}, hg{_hg}, bf{_bf},left{l}, right{r} { }
};

template<typename Tv>
class Avl_tree
{
private:
    int init_height();
    int _update_hg_bf(std::stack<Avl_node<Tv>*> path);
    std::vector<Tv> vec;
public:
    Avl_node<Tv>* root;
    Avl_tree() = delete;
    Avl_tree(Tv _val) {
        // create AVL through insert
        this->root = new Avl_node<Tv>(0, 0, _val);
        // then init_height
        // if (_update_height() == 0)
        //     printf("Init height finished...");
    }

    // vec
    std::vector<Tv>& get_vec() { return vec; }

    // hg
    int height(Avl_node<Tv>* node);

    // parent
    Avl_node<Tv>* parent(Avl_node<Tv>* root, Avl_node<Tv>* node);

    // SUCCESSOR
    Avl_node<Tv>* minimum(Avl_node<Tv>* node);
    Avl_node<Tv>* successor(Avl_node<Tv>* node);

    // PREDECESSOR
    Avl_node<Tv>* maximum(Avl_node<Tv>* node);
    Avl_node<Tv>* predecessor(Avl_node<Tv>* node);

    //search
    Avl_node<Tv>* search(Tv val);

    // traverse
    int pre_order(Avl_node<Tv>*&);
    int in_order(Avl_node<Tv>*&);
    int post_order(Avl_node<Tv>*&);
    int layer_order(Avl_node<Tv>*&);

    // Rotate
    int rotate_left(Avl_node<Tv>* node);
    int rotate_right(Avl_node<Tv>* node);
    int rotate_left_right(Avl_node<Tv>* node);
    int rotate_right_left(Avl_node<Tv>* node);

    // Balance Factor
    int balance_factor(Avl_node<Tv>* node);

    // in Blancing Binary Search Tree
    int balance(Avl_node<Tv>* node);
    
    // int _update_height(Avl_node<Tv>* node);
    int insertion(Avl_node<Tv>* root, Avl_node<Tv>* node);

    Avl_node<Tv>* replace(Avl_node<Tv>* u, Avl_node<Tv>* v);
    int deletion(Tv val);

    virtual ~Avl_tree() noexcept = default;
};

// -------------------------Black Red---------------------------------------
constexpr bool BLACK = true;
constexpr bool RED = false;
template<typename Tv>
class BR_node
{
public:
    Tv key;
    bool color;
    BR_node<Tv>* left;
    BR_node<Tv>* right;
    BR_node<Tv>* parent;

    BR_node(Tv _key) : key{_key}, color{RED}, left{nullptr}, right{nullptr}, parent{nullptr} { }
    BR_node(Tv _key, bool _color) : key{_key}, color{_color}, left{nullptr}, right{nullptr}, parent{nullptr} { }
    BR_node(Tv _key, bool _color, BR_node<Tv>* _l, BR_node<Tv>* _r, BR_node<Tv>* _p) : key{_key}, color{_color}, left{_l}, right{_r}, parent{_p} { }
};

template<typename Tv>
class Black_Red_tree
{
private:
    std::map<Tv, bool> mp;
    int _rb_fixup_i(BR_node<Tv>*);
    int _rb_fixup_d(BR_node<Tv>*);
public:
    BR_node<Tv>* root;

    Black_Red_tree() : root{nullptr} { }
    Black_Red_tree(Tv _key, BR_node<Tv>* _l, BR_node<Tv>* _r, BR_node<Tv>* _p) { root = new BR_node<Tv>(_key, BLACK, _l, _r, _p); }

    // vec
    std::map<Tv, bool>& get_map() { return mp; }

    std::size_t bh();

    // traverse
    int pre_order(BR_node<Tv>*&);
    int in_order(BR_node<Tv>*&);
    int post_order(BR_node<Tv>*&);
    int layer_order(BR_node<Tv>*&);

    // rotation
    int left_rotate(BR_node<Tv>*);
    int right_rotate(BR_node<Tv>*);

    int insertion(BR_node<Tv>* node);

    BR_node<Tv>* minimum(BR_node<Tv>* node);
    BR_node<Tv>* successor(BR_node<Tv>* node);
    BR_node<Tv>* maximum(BR_node<Tv>* node);
    BR_node<Tv>* predecessor(BR_node<Tv>* node);

    BR_node<Tv>* search(Tv key);
    BR_node<Tv>* replace(BR_node<Tv>* u, BR_node<Tv>* v);
    int deletion(Tv key);

    virtual ~Black_Red_tree() noexcept {
        delete root;
    }
};

// -------------------------Treap---------------------------------------







// -------------------------B Tree---------------------------------------
template<typename Tv>
class B_tree : public virtual Binary_tree<Tv>
{
public:
    Tree_node<Tv>* root;
    int insertion(Tree_node<Tv>* root, Tree_node<Tv>* node) override;
    int deletion(Tree_node<Tv>* &root, Tv val) override;
    ~B_tree() {}   
};

// -------------------------B+ Tree---------------------------------------
template<typename Tv>
class B_puls_tree : public virtual Binary_tree<Tv>
{
public:
    Tree_node<Tv>* root;
    int insertion(Tree_node<Tv>* root, Tree_node<Tv>* node) override;
    int deletion(Tree_node<Tv>* &root, Tv val) override;
    ~B_puls_tree() {}
};
