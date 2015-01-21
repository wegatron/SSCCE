#include <iostream>
#include <streambuf>
#include <fstream>
#include <locale>
#include <cstdio>
#include <thread>
#include <vector>

using namespace std;

class indentbuf: public streambuf {
public:
  indentbuf(streambuf* sbuf): m_sbuf(sbuf), m_indent(4), m_need(true) {}
  int indent() const { return m_indent; }
  void indent() { m_indent+=4; }
  void deindent() { if(m_indent >= 4) m_indent-= 4;  }
protected:
  virtual int_type overflow(int_type c) {
    if (traits_type::eq_int_type(c, traits_type::eof()))
      return m_sbuf->sputc(c);
    if (m_need)
      {
        fill_n(ostreambuf_iterator<char>(m_sbuf), m_indent, ' ');
        m_need = false;
      }

    if (traits_type::eq_int_type(m_sbuf->sputc(c), traits_type::eof()))
      return traits_type::eof();

    if (traits_type::eq_int_type(c, traits_type::to_char_type('\n')))

      m_need = true;

    return traits_type::not_eof(c);
  }
  streambuf* m_sbuf;
  int m_indent;
  bool m_need;
};

class IndentStream : public ostream {
public:
  IndentStream(ostream &os) : ib(os.rdbuf()), ostream(&ib){}
    ostream& indent(ostream& stream) {
        ib.indent();
        return stream;
    }

  static ostream& deindent(ostream& stream) {
    IndentStream* pIndentStream = dynamic_cast<IndentStream*>(&stream);
    if (pIndentStream != nullptr)
      {
        pIndentStream->ib.deindent();
      }

    return stream;
  }

private:
    indentbuf ib;
};

class CompositOstream final {
public:
  CompositOstream() {}
  void clear() {
    oss_.clear();
  }

  void addOstream(std::ostream* os) {
    oss_.push_back(os);
  }

  template <typename T>
    CompositOstream& operator<<(const T& t) {
    for(std::ostream* os : oss_) {
      (*os) << t;
    }
    return *this;
  }
    CompositOstream& operator<<(std::ostream& (*__pf)(std::ostream&))
    {
      for(std::ostream* os : oss_) {
          __pf(*os);
        }
        return *this;
    }
private:
  CompositOstream(const CompositOstream& cls) {}
  std::vector<std::ostream*> oss_;
};

int main()
{
//    IndentStream is(cout);
//    is << "31 hexadecimal: " << hex << 31 << endl;
//    is << IndentStream::deindent << "31 hexadecimal: " << hex << 31 << endl;
  CompositOstream test;
  std::ofstream ofs ("test.txt", std::ofstream::out);
  test.addOstream(&ofs);
  test << 456 << " hahaha" << std::endl;
    return 0;
}
