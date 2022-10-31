#include "_funXML.h"
#include <iostream>
#include <cstdio>

/* -------------------------funXML------------------------- */
const ElemNode* funxml::operator[] (int index) const
{
  if( index < 0 )  index = 0;
  return elem[index];
}

bool funxml::add(ElemNode *elemnode)
{
  elem.push_back(elemnode);
  return true;
}

void print_space(const int num)
{
  for(int i = 0; i < num; ++i)
    std::cout << " ";
}

void vis(ElemNode *node)
{
  static int vis_level = 0;
  vis_level += 2;
  print_space(vis_level);
  std::cout << node->get_name() << std::endl;
  if(node->list == 0)
  {
    vis_level -= 2;
    return;
  }
  for(ListNode::iterator iter = node->list->begin();\
      iter != node->list->end(); ++iter)
  {
    vis(*iter);
  }
  vis_level -= 2;
}

void funxml::display() const
{
  if(!head.empty() )
    std::cout << "Head: " << head << std::endl;
  std::cout << root << "[Root]" << std::endl;
  for(int i = 0; i != elem.size(); ++i)
  {
    vis(elem[i]);
  }
}


funxml funxml_receiver(const std::string &str)
{
  funxml xml;
  char strstream[str.size() + 1]; memset(strstream, 0, sizeof(strstream) );
  strcpy(strstream, str.c_str());

  //预处理 并保存头节点信息
  char strhead[301]; memset(strhead, 0, sizeof(strhead));
  funxml_preprocess(strstream, strhead);
  xml.head = strhead; 

  //消除root节点 并保存root信息
  funxml_rmoveroot(strstream, xml.root);

  //解析各个节点 并保存至xml中
  funxml_analyser(strstream, xml);

  return xml;
}

#if 0
void funxml_preprocess(char *str, char *headstr)
{
  char tempstr[strlen(str) + 1]; memset(tempstr, 0, sizeof(tempstr) );
  char *first, *last;
  first = strchr(str, '<'); last = strrchr(str, '>');

  //判断是否存在头节点
  if( *(first + 1) == '?')
  {
    char *hfirst = first + 2;
    char *hlast = strchr(hfirst, '?'); 
    int len = hlast - hfirst;
    char outstr[len + 1];  memset(outstr, 0, sizeof(outstr) );
    strncpy(outstr, hfirst, len); 
    first = strchr(hlast, '<');
    strncpy(tempstr, first, last - first + 1);
    memset(str, 0, sizeof(str) );
    strcpy(str, tempstr);
    memset(headstr, 0, sizeof(headstr));
    strcpy(headstr, tempstr);
  }
  else
  {
    strncpy(tempstr, first, last - first + 1);
    memset(str, 0, sizeof(str));
    strcpy(str, tempstr);
    return;
  }
  return;
}
#endif

void funxml_preprocess(char *str, char *headstr)
{
  char tempstr[strlen(str) + 1]; memset(tempstr, 0, sizeof(tempstr));
  long first, last;
  first = 0; last = strlen(str) + 1;

  for(;first != last; ++first)
    if(str[first] == '<') break;
  for(;last != first; --last)
    if(str[last] == '>') break;

  if(str[first + 1] == '?')
  {
    long flag = first + 1;
    while(str[++flag] != '?');

    memset(headstr, 0, sizeof(headstr));
    strncpy(headstr, str+2, flag - first - 2);

    first = flag + 1;
    for(;first != last; ++first)
      if(str[first] == '<') break;
    strncpy(tempstr, str + first, last - first + 1);
    memset(str, 0, sizeof(str));
    strcpy(str, tempstr);
  }
  else
  {
    memset(headstr, 0, sizeof(headstr));
    strncpy(tempstr, str + first, last - first + 1); 
    strcpy(str, tempstr);
  }
}

