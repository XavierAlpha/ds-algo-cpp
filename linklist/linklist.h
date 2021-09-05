#pragma once
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <memory>
#include <vector>


// #define print_link_init(link_node_d, link_node_n)                              \
//   printf("Initial Finished at line=%d, data=%d next=%p\n", (__LINE__),         \
//          (link_node_d), (link_node_n))
#define print_link_init(link_node_d, link_node_n) 
// Link_list Related
template <typename P>
// concept As_parameter = std::is_fundamental<P>::value;
concept As_parameter = true;

template <As_parameter Tp> using node_t = Tp;

template <As_parameter Ty>
class List_node
{
public:
  List_node() : val{0}, next{nullptr} { print_link_init(0, nullptr); }
  List_node(node_t<Ty> d) : val{d}, next{nullptr} { print_link_init(val, nullptr); }
  List_node(node_t<Ty> d, List_node<Ty> *n) : val{d}, next{n} { print_link_init(d, n); }
  node_t<Ty> val;
  List_node<Ty> *next;
};

template <As_parameter Ty> class Linklist_mgr {
private:
  std::unique_ptr<List_node<Ty>> _up;
public:
  Linklist_mgr() 
  {
    _up = std::make_unique<List_node>();
  }
  ~Linklist_mgr() 
  {
    _up.release();
    delete _up;
  }
  std::unique_ptr<List_node<Ty>> get() { return _up; }
  List_node<Ty>* release() { return _up.release(); }
};

template <As_parameter Ty>
List_node<Ty> *create_linklist_from_vector(node_t<Ty> arr[], size_t sz) 
{
  auto h = new List_node<Ty>(arr[0]);
  auto tail = h;
  for (size_t i = 1; i < sz; ++i) 
  {
    tail->next = new List_node<Ty>(arr[i]);
    tail = tail->next;
  }
  return h;
}

template<As_parameter Ty>
void free_linklist(List_node<Ty>* ln)
{
  auto p = ln;
  if (p && p->next)
    p = p->next;
  while (p)
  {
    ln->next = nullptr;
    delete ln;
    ln = p;
    p = p->next;
  }
  delete ln;
}

template<As_parameter Ty>
void show_node(List_node<Ty>* tmp)
{
  while (tmp)
  {
    printf("%d\n", tmp->val);
    tmp = tmp->next;
  }
}

template<>
void show_node(List_node<std::vector<int>>* tmp)
{
  while (tmp)
  {
    auto v = tmp->val;
    for (auto val : v)
      printf("%d ", val);
    tmp = tmp->next;
  }
  printf("\n");
}

template<As_parameter Ty>
extern void common_node(List_node<Ty>* p1, List_node<Ty>* p2, size_t len1, size_t len2, List_node<Ty>* &ret);
