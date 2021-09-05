#include "linklist.h"
#include "common_node.h"
#include "reverse.h"
#include "bintodec.h"
#include <vector>

int main()
{
  std::vector<int> a1{11}, a2{12};
  node_t<std::vector<int>> arr1[3] = {a1, a2};
  auto p1 = create_linklist_from_vector(arr1, 2);
  auto tail1 = p1;
  while (tail1->next)
  {
    tail1 = tail1->next;
  }
  show_node(p1);

  std::vector<int> b1{21}, b2{22}, b3{23};
  node_t<std::vector<int>> arr2[3] = {b1, b2, b3};
  auto p2 = create_linklist_from_vector(arr2, 3);
  auto tail2 = p2;
  while (tail2->next)
  {
    tail2 = tail2->next;
  }
  show_node(p2);

  std::vector<int> c1{31}, c2{32}, c3{33};
  node_t<std::vector<int>> arr3[3] = {c1, c2, c3};
  auto p3 = create_linklist_from_vector(arr3, 3);
  show_node(p3);
  auto tail3 = p3;
  while (tail3->next)
  {
    tail3 = tail3->next;
  }

  // connect common node
  tail1->next = p3;
  tail2->next = p3;
  
  // show after connecting
  show_node(p1);
  show_node(p2);

  // 1 find common
  auto len1 = 2, len2 = 3;
  auto ret = p1;
  common_node(p1, p2, tail3, len1, len2, ret);
  show_node(ret);

  // 2 reverse list
  show_node(p1);
  auto revlist = reverse(p1);
  show_node(revlist);


  // 3 getDecimalValue
  node_t<int> arr4[3] {1,0,1};
  auto node = create_linklist_from_vector(arr4, 3);
  auto retdec = getDecimalValue(node);
  printf("%d\n", retdec);


  // release
  free_linklist(p1);
  free_linklist(p2);
  free_linklist(p3);
  free_linklist(node);
  return 0;
}

