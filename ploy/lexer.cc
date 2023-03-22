#include <stack>

#include "lexer.h"

std::ostream &operator<<(std::ostream &out, std::vector<Token> &toks)
{
  for(Token &T : toks) {
    out << T << " ";
  }
  
  return out;
}

std::ostream &operator<<(std::ostream &out, Token t)
{
  // out << t.type << ' ';
  if(t.type == OPAR) {
    out << '(';
  } else if(t.type == CPAR) {
    out << ')';
  } else if(t.type == QUOT) {
    out << '\'';
  } else if(t.type == BOOL) {
    out << (t.b ? "#t" : "#f");
  } else if(t.type == IDENT) {
    out << t.i;
  } else if(t.type == NUM) {
    out << t.n;
  }

  return out;
}


std::ostream &operator<<(std::ostream &out, ttype t)
{
  if(t == BOOL) out << "BOOL";
  else if(t == IDENT) out << "IDENT";
  else if(t == NUM) out << "NUM";
  else if(t == OPAR) out << "OPAR";
  else if(t == CPAR) out << "CPAR";
  else if(t == QUOT) out << "QUOT";
  else if(t == NONE) out << "NONE";
  return out;
}

// read tokens until parentheses are balanced
std::vector<Token> read_tokens(std::istream &in)
{
  int depth = 0;
  std::vector<Token> toks;

  Token T;
  do {
    bool success = nexttoken(in, T);
    if(!success) {
      if(!depth) {
        return toks;
      }
      std::cerr << depth << " unmatched opening parentheses\n";
      exit(1);
    }

    if(T.type == OPAR) {
      depth++;
    } else if(T.type == CPAR) {
      depth--;
    }

    if(depth < 0) {
      std::cerr << "unmatched closing parenthesis\n";
    }

    toks.push_back(T);
  } while(depth || T.type == QUOT);

  return toks;
}

void close_quote(std::vector<Token> &new_toks, std::stack<int> &marks, int &depth)
{
  while(!marks.empty() && (depth == marks.top())) {
    new_toks.push_back(Token{CPAR});
    depth--;
    marks.pop();
  }
}

// '(1 2 '3) -> (quote (1 2 (quote 3)))
std::vector<Token> expand_quote(std::vector<Token> toks)
{
  int depth = 0;
  std::stack<int> marks;

  std::vector<Token> new_toks;
  
  for(Token &T : toks) {
    
    if(T.type == QUOT) {
      new_toks.push_back(Token{OPAR});
      new_toks.push_back(Token{"quote"});
      // std::cerr << new_toks.back().i << std::endl;
      
      depth++;
      marks.push(depth);
    }
    else {
      if(T.type == OPAR)
        depth++;
      else if(T.type == CPAR)
        depth--;
      new_toks.push_back(T);
      close_quote(new_toks, marks, depth);
    }

    // else {
    // }

  }
  close_quote(new_toks, marks, depth);

  return new_toks;
}

// read a token into T
// return true if success
bool nexttoken(std::istream &in, Token &T)
{
  static std::string buf = "";

  if(buf == "") {
    in >> buf;
    if(in.fail()) {
      return false;
    }
  }
  
  int nr = 0; // number of characters read
  
  // #t #f
  if(hasbool(buf)) {
    if(buf[1] == 't') {
      T = Token {true};
    } else {
      T = Token {false};
    }

    nr = 2;
  }

  // '
  else if(hasquote(buf)) {
    T = Token {QUOT};
    nr = 1;
  }
  
  // (
  else if(hasopar(buf)) {
    T = Token {OPAR};
    nr = 1;
  }

  // )
  else if(hascpar(buf)) {
    T = Token {CPAR};
    nr = 1;
  }

  int lint = longestint(buf);
  int lident = longestident(buf);
  
  if((lint >= lident) && lint) {
    int n;
    std::istringstream iss{buf};
    iss >> n;
    T = Token {n};
    nr = lint;
  }

  else if(lident) {
    std::string id;
    for(int i = 0; i < lident; i++) {
      id += buf[i];
    }
    T = Token {id};
    nr = lident;
  }

  if(nr == 0) {
    // if(!buf.empty()) {
      std::cerr << "no tokens in sight: " << buf << std::endl;
      exit(1);
    // }
    // return false;
  }

  // move buffer forward
  buf = buf.substr(nr);

  return true;
}

// boolean identifier integer ' ( )

bool isext(char c)
{
  static const char ext[] = "!$%&*+-./:<=>?@^_~";
  return strchr(ext, c);
}

int longestident(std::string s)
{
  bool hasnondigit = false;
  unsigned long i;
  
  for(i = 0; i < s.size(); i++) {
    if(!isdigit(s[i]) && !isalpha(s[i]) && !isext(s[i])) {
      break;
    }

    if(!isdigit(s[i])) {
      hasnondigit = true;
    }
  }

  if(hasnondigit) {
    return i;
  } else {
    return 0;
  }
}

bool issign(char c)
{
  return (c == '+') || (c == '-');
}

int longestint(std::string s)
{
  if(s.empty()) {
    return 0;
  }

  if(issign(s[0])) {
    if(s.size() == 1 || !isdigit(s[1])) {
      return 0;
    }
  } else if(!isdigit(s[0])) {
    return 0;
  }
  
  unsigned long i;
  for(i = 1; i < s.size(); i++) {
    if(!isdigit(s[i])) {
      break;
    }
  }

  return i;
}

bool hasbool(std::string s)
{
  if(s.size() < 2) return false;
  return (s[0] == '#') && ((s[1] == 'f') || (s[1] == 't'));
}

bool hasquote(std::string s)
{
  if(s.empty()) return false;
  return s[0] == '\'';
}

bool hasopar(std::string s)
{
  if(s.empty()) return false;
  return s[0] == '(';
}

bool hascpar(std::string s)
{
  if(s.empty()) return false;
  return s[0] == ')';
}
