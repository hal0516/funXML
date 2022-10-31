#include <string>
#include <vector>

class Node;
class RootNode; class ElemNode; class AttributeNode; class ValueNode;
class ListNode; class HeadNodel; class CDATANode; class NoteNode;
typedef enum __type_of_node__ {
  /* 根节点，元素节点，属性节点，值节点 */
  ROOTNODE, ELEMNODE, ATTRIBUTENODE, VALUENODE,
  /* 列表节点，头节点，CDATEA节点，注释节点 */
  LISTNODE, HEADNODE, CDATANODE, NOTENODE
}NODETYPE;

/* -------------------------属性节点迭代器------------------------- */
class AttributeNode_iterator{
public:
  AttributeNode_iterator() {}
  AttributeNode_iterator(const int index, const std::vector<std::string> &key,
                         const std::vector<std::string> &words)
    :m_index(index), m_key(key), m_words(words) {}
  bool operator==(AttributeNode_iterator dest) const;
  bool operator!=(AttributeNode_iterator dest) const;
  const std::string& operator*() const;
  const std::string& operator&() const;
  AttributeNode_iterator& operator++();
  AttributeNode_iterator operator++(int);
private:
  int m_index;
  std::vector<std::string> m_key;
  std::vector<std::string> m_words;
  
};

/* -------------------------列表节点迭代器------------------------- */
class ListNode_iterator{
public:
  ListNode_iterator() {}
  ListNode_iterator(const int index,\
                    const std::vector<ElemNode*> &list)
    : m_index(index), m_list(list) {}
  bool operator==(ListNode_iterator dest) const;
  bool operator!=(ListNode_iterator dest) const;
  ElemNode* operator*() const;
  ListNode_iterator& operator++();
  ListNode_iterator operator++(int);

private:
  int m_index;
  std::vector<ElemNode*> m_list;
};

