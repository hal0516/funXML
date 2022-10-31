#pragma once
#include "_funNode.h"
#include <string>
#include <cstring>

class charStack{
public:
  charStack() : m_top(-1) {}
  bool empty() const { return m_top <= -1; }
  const int top() const { return m_top; }
  const char peek() const;
  bool comp(const char &ch) const;
  void push(const char &ch);
  const char pop();
  const int size() const { return m_top + 1; }
private:
  std::vector<char> m_data;
  int m_top;
};

class elemStack{
public:
  elemStack() : m_top(-1) {}
  bool empty() const { return m_top <= -1; }
  const std::string peekE() const;
  ElemNode* peekP() const;
  bool comp(const std::string &str) const;
  void push(const std::string &str, ElemNode *p);
  void pop();
  const int size() const { return m_top + 1; }
private:
  std::vector<std::string> m_elemName;
  std::vector<ElemNode*> m_elemPointer;
  int m_top;
};


class funxml{
public:
  const ElemNode* operator[] (int index) const;
  bool add(ElemNode *elemnode);
  void display() const;

  std::vector<ElemNode*> elem;
  std::string head;
  std::string root;
};

funxml funxml_receiver(const std::string &str);
void funxml_preprocess(char *str, char *headstr);
void funxml_rmoveroot(char *str, std::string &rootstr);
void funxml_analyser(char *str, funxml &xml);
bool special(const char ch);
const char useEscapeChar(const std::string &str);
const int classifier(funxml &xml, const char ch, long &i,\
                     charStack &charstack, elemStack &elemstack,\
                     ElemNode *&tempElemNode, std::string &tempElemName,\
                     std::string &tempAttributeName, std::string &tempAttributeValue,\
                     AttributeNode *&tempAttributeNode,ListNode *&tempListNode,\
		     std::string &tempValue, std::string &escapeChar);
