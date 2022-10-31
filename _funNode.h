#pragma once
#include "_funNode_iterator.h"
#include <iostream>
#include <string>
#include <vector>

#if 0
typedef enum __type_of_node__ {
/* 根节点，元素节点，属性节点，值节点 */
  ROOTNODE, ELEMNODE, ATTRIBUTENODE, VALUENODE,
/* 列表节点，头节点，CDATEA节点，注释节点 */
  LISTNODE, HEADNODE, CDATANODE, NOTENODE
}NODETYPE;
#endif

/* -------------------------抽象类Node------------------------- */
class Node{
public:
  virtual ~Node() {}
  virtual const std::string type_str() const = 0;
  const NODETYPE m_type() const { return m_nodeType; }
  Node(NODETYPE nodeType) 
    : m_nodeType(nodeType) {}
private:
  NODETYPE m_nodeType;
};

/* -------------------------属性节点------------------------- */
class AttributeNode : public Node{
  //friend class AttributeNode_iterator;
public:
  const std::string type_str() const { return "ATTRIBUTENODE"; }
  AttributeNode() 
    : Node(ATTRIBUTENODE) {}
  AttributeNode(const AttributeNode &dest) 
    : Node(ATTRIBUTENODE), m_key(dest.m_key), m_words(dest.m_words) {}
  bool add(const std::string &key, const std::string &words);
  void clear() { m_key.clear(); m_words.clear(); }
/* ----迭代器相关---- */
  typedef AttributeNode_iterator iterator;
  AttributeNode_iterator begin() const;
  AttributeNode_iterator end() const;
private:
  std::vector<std::string> m_key;
  std::vector<std::string> m_words;
  bool m_check_key(const std::string &key) const;
};

/* -------------------------值节点------------------------- */
class ValueNode : public Node{
  friend std::ostream& operator<<(std::ostream &os, const ValueNode &dest);
public:
  const std::string type_str() const { return "VALUENODE"; }
  ValueNode() : Node(VALUENODE) {}
  ValueNode(const std::string &value)
    :Node(VALUENODE), m_value(value) {}
  const std::string& value() const;
  void set(const std::string &str) { m_value = str; }
  void add(const std::string &str) { m_value += str; }
  void clear() { m_value.clear(); }

private:
  std::string m_value;
};

/* -------------------------注释节点------------------------- */
class NoteNode : public Node{
  friend std::ostream& operator<<(std::ostream &os, const NoteNode &dest);
public:
  const std::string type_str() const { return "NOTENODE"; }
  NoteNode() : Node(NOTENODE) {}
  NoteNode(const std::string &note)
    : Node(NOTENODE), m_note(note) {}
  const std::string& note() const;

private:
  std::string m_note;
};

/* -------------------------CDATA节点------------------------- */
class CDATANode : public Node{
  friend std::ostream& operator<<(std::ostream &os, const CDATANode &dest);
public:
  const std::string type_str() const { return "CDATANODE"; }
  CDATANode() : Node(CDATANODE) {}
  CDATANode(const std::string &CDATA)
    : Node(CDATANODE), m_CDATA(CDATA) {}
  const std::string& CDATA() const;
private:
  std::string m_CDATA;
};

/* -------------------------元素节点------------------------- */
class ElemNode : public Node{
public:
  const std::string type_str() const { return "ElemNode"; }
  ElemNode() : Node(ELEMNODE) {}
  void clear() {name = 0; attribute = 0; value = 0; list = 0;}
  const std::string &get_name() {return *name;}
public:
  std::string *name = 0;
  AttributeNode *attribute = 0;
  ValueNode *value = 0;
  ListNode *list = 0;
};

/* -------------------------列表节点------------------------- */
class ListNode : public Node{
public:
  const std::string type_str() const { return "LISTNODE"; }
  ~ListNode();
  ListNode() : Node(LISTNODE) {}
  void add(ElemNode *node);
  void clear() { m_list.clear(); }
  ElemNode* elem(const int i) { return m_list[i]; }
  const int size() const { return m_list.size(); }
  ListNode& operator<<(ElemNode *node) { add(node); return *this; }
/* ----迭代器相关---- */
  typedef ListNode_iterator iterator;
  ListNode_iterator begin() const;
  ListNode_iterator end() const;

private:
  std::vector<ElemNode*> m_list;
};
