#include "_funNode.h"
#include <iostream>

/* -------------------------属性节点------------------------- */
bool AttributeNode::add(const std::string &key, const std::string &words)
{
  if (m_check_key(key))  return false;
  m_key.push_back(key);
  m_words.push_back(words);
  return true;
}

bool AttributeNode::m_check_key(const std::string &key) const
{
  for (auto iter = m_key.begin(); iter != m_key.end(); ++iter)
    if (*iter == key)
      return true;
  return false;
}
AttributeNode_iterator AttributeNode::begin() const
{
  return AttributeNode_iterator(0, m_key, m_words);
}

AttributeNode_iterator AttributeNode::end() const
{
  return AttributeNode_iterator(m_key.size(), m_key, m_words);
}

/* -------------------------值节点------------------------- */
const std::string& ValueNode::value() const
{
  return m_value;
}

std::ostream& operator<<(std::ostream &os, const ValueNode &dest)
{
  os << dest.m_value;
  return os;
}

/* -------------------------注释节点------------------------- */
const std::string& NoteNode::note() const
{
  return m_note;
}

std::ostream& operator<<(std::ostream &os, const NoteNode &dest)
{
  os << dest.m_note;
  return os;
}

/* -------------------------CDATA节点------------------------- */
const std::string& CDATANode::CDATA() const
{
  return m_CDATA;
}

std::ostream& operator<<(std::ostream &os, const CDATANode &dest)
{
  os << dest.m_CDATA;
  return os;
}

/* -------------------------元素节点------------------------- */


/* -------------------------列表节点------------------------- */
ListNode::~ListNode()
{
  for(int i = 0; i != m_list.size(); ++i)
  {
    delete m_list[i];
  }
}

void ListNode::add(ElemNode *node)
{
  m_list.push_back(node);
}

/* ----迭代器相关---- */
ListNode_iterator ListNode::begin() const
{
  return ListNode_iterator(0, m_list);
}

ListNode_iterator ListNode::end() const
{
  return ListNode_iterator(m_list.size(), m_list);
}
