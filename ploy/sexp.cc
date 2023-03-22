#include "sexp.h"
#include "forms.h"

// gets initialized in main
Sexp *the_empty_list;

std::ostream &operator<<(std::ostream &out, Atom &a)
{
  if(a.type == NUMBER) {
    out << a.num;
  } else if(a.type == SYMBOL) {
    out << a.symb;
  } else if(a.type == BOOLEAN) {
    out << (a.b ? "#t" : "#f");
  }

  return out;
}

void flat_sexp(std::ostream &out, Sexp *e, bool open)
{
  if(e->atom) {
    out << e->a << " ";
  }

  else if(e == the_empty_list) {
    out << ") ";
  }

  else {
    if(open) {
      out << "( ";
    }
    flat_sexp(out, e->car, true);
    flat_sexp(out, e->cdr, false);
  }
}

void put_sexp(std::ostream &out, Sexp *e, int indent)
{
  // indent
  for(int i = 0; i < indent; i++) {
    out << ' ';
  }
  
  if(e == the_empty_list) {
    out << "[/]" << std::endl;
  }

  else if(e->atom) {
    out << e->a << std::endl;
  }

  else {
    out << "[ ]" << std::endl;
    put_sexp(out, e->car, indent+2);
    put_sexp(out, e->cdr, indent+2);
  }
}

std::ostream &operator<<(std::ostream &out, Sexp *e)
{
  flat_sexp(out, e);
  return out;
}

// get length of list
int list_len(Sexp *e)
{
  if(e->atom) {
    std::cerr << "cannot get length of non-list\n";
    exit(1);
  }
  
  else if(e == the_empty_list) {
    return 0;
  }
  
  else {
    return 1 + list_len(e->cdr);
  }
}

Sexp *eval(Sexp *e)
{
  // atom
  if(e->atom) {
    // number or boolean evaluates to itself
    if(e->a.type == NUMBER || e->a.type == BOOLEAN)
      return e;

    // symbol
    else {
      // TODO
      std::cerr << "symbol lookup hasn't been implemented yet\n";
      exit(1);
    }
  }

  // syntactic form
  else if(is_form(e->car)) {
    return eval_form(e);
  }

  // function call
  else {
    // TODO
    std::cerr << "function call hasn't been implemented yet\n";
    exit(1);
  }
}

// convert tokens into sexp
// toks is guaranteed to contain exactly 1 sexp
Sexp *get_sexp(std::vector<Token> toks) {
  // atom
  if(toks.size() == 1) {
    Token &T = toks[0];
    
    Sexp *e = new Sexp(true);
    if(T.type == NUM) {
      e->a = Atom(T.n);
    }

    else if(T.type == IDENT) {
      e->a = Atom(T.i);
    }

    else if(T.type == BOOL) {
      e->a = Atom(T.b);
    }

    else {
      std::cerr << "unrecognized atom token" << T << std::endl;
      exit(1);
    }

    return e;
  }

  // list
  else {
    // remove opening and closing parenthesis
    if(toks[0].type != OPAR) {
      std::cerr << "list does not start with '('\n";
      exit(1);
    }
    toks.erase(toks.begin());

    if(toks.back().type != CPAR) {
      std::cerr << "list does not end with ')'\n";
      exit(1);
    }
    toks.pop_back();

    // recurse
    return get_list(toks);
  }
}

Sexp *get_list(std::vector<Token> toks) {

  // base case: empty list
  if(toks.empty()) {
    return the_empty_list;
  }
  
  Sexp *e = new Sexp{false};
  
  // grab first element of list
  std::vector<Token> first;
  int depth = 0;
  int i = 0;
  do {
    Token &T = toks[i];
    
    if(T.type == OPAR)
      depth++;
    else if(T.type == CPAR)
      depth--;
    
    first.push_back(T);
    
    i++;
  } while(depth);

  // delete first element from toks
  toks.erase(toks.begin(), toks.begin() + i);

  // recurse down
  e->car = get_sexp(first);

  // recurse sideways
  e->cdr = get_list(toks);

  return e;
}

