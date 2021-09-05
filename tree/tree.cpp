#include "tree.h"
#include <cmath>
#include <stack>
//---------------------------------Binary tree Begin------------------------------------------
//DFS
template<typename Tv>
inline int Binary_tree<Tv>::pre_order(Tree_node<Tv>*& root)
{
    if (!root)
        return -1;
    vec.push_back(root->val);
    pre_order(root->left);
    pre_order(root->right);
    return 0;
}

template<typename Tv>
inline int Binary_tree<Tv>::in_order(Tree_node<Tv>*& root)
{
    if (!root)
        return -1;
    in_order(root->left);
    vec.push_back(root->val);
    in_order(root->right);
    return 0;
}

template<typename Tv>
inline int Binary_tree<Tv>::post_order(Tree_node<Tv>*& root)
{
    if (!root)
        return -1;
    post_order(root->left);
    post_order(root->right);
    vec.push_back(root->val);
    return 0;
}

//BFS
template<typename Tv>
inline int Binary_tree<Tv>::layer_order(Tree_node<Tv>*& root)
{
    std::queue<Tree_node<Tv>*> q;
    q.push(root);
    while(!q.empty())
    {
        auto node = q.front();
        q.pop();
        vec.push_back(node->val);
        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
    return 0;
}

// 配套 create_tree 的 recursive_build tag
static struct Default_pre_in_rb {} pre_order_in_rb;
static struct Default_in_post_rb {} post_order_in_rb;

template<typename Tv, typename Tc>
static Tree_node<Tv>* recursive_build(Tc& pre_order, Tc& in_order, std::size_t pre_l, std::size_t pre_r, std::size_t in_l, std::size_t in_r, const int& which_)
{
    if (which_ == 0)
        return recursive_build_internal<Tv, Tc>(pre_order, in_order, pre_l, pre_r, in_l, in_r, pre_order_in_rb);
    if (which_ == 1)
        return recursive_build_internal<Tv, Tc>(pre_order, in_order, pre_l, pre_r, in_l, in_r, post_order_in_rb);
    return nullptr;
}
// ----------------------------------------------------------------------------------------------------

template<typename Tv>
template<typename Tc>
inline Tree_node<Tv>* Binary_tree<Tv>::create_tree_internal(Tc& pre_order, Tc& in_order, Default_pre_in)
{
    // 索引来递归解决
    printf("call 0...");
    std::size_t pre_l = 0, pre_r = pre_order.size() - 1, in_l = 0, in_r = pre_r;
    return recursive_build<Tv, Tc>(pre_order, in_order, pre_l, pre_r, in_l, in_r, 0);
}

template<typename Tv, typename Tc>
static Tree_node<Tv>* recursive_build_internal(Tc& pre_order, Tc& in_order, std::size_t pre_l, std::size_t pre_r, std::size_t in_l, std::size_t in_r, Default_pre_in_rb& pre_order_in_rb)
{
    if (pre_l > pre_r)
        return nullptr;
    
    auto root = new Tree_node<Tv>(pre_order[pre_l]);
    if (!root)
        exit(-1);
    std::size_t i = 0;
    for ( i = in_l; i <= in_r ; i++ )
    {
        if (pre_order[pre_l] == in_order[i])
            break;
    }
    auto left_count = i - in_l;
    root->left = recursive_build_internal<Tv, Tc>(pre_order, in_order, pre_l + 1, pre_l + left_count, in_l, i - 1, pre_order_in_rb);
    root->right = recursive_build_internal<Tv, Tc>(pre_order, in_order, pre_l + left_count + 1, pre_r, i + 1, in_r, pre_order_in_rb);
    return root;
}

// using post-in-order to create tree --------------------------------------------------------------

// 类外 post_order_in 定义, 需要有限定
template<typename Tv>
struct Binary_tree<Tv>::Default_in_post Binary_tree<Tv>::post_order_in;


template<typename Tv>
template<typename Tc>
inline Tree_node<Tv>* Binary_tree<Tv>::create_tree_internal(Tc& post_order, Tc& in_order, Default_in_post)
{
    // 索引来递归解决
    printf("call 1...");
    int in_l = 0, post_l = 0, in_r = in_order.size() - 1, post_r = in_r;
    return recursive_build_internal<Tv, Tc>(post_order, in_order, 0, in_r, 0, post_r, post_order_in_rb);
}

template<typename Tv, typename Tc>
static Tree_node<Tv>* recursive_build_internal(Tc& post_order, Tc& in_order, int in_l, int in_r, int post_l, int post_r, Default_in_post_rb& post_order_in_rb)
{
    if (post_l > post_r)
        return nullptr;
    auto root = new Tree_node<Tv>(post_order[post_r]);
    if (!root)
        exit(-1);
    int i = in_l;
    for(i = in_l; i <= in_r; i++)
    {
        if (in_order[i] == post_order[post_r])
            break;
    }
    auto left_count = i - in_l;
    root->left = recursive_build_internal<Tv, Tc>(post_order, in_order, in_l, i - 1, post_l, post_l + left_count - 1, post_order_in_rb);
    root->right = recursive_build_internal<Tv, Tc>(post_order, in_order, i + 1, in_r, post_l + left_count, post_r - 1, post_order_in_rb);
    return root;
}

//PARENT
template<typename Tv>
inline Tree_node<Tv>* Binary_tree<Tv>::parent(Tree_node<Tv>* root, Tree_node<Tv>* node)
{
    if (!node || root == node)
        return nullptr;
    std::queue<Tree_node<Tv>*> q;
    q.push(root);
    while (!q.empty())
    {
        auto tmp = q.front();
        if (tmp->left == node)
            return tmp;
        else if (tmp->left)
            q.push(tmp->left);
        if (tmp->right == node)
            return tmp;
        else if (tmp->right)
            q.push(tmp->right);
        q.pop();
    }
    return nullptr;
}

//SEARCH
template<typename Tv>
inline Tree_node<Tv>* Binary_tree<Tv>::search(Tree_node<Tv>* root, Tv val)
{
    while (root)
    {
        if (root->val == val)
            return root;
        if (val < root->val)
        {
            root = root->left;
            continue;
        }
        if (val > root->val)
        {
            root = root->right;
            continue;
        }
    }
    return nullptr;
}


//SUCCESSOR Minimum
template<typename Tv>
inline Tree_node<Tv>* Binary_tree<Tv>::minimum(Tree_node<Tv>* node)
{
    // case 0 : node = nullptr
    if (!node)
        return nullptr;

    /* case 1 : node->left == nullptr
         node
        /    \
      null  right
            /   \
    
    */
    if (!node->left)
        return node;
    
    // case 2 : else go to node->left till nullptr
    while (node->left)
    {
        node = node->left;
    }
    return node;
}

template<typename Tv>
inline Tree_node<Tv>* Binary_tree<Tv>::successor(Tree_node<Tv>* node)
{
    // case 1 : node == nullptr
    if (!node)
        return nullptr;
    
    // case 2 : node->right != nullptr
    if (node->right)
        return minimum(node->right);

    auto parnt = parent(root, node);
    if (!parnt)
        return nullptr;
    
    /*  case 3: node->right == null and node->parent->left == node
              parent
              /    \
            node
            /  \
          ...  null  
    */
    if (parnt->left == node)
        return parnt;
    
    /* case 4 : node->right == null and node->parent->right == node
        parent
        /    \
            node
            /  \
          ...  null  
    */
    if (parnt->right == node)
        return nullptr;
    return nullptr;
}

//PREDECESSOR Maximum
template<typename Tv>
inline Tree_node<Tv>* Binary_tree<Tv>::maximum(Tree_node<Tv>* node)
{
    // case 1 : node == nullptr
    if (!node)
        return nullptr;
    
    /* case 2 : node->right == nullptr
         node
        /    \
       left  null
       /  \       
    
    */
    if (!node->right)
        return node;
    
    // case 3 : node->right != nullptr
    while (node->right)
    {
        node = node->right;
    }
    return node;
}

template<typename Tv>
inline Tree_node<Tv>* Binary_tree<Tv>::predecessor(Tree_node<Tv>* node)
{
    if (!node)
        return nullptr;
    
    // case 1: node->left != null
    if (node->left)
        return maximum(node->left);

    auto parnt = parent(root, node);
    if (!parnt)
        return nullptr;

    /*  case 2: node->left == null and node->parent->right == node
        parent
        /   \
            node
            /  \
          null  ...
    
    */
    if (parnt->right == node)
        return parnt;

    /*  case 3: node->left == null and node->parent->left == node
              parent
              /    \
            node
            /  \
          null  ...
    
    */
    if (parnt->left == node)
        return nullptr;
    return nullptr;
}

template<typename Tv>
inline int Binary_tree<Tv>::insertion(Tree_node<Tv>* root, Tree_node<Tv>* node)
{
    auto _parent = root;
    while (root)
    {
        auto t = root;
        if (node->val < root->val)
        {
            _parent = t;
            root = root->left;
            continue;
        }
        if (node->val > root->val)
        {
            _parent = t;
            root = root->right;
            continue;
        }
    }
    if (!_parent) // cant find a proper position to insert
        return -1;
    if (node->val < _parent->val) // insert to the left of parent
        _parent->left = node;
    else // insert to the right of parent
        _parent->right = node;
    printf("insert %d\n", node->val);
    return 0;
}

template<typename Tv>
Tree_node<Tv>* Binary_tree<Tv>::replace(Tree_node<Tv>* &root, Tree_node<Tv>* u, Tree_node<Tv>* v)
{
    // V replace U only consider parent->left or right's change, not V or U's left or right;
    auto p = parent(root, u);
    if (root == u) // if delete root
    {
        root = v; // change new root
    }
    else if (p->left == u)
    {
        p->left = v;
    }
    else // (p->right == u || null)
    {
        p->right = v;
    }
    return u;
}

template<typename Tv>
inline int Binary_tree<Tv>::deletion(Tree_node<Tv>* &root, Tv val)
{
    // successor replacment version (the other one is predecessor version)
    auto node = search(root, val);
    if (!node)
        return -1;
    // case 1,2 : root->left=null or root->right=null
    if (!node->left)
        delete replace(root, node, node->right);
    else if (!node->right)
        delete replace(root, node, node->left);
    else // case 3 : root->left, root->right != null
    {
        auto suc = successor(node);
        // suc 是否拐弯? 是,node->right != suc  否, 则node->right == suc
        if (node->right != suc)
        {
            replace(root, suc, suc->right); // first
            suc->right = node->right;
        }
        // second
        suc->left = node->left;
        //suc->right = node->right;
        delete replace(root, node, suc);
    }
    printf("delete %d\n", val);
    return 0;
}
//---------------------------------Binary tree End------------------------------------------

//--------------------------------------AVL Begin-------------------------------------------

//SUCCESSOR Minimum
template<typename Tv>
inline Avl_node<Tv>* Avl_tree<Tv>::minimum(Avl_node<Tv>* node)
{
    // case 0 : node = nullptr
    if (!node)
        return nullptr;
    // case 1 : node->left == nullptr
    if (!node->left)
        return node;
    // case 2 : else go to node->left till nullptr
    while (node->left) {
        node = node->left;
    }
    return node;
}

template<typename Tv>
inline Avl_node<Tv>* Avl_tree<Tv>::successor(Avl_node<Tv>* node)
{
    // case 1 : node == nullptr
    if (!node)
        return nullptr;
    // case 2 : node->right != nullptr
    if (node->right)
        return minimum(node->right);
    auto parnt = parent(root, node);
    if (!parnt)
        return nullptr;
    // case 3: node->right == null and node->parent->left == node
    if (parnt->left == node)
        return parnt;
    // case 4 : node->right == null and node->parent->right == node
    //if (parnt->right == node)
    //    return nullptr;
    return nullptr;
}

//PREDECESSOR Maximum
template<typename Tv>
inline Avl_node<Tv>* Avl_tree<Tv>::maximum(Avl_node<Tv>* node)
{
    // case 1 : node == nullptr
    if (!node)
        return nullptr;
    // case 2 : node->right == nullptr
    if (!node->right)
        return node;
    // case 3 : node->right != nullptr
    while (node->right) {
        node = node->right;
    }
    return node;
}

template<typename Tv>
inline Avl_node<Tv>* Avl_tree<Tv>::predecessor(Avl_node<Tv>* node)
{
    if (!node)
        return nullptr;
    // case 1: node->left != null
    if (node->left)
        return maximum(node->left);
    auto parnt = parent(root, node);
    if (!parnt)
        return nullptr;
    //  case 2: node->left == null and node->parent->right == node
    if (parnt->right == node)
        return parnt;
    //  case 3: node->left == null and node->parent->left == node
    //if (parnt->left == node)
    //    return nullptr;
    return nullptr;
}

template<typename Tv>
inline Avl_node<Tv>* Avl_tree<Tv>::search(Tv val)
{
    auto ret = this->root;
    while (ret)
    {
        if (val > ret->val)
            ret = ret->right;
        else if (val < ret-val)
            ret = ret->left;
        else
            break;
    }
    if (!ret)
        return nullptr;
    return ret;
}

//DFS
template<typename Tv>
inline int Avl_tree<Tv>::pre_order(Avl_node<Tv>*& root)
{
    if (!root)
        return -1;
    vec.push_back(root->val);
    pre_order(root->left);
    pre_order(root->right);
    return 0;
}

template<typename Tv>
inline int Avl_tree<Tv>::in_order(Avl_node<Tv>*& root)
{
    if (!root)
        return -1;
    in_order(root->left);
    vec.push_back(root->val);
    in_order(root->right);
    return 0;
}

template<typename Tv>
inline int Avl_tree<Tv>::post_order(Avl_node<Tv>*& root)
{
    if (!root)
        return -1;
    post_order(root->left);
    post_order(root->right);
    vec.push_back(root->val);
    return 0;
}

//BFS
template<typename Tv>
inline int Avl_tree<Tv>::layer_order(Avl_node<Tv>*& root)
{
    std::queue<Tree_node<Tv>*> q;
    q.push(root);
    while(!q.empty())
    {
        auto node = q.front();
        q.pop();
        vec.push_back(node->val);
        if (node->left)
            q.push(node->left);
        if (node->right)
            q.push(node->right);
    }
    return 0;
}

template<typename Tv>
inline Avl_node<Tv>* Avl_tree<Tv>::parent(Avl_node<Tv>* root, Avl_node<Tv>* node)
{
    decltype(root) ret = nullptr;
    while (root)
    {
        if (node->val > root->val) {
            ret = root;
            root = root->right;
        }
        else if (node->val < root->val) {
            ret = root;
            root = root->left;
        }
        else
            break;
    }
    if (!root)
        return nullptr;
    return ret;
}

template<typename Tv>
inline int Avl_tree<Tv>::rotate_left(Avl_node<Tv>* node)
{
    /*    node(tmp root)
          /  \
           pivot
            /  \
              ...
              /  \
    */
    auto p = parent(this->root, node);
    auto pivot = node->right;
    node->right = pivot->left;
    if (!p) //node==root
        this->root = pivot;
    else if (p->left == node)
        p->left = pivot;
    else //p->right == node
        p->right = pivot;
    pivot->left = node;
    
    // update balance factor and height. only consider node and pivot, the others won's change
    node->hg = std::max(height(node->left), height(node->right)) + 1;
    pivot->hg = std::max(height(pivot->left), height(pivot->right)) + 1;
    node->bf = balance_factor(node);
    pivot->bf = balance_factor(pivot);
    return 0;
}

template<typename Tv>
inline int Avl_tree<Tv>::rotate_right(Avl_node<Tv>* node)
{
    /*    node
          /
        pivot
         /
        ...
    */
    auto pivot = node->left;
    node->left =  pivot->right;
    auto p = parent(this->root, node);
    if (!p) // node==root
        this->root = pivot;
    else if (p->left == node)
        p->left = pivot;
    else
        p->right = pivot;
    pivot->right = node;

    // update balance factor and height. only consider node and pivot, the others won's change
    node->hg = std::max(height(node->left), height(node->right)) + 1;
    pivot->hg = std::max(height(pivot->left), height(pivot->right)) + 1;
    node->bf = balance_factor(node);
    pivot->bf = balance_factor(pivot);
    return 0;
}

template<typename Tv>
inline int Avl_tree<Tv>::rotate_left_right(Avl_node<Tv>* node)
{
    /*    node
          /
        pivot
           \
           ...
    */
    rotate_left(node->left);
    rotate_right(node);
    return 0;
}

template<typename Tv>
inline int Avl_tree<Tv>::rotate_right_left(Avl_node<Tv>* node)
{
    /*  node
          \
         pivot
          /
         ...
    */
    rotate_right(node->right);
    rotate_left(node);
    return 0;
}

template<typename Tv>
inline int Avl_tree<Tv>::balance_factor(Avl_node<Tv>* node)
{
    if (!node->left) {
        if (!node->right)
            return 0;
        else
            return 0 - node->right->hg - 1;
    }
    else if (!node->right) {
            if (!node->left)
                return 0;
            else
                return node->left->hg + 1;
    }
    else
        return node->left->hg - node->right->hg;
}

template<typename Tv>
inline int Avl_tree<Tv>::height(Avl_node<Tv>* node)
{
    // 此结点高度值, 考虑 处理过程中 node==nullptr 的情形
    if (!node)
        return -1;
    return node->hg;
}

// in Blancing Binary Search Tree
template<typename Tv>
inline int Avl_tree<Tv>::balance(Avl_node<Tv>* node)
{
    // After rotation, if neccessary, functions will update the node's height and balance factor
    // it seems like to process under the nodes in path, which direction is downwards
    if (balance_factor(node) > 1)
    {
        if (balance_factor(node->left) >= 0)
            rotate_right(node);
        else // node->left's BF == -1
            rotate_left_right(node);
    }
    else if (balance_factor(node) < -1)
    {
        if (balance_factor(node->right) <= 0)
            rotate_left(node);
        else // node->right's BF == 1
            rotate_right_left(node);
    }
    return 0;
}

template<typename Tv>
inline int Avl_tree<Tv>::_update_hg_bf(std::stack<Avl_node<Tv>*> path)
{
    /*
    this function process the node's height and bf in path, which are the passing nodes.
    it seems like the processing is upwards
    */
    while (!path.empty())
    {
        auto nd = path.top();
        path.pop();
        auto origin_h = nd->hg;
        nd->hg = std::max(height(nd->left), height(nd->right)) + 1;
        if (origin_h == nd->hg) // optimize!
            break; // height won't change any more, no need to process later nodes
        nd->bf = balance_factor(nd);

        //downwards for nd's hg and bf
        if (nd->bf > 1 || nd->bf < -1)
            balance(nd);
    }
    return 0;
}

// template<typename Tv>
// inline int Avl_tree<Tv>::_update_height(Avl_node<Tv>* node)
// {
//     /*
//     TODO: optimize! 
//     update height when rotate once, may +1 or -1, according to path
//     There recaculate all height in recursion with more time costs
//     */
//     if (!node)
//         return -1;
//     else {
//         node->hg = std::max(_update_height(node->left), _update_height(node->right)) + 1;
//         return node->hg;
//     }
// }

template<typename Tv>
inline int Avl_tree<Tv>::insertion(Avl_node<Tv>* root, Avl_node<Tv>* node)
{
    std::stack<Avl_node<Tv>*> path;
    while (root)
    {
        path.push(root);
        if (node->val > root->val)
            root = root->right;
        else
            root = root->left;
    } // join to path
    // Insert the node
    auto _parent = path.top();
    if (node->val > _parent->val)
        _parent->right = node;
    else
        _parent->left = node;

    // Rebalance the passing nodes stored in stack
    _update_hg_bf(path);

    printf("insert %d\n", node->val);   
    return 0;
}

template<typename Tv>
inline Avl_node<Tv>* Avl_tree<Tv>::replace(Avl_node<Tv>* u, Avl_node<Tv>* v)
{ 
    // v replace u only consier parent's correctness
    auto p = parent(this->root, u);
    if (!p)
        this->root = v;
    else if (p->left == u)
        p->left = v;
    else // p->right == u
        p->right = v;
    return u;
}

template<typename Tv>
inline int Avl_tree<Tv>::deletion(Tv val)
{
    std::stack<Avl_node<Tv>*> path;
    auto nd = this->root;
    // search nd and join the path to stack
    while (nd)
    {
        if (val == nd->val)
            break;
        path.push(nd); // Notice:Not Neccessary to push the node named "nd" that will be replaced into stack
        if (val < nd->val)
            nd = nd->left;
        else
            nd = nd->right;
    }

    if (!nd)
        return -1;
    if (!nd->left)
    {
        delete replace(nd, nd->right); // nd was replaced

        // update path's nodes about height and balance factor
        _update_hg_bf(path);
    }
    else if (!nd->right)
    {
        delete replace(nd, nd->left);
        _update_hg_bf(path);
    }
    else {
        auto suc = successor(nd);
        /* case 1              case 2
             nd                 nd
            /  \               /  \
          ...  suc           ...  right
                 \                /  \
              suc->right         .    .
                 / \            / \     \
                              suc 
                                \
                               suc->right
        */
        // case 1
        path.push(suc); // nd will be replaced by suc

        if (nd->right != suc) // case 2
        {
            auto _ip = nd->right;
            path.push(_ip); // inflection point
            
            while (_ip->left != suc) // join the node before suc to stack
            {
                path.push(_ip);
                _ip = _ip->left;
            }

            // after complete path stack, do the deletion thing
            delete replace(suc, suc->right);
            suc->right = nd->right;
        }
        // case 1
        suc->left = nd->left;
        delete replace(nd, suc);

        // Indeed, in case2, the nd will be replaced by suc
        // So, original nd's all parent nodes won't be affected,
        // fortunately, _update_hg_bf has a detecting mechanism about whether there is a change of height and bf or not, if not, function exits.
        _update_hg_bf(path);
    }
    printf("delete %d\n", val);
    return 0;
}

//--------------------------------------AVL End-------------------------------------------

int main(int argc, char const *argv[])
{
//---------------Binary Tree-----------------
    std::vector<int> pre_order {3,9,20,15,7};
    std::vector<int> in_order {9,3,15,20,7};
    Binary_tree<int> bt0(pre_order, in_order, 0);
    printf("@%p\n", bt0.root);
    bt0.pre_order(bt0.root);
    auto& vec0 = bt0.get_vec();
    printf("pre_order + in_order: ");
    for (auto val : vec0)
        printf("%d ", val);
    printf("\n");

    std::vector<int> in_order1 {3,7,9,15,20};
    std::vector<int> post_order {3,9,20,15,7};
    Binary_tree<int> bt1(post_order, in_order1, 1);
    printf("@%p\n", bt1.root);
    bt1.in_order(bt1.root);
    auto& vec1 = bt1.get_vec();
    printf("post_order + in_order: ");
    for (auto val : vec1)
        printf("%d ", val);
    printf("\n");
    
    auto ret = bt1.search(bt1.root, 15);
    printf("Find value:%d @ %p\n", ret->val, ret);

    auto sor = bt1.successor(ret);
    printf("Value %d's successor is %d\n", ret->val, sor->val);

    auto psor = bt1.predecessor(ret);
    printf("Value %d's predecessor is %d\n", ret->val, psor->val);

    printf("Insertion Operation----------------------------------------------------------\n");
    bt1.get_vec().clear();
    auto new_node1 = new Tree_node<int>(25);
    auto new_node2 = new Tree_node<int>(2);
    auto new_node3 = new Tree_node<int>(10);
    printf("Insert %d...\n", new_node1->val);
    bt1.insertion(bt1.root, new_node1);
    printf("Insert %d...\n", new_node2->val);
    bt1.insertion(bt1.root, new_node2);
    printf("Insert %d...\n", new_node3->val);
    bt1.insertion(bt1.root, new_node3);
    bt1.in_order(bt1.root);
    auto& vec2 = bt1.get_vec();
    printf("After Insertion : in_order...\n");
    for (auto val : vec2)
        printf("%d ", val);
    printf("\n");

    printf("Deletion Operation----------------------------------------------------------\n");
    bt1.get_vec().clear();
    printf("Delete 25...\n");
    bt1.deletion(bt1.root, 25);
    printf("Delete 2...\n");
    bt1.deletion(bt1.root, 2);
    printf("Delete 10..\n");
    bt1.deletion(bt1.root, 10);
    printf("Delete root 7, test passed...\n");
    bt1.deletion(bt1.root, 7); // delete root
    printf("Delete 15...\n");
    bt1.deletion(bt1.root, 15);

    bt1.in_order(bt1.root);
    auto& vec3 = bt1.get_vec();
    printf("After Deletion : in_order...\n");
    for (auto val : vec3)
        printf("%d ", val);
    printf("\n");

//---------------AVL Tree-----------------
    printf("----------------------------AVL Tree----------------------------\n");
    Avl_tree<int> avl{3};
    auto avl_node_2 = new Avl_node<int>(1);
    auto avl_node_1 = new Avl_node<int>(2);
    auto avl_node_0 = new Avl_node<int>(0);
    auto avl_node__1 = new Avl_node<int>(-1);
    /* 
           3                   2                     2               2            2
          /                   / \    insert 0       / \ insert -1   / \ balance  / \
         1     balance ===>  1   3   ===>          1   3  ====>    1   3 ====>  0   3
         \                                        /               /            / \
          2                                      0               0            -1  1
                                                                /
                                                               -1
    */
    printf("Insert %d...\n", avl_node_2->val);
    avl.insertion(avl.root, avl_node_2);
    printf("Insert %d...\n", avl_node_1->val);
    avl.insertion(avl.root, avl_node_1);
    printf("Insert %d...\n", avl_node_0->val);
    avl.insertion(avl.root, avl_node_0);
    printf("Insert %d...\n", avl_node__1->val);
    avl.insertion(avl.root, avl_node__1);
    /* after insertion and rebalance
            2(root)
          /   \
         0     3
        / \
       -1  1
    */
    avl.in_order(avl.root);
    auto& av1_vec = avl.get_vec();
    printf("After Insertion : in_order...\n");
    for (auto val : av1_vec)
        printf("%d ", val);
    printf("\n");

    printf("Delete 1...\n");
    avl.deletion(1);
    printf("Delete 3...\n");
    avl.deletion(3); // root
    avl.get_vec().clear();
    avl.in_order(avl.root);
    auto& av1_vec_d = avl.get_vec();
    printf("After Deletion : in_order...\n");
    for (auto val : av1_vec_d)
        printf("%d ", val);
    printf("\n");

//---------------Black Red Tree-----------------
    printf("-----------------------------END-----------------------------\n");
    return 0;
}