void funxml_rmoveroot(char *str, std::string &rootstr)
{
  std::string tempstr(str);
  long rootstart = tempstr.find('<');
  long rootend = tempstr.find('>');
  rootstr = tempstr.substr(rootstart + 1, rootend - rootstart - 1);
  rootstart = tempstr.find('<', rootend);
  rootend = tempstr.rfind('<');
  memset(str, 0, sizeof(str));
  strcpy(str, tempstr.substr(rootstart, rootend - rootstart - 1).c_str() );
}

void funxml_analyser(char *str, funxml &xml)
{
  charStack charstack;
  elemStack elemstack;

  std::string tempElemName;
  std::string tempAttributeName;
  std::string tempAttributeValue;
  ElemNode *tempElemNode = 0;
  AttributeNode *tempAttributeNode = 0;
  ListNode *tempListNode = 0;
  std::string tempValue;
  std::string escapeChar;

  const long charstart = 0; const long charend = strlen(str) + 1;
  long i;
  for(i = charstart; i != charend; i++)
  {
    char ch = str[i];
    int flag = -1;
    flag = classifier(xml, ch, i,\
	              charstack, elemstack,\
	              tempElemNode, tempElemName,\
	              tempAttributeName, tempAttributeValue,\
	              tempAttributeNode, tempListNode,\
		          tempValue, escapeChar);

    switch(flag)
    {
      case -1:
	std::cerr << "Wrong!\n";
      case 0:
	break;
      case 1:
	charstack.push(ch);
	break;
      case 2:
	tempElemName += ch;
	break;
      case 3:
	charstack.pop();
	tempElemNode = new ElemNode;
	tempElemNode->name = new std::string(tempElemName);
	tempElemNode->attribute = tempAttributeNode;
	elemstack.push(tempElemName, tempElemNode);

	tempAttributeNode = 0; tempElemNode = 0;
	tempElemName.clear(); tempAttributeName.clear();
	tempAttributeName.clear();
	break;
      case 4:
	tempValue += ch;
	break;
      case 5:
	i = i + elemstack.peekE().length() + 1;
	tempElemNode = elemstack.peekP();
	elemstack.pop();
	charstack.pop();
	if(elemstack.empty() )
	{
	  xml.elem.push_back(tempElemNode);
	  tempElemNode = 0;
	}
	else
	{
	  if(elemstack.peekP()->list == 0)
	    elemstack.peekP()->list = new ListNode;
	  elemstack.peekP()->list->add(tempElemNode);
	  tempListNode = 0;
	  tempElemNode = 0;
	}
	break;
      case 6:
	charstack.push(ch);
	break;
      case 7:
	escapeChar += ch;
	break;
      case 8:
	charstack.pop();
	tempValue += useEscapeChar(escapeChar);
	escapeChar.clear();
	break;
      case 9:
	charstack.push(ch);
	elemstack.peekP()->value = new ValueNode(tempValue);
	tempValue.clear();
	break;
      case 10:
	charstack.pop();
	while(str[i] != '>')
	  i++;
	break;
      case 11:
	charstack.push(ch);
	break;
      case 12:
	tempAttributeName += ch;
	break;
      case 13:
	charstack.pop();
	break;
      case 14:
	charstack.push(ch);
	break;
      case 15:
	tempAttributeValue += ch;
	break;
      case 16:
	charstack.pop();
	if(tempAttributeNode == 0)
  	  tempAttributeNode = new AttributeNode;
	tempAttributeNode->add(tempAttributeName, tempAttributeValue);
	tempAttributeName.clear();
	tempAttributeValue.clear();
	break;
      case 17:
	break;
      case 18:
	tempValue += ch;
	break;
      default:
	//调试时开启
	//std::cerr << flag << " 溢出啦！\n";
	break;
    }  // switch(flag)

    // 调试时使用
    #if 0
    printf("%c", ch);
    std::cout << ":" << flag << " " << std::endl;
    #endif

  }  // for 
}  //funxml_analyser(char *str, funxml &xml)


bool special(const char ch)
{
  if(ch == '<' || ch == '>'|| \
     ch == ' ' || ch == '='|| \
     ch == '&' || ch == ';'|| \
     ch == '!' || ch == '"'|| \
     ch == '-' || ch == '/'|| \
     ch == '[' || ch == ']')
  {
    return true;
  }
  return false;
}

