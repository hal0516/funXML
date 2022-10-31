/*
 *
 */
#ifndef _C_FILE_H
#define _C_FILE_H
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <string>
#include <vector>

typedef class Cfile
{
private:
  FILE *m_fp;                             //文件指针
  std::string m_fileTotalPath;
  std::string m_writeBuffer;              //写入缓冲
  std::string m_readBuffer;               //读取缓冲
  
private:
  /*以mode读写模式安全打开文件, 
   * 安全打开成功返回true，打开失败返回false
   * 参数fileTotalPath必须为绝对路径*/
  bool m_Fopen_mode(FILE *&fp, const std::string &fileTotalPath,\
		    const std::string &mode);     
  /*安全关闭文件*/
  void m_Fclose(FILE *&fp);    
  /*安全更改文件读写模式为mode
   * 更改成功返回true，更改失败返回false*/
  bool m_FchangeIOMode(FILE *&fp, const std::string &fileTotalPath,\
		       const std::string &mode);    
public:
  ~Cfile();
  Cfile();
  Cfile(const std::string &fileTotalPath);
  bool Fopen(const std::string &fileTotalPath);
  void Fclose();
  void Fwrite(const std::string &format, ...);
  void Fwrite_insert(const long offset, const int origin,\
		     const std::string &format, ...);
  void Fwrite_cover(const long offset, const int origin,\
		    const std::string &format, ...);
  const std::string Fread() const;
  void Fclear();

}*pCfile;

#endif
