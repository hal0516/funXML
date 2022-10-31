#include "_funNode_iterator.h"


/* -------------------------属性节点迭代器------------------------- */
bool AttributeNode_iterator::operator==(AttributeNode_iterator dest) const
{
  return m_index == dest.m_index;
}

bool AttributeNode_iterator::operator!=(AttributeNode_iterator dest) const
{
  return !(*this == dest);
}

const std::string& AttributeNode_iterator::operator*() const
{
  return m_key[m_index];
}

const std::string& AttributeNode_iterator::operator&() const
{
  return m_words[m_index];
}

AttributeNode_iterator& AttributeNode_iterator::operator++()
{
  ++m_index;
  return *this;
}

AttributeNode_iterator AttributeNode_iterator::operator++(int)
{
  AttributeNode_iterator temp = *this;
  ++m_index;
  return temp;
}

/* -------------------------列表节点迭代器------------------------- */
bool ListNode_iterator::operator==(ListNode_iterator dest) const
{
  return m_index == dest.m_index;
}

bool ListNode_iterator::operator!=(ListNode_iterator dest) const
{
  return !(*this == dest);
}

ElemNode* ListNode_iterator::operator*() const
{
  return m_list[m_index];
}

ListNode_iterator& ListNode_iterator::operator++()
{
  m_index++;
  return *this;
}

ListNode_iterator ListNode_iterator::operator++(int)
{
  ListNode_iterator temp = *this;
  m_index++;
  return temp;
}