const char useEscapeChar(const std::string &str)
{
  if(str == "lt")
    return '<';
  else if(str == "gt")
    return '>';
  else if(str == "amp")
    return '&';
  else if(str == "apos")
    return '\'';
  else if(str == "quot")
    return '\"';
  else 
    return 0;
}

const int classifier(funxml &xml, const char ch, long &i,\
                     charStack &charstack, elemStack &elemstack,\
                     ElemNode *&tempElemNode, std::string &tempElemName,\
                     std::string &tempAttributeName, std::string &tempAttributeValue,\
                     AttributeNode *&tempAttributeNode, ListNode *&tempListNode,\
		     std::string &tempValue, std::string &escapeChar)
{
  if(ch == '\t' || ch == '\n' || ch == '\r') // 0 
  {
    return 0;
  }
  else
  {
    if(special(ch) )        // 1
    {
      if(charstack.empty() )   // 2
      {
	if(elemstack.empty() )   // 3
	{
	  if(ch == '<')     // 4
	    return 1;
	  else if(ch == ' ')
	    return 17;
	  else 
	    return 99;
	}
	else                  // 3 NO
	{
	  if(ch == '<')  // 5
	    return 9;
	  else if(ch == '&')
	    return 6;
	  else if(ch == ' ')
	    return 18;
	  else
	    return 98;
	}
      }
      else  // 2 NO
      {
	if(charstack.peek() == '<')  // 6
	{
	  if(ch == '>')        // 7
	    return 3;
	  else if(ch == '\"')
	    return 14;
	  else if(ch == '/')
	    return 5;
	  else if(ch == '!')
	    return 10;
	  else if(ch == ' ')
	    return 11;
	  else
	    return 97;
	}
	else if(charstack.peek() == '&')
	{
	  if(ch == ';')   // 8
	    return 8;
	  else
	    return 96;
	}
	else if(charstack.peek() == ' ')
	{
	  if(ch == '=')    //  9
	    return 13;
	  else
	    return 95;
	}
	else if(charstack.peek() == '\"')
	{
	  if(ch == '\"')
	    return 16;
	  else
	    return 94;
	}
	else
	  return 93;
      }
    }
    else  // 1 NO
    {
      if(charstack.empty() )  // 11
      {
	if(elemstack.empty() )  // 12
	{
	  return 93;
	}
	else             // 12 NO
	{
	  return 4;
	}
      }
      else  // 11 NO
      {
	if(charstack.peek() == '\"')
	  return 15;
	else if(charstack.peek() == ' ')
	  return 12;
	else if(charstack.peek()  == '&')
	  return 7;
	else if(charstack.peek() == '<')
	  return 2;
	else
	  return 92;
      }
    }
  }

}  // classifier()

/* -------------------------charStack------------------------- */
const char charStack::peek() const
{
  if(!empty() )
    return m_data[m_top];
  return 0;
}

bool charStack::comp(const char &ch) const
{
  if(empty() )  return false;
  return peek() == ch;
}

void charStack::push(const char &ch)
{
  m_data.push_back(ch);
  m_top++;
}

const char charStack::pop()
{
  if(!empty() )
  {
    char tempchar = peek();
    m_data.pop_back();
    --m_top;
    return tempchar;
  }
  return 0;
}

/* -------------------------elemStack------------------------- */
const std::string elemStack::peekE() const
{
  if(!empty())
    return m_elemName[m_top];
  return std::string();
}

ElemNode* elemStack::peekP() const
{
  if(!empty())
    return m_elemPointer[m_top];
  return 0;
}

bool elemStack::comp(const std::string &str) const
{
  if(empty()) return false;
  return str == m_elemName[m_top];
}

void elemStack::push(const std::string &str, ElemNode *p)
{
  m_elemName.push_back(str);
  m_elemPointer.push_back(p);
  m_top++;
}

void elemStack::pop()
{
  if(!empty())
  {
    m_elemName.pop_back();
    m_elemPointer.pop_back();
    --m_top;
  }
  return;
}
