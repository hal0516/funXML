#include "_Cfile.h"

/**/
bool Cfile::m_Fopen_mode(FILE *&fp, const std::string &fileTotalPath, const std::string &mode)
{
  m_Fclose(fp);              //打开前先进行安全关闭
  if( (fp = fopen(fileTotalPath.c_str(), mode.c_str()) ) == 0)
  {
    return false;
  }

  return true;
}

/*安全关闭fp所指文件*/
void Cfile::m_Fclose(FILE *&fp)
{
  if(fp != 0)    //若文件指针不为空，则关闭。避免重复关闭
  {
    fclose(fp);
    fp = 0;
  }
}

bool Cfile::m_FchangeIOMode(FILE *&fp, const std::string &fileTotalPath,\
                            const std::string &mode)
{
  m_Fclose(fp);    //先进行安全关闭
  if(m_Fopen_mode(fp, fileTotalPath, mode) == false)
  /*以mode读写模式重新打开文件*/
  {
    return false;
  }
  return true;
}

/**/
Cfile::~Cfile()
{
  Fclose();
}

Cfile::Cfile() :
  m_fp(0) {}

Cfile::Cfile(const std::string &fileTotalPath):
  m_fp(0)
{
  Fopen(fileTotalPath);
}

bool Cfile::Fopen(const std::string &fileTotalPath)
{
  m_Fclose(m_fp);
  if(m_Fopen_mode(m_fp, fileTotalPath, "r+") == false)
  {
    if(m_Fopen_mode(m_fp, fileTotalPath, "w") == false)
      return false;

    m_Fclose(m_fp);

    if(m_Fopen_mode(m_fp, fileTotalPath, "r+") == false)
      return false;
  }
  m_fileTotalPath = fileTotalPath;
  return true;
}

void Cfile::Fclose()
{
  m_Fclose(m_fp);
}

void Cfile::Fwrite(const std::string &format, ...)
{
  if(m_fp == 0)  return;
  fseek(m_fp, 0, 2);
  va_list arg;
  va_start(arg, format);
  vfprintf(m_fp, format.c_str(), arg);
  va_end(arg);
}

void Cfile::Fwrite_insert(const long offset, const int origin, const std::string &format, ...)
{
  if(m_fp == 0)  return;

  m_writeBuffer.clear();
  m_readBuffer.clear();

  fseek(m_fp, offset, origin);
  char str[1024 + 1];

  va_list arg;
  va_start(arg, format);
  vsprintf(str, format.c_str(), arg);
  va_end(arg);
  m_writeBuffer = str;

  char ch;
  while( (ch = fgetc(m_fp)) != EOF)
  {
    m_readBuffer += ch;
  }

  fseek(m_fp, offset, origin);
  fprintf(m_fp, m_writeBuffer.c_str() ); 
  fprintf(m_fp, m_readBuffer.c_str() );

  m_writeBuffer.clear();  m_readBuffer.clear();
}

void Cfile::Fwrite_cover(const long offset, const int origin, const std::string &format, ...)
{
  if(m_fp == 0)  return;
  fseek(m_fp, offset, origin);
  va_list arg;
  va_start(arg, format);
  vfprintf(m_fp, format.c_str(), arg);
  va_end(arg);
}

const std::string Cfile::Fread() const
{
  std::string tempStr;  tempStr.clear();

  if(m_fp == 0)  return tempStr;

  rewind(m_fp);  char str[301];
  while(1)
  {
    memset(str, 0, sizeof(str) );
    if(fgets(str, 301, m_fp) == 0)  break;
    tempStr += str;
  }
  return tempStr;
}

void Cfile::Fclear()
{
  if(m_fp == 0)  return;
  
  m_FchangeIOMode(m_fp, m_fileTotalPath, "w");
  m_FchangeIOMode(m_fp, m_fileTotalPath, "r+");
}

