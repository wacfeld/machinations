#include "sexp.h"
#include "forms.h"
#include "io.h"
#include "defaults.h"
#include "proc.h"

// gets initialized in main
Sexp *the_empty_list;


Sexp *index(Sexp *e, int i)
{
  if(e->atom) {
    std::cerr << "trying to index non-list\n";
    longjmp(repl_start, 1);
  }
  
  if(i == 1) {
    return e->car;
  }

  return index(e->cdr, i-1);
}

// get length of list
int list_len(Sexp *e)
{
  if(e->atom) {
    std::cerr << "cannot get length of non-list\n";
    // exit(1);
    longjmp(repl_start, 1);
  }
  
  else if(e == the_empty_list) {
    return 0;
  }
  
  else {
    return 1 + list_len(e->cdr);
  }
}

// everything except #f is true
bool eval_truth(Sexp *e)
{
  if(!e->atom)
    return true;
  
  if(e->a.type != BOOLEAN)
    return true;
  
  return e->a.boole;
}

Sexp *eval(Sexp *e)
{
  // atom
  if(e->atom) {
    // number, boolean, or procedure evaluates to itself
    if(e->a.type == NUMBER || e->a.type == BOOLEAN || e->a.type == PROCEDURE)
      return e;

    // symbol
    else {
      // lookup in bindings
      std::string &name = e->a.symb;
      if(bindings.count(name)) {
        return bindings[name];
      }
      
      else {
        std::cerr << "name '" << name << "' has no binding\n";
        // exit(1);
        longjmp(repl_start, 1);
      }
    }
  }

  else if(e == the_empty_list) {
    return e;
  }

  // syntactic form
  else if(is_form(e->car)) {
    return eval_form(e);
  }

  // procedure call
  else {
    // evaluate car (should evaluate to procedure)
    Sexp *car = eval(e->car);
    if(!isproc(car)) {
      std::cerr << "car of procedure call is not procedure\n";
      // exit(1);
      longjmp(repl_start, 1);
    }

    // evaluate arguments
    Sexp *cdr = eval_list(e->cdr);

    // call procedure
    return call(car->a.proc, cdr);
  }
}

// evaluate every element in list and return the new list
Sexp *eval_list(Sexp *e)
{
  if(e->atom) {
    std::cerr << "eval_list(): asked to evaluate non-list\n";
  }

  if(e == the_empty_list) {
    return e;
  }
  
  Sexp *newe = new Sexp{false};
  newe->car = eval(e->car);
  newe->cdr = eval_list(e->cdr);

  return newe;
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
      // exit(1);
      longjmp(repl_start, 1);
    }

    return e;
  }

  // list
  else {
    // remove opening and closing parenthesis
    if(toks[0].type != OPAR) {
      std::cerr << "list does not start with '('\n";
      // exit(1);
      longjmp(repl_start, 1);
    }
    toks.erase(toks.begin());

    if(toks.back().type != CPAR) {
      std::cerr << "list does not end with ')'\n";
      // exit(1);
      longjmp(repl_start, 1);
    }
    toks.pop_back();

    // recurse
    return get_list(toks);
  }
}

// true toks contains exactly 1 s-expression
bool solitary(std::vector<Token> toks)
{
  int depth = 0;
  unsigned long i = 0;
  do {
    if(toks[i].type == OPAR)
      depth++;
    else if(toks[i].type == CPAR)
      depth--;
    i++;
  } while(depth);

  return i == toks.size();
}

Sexp *get_list(std::vector<Token> toks)
{

  // base case: empty list
  if(toks.empty()) {
    return the_empty_list;
  }
  
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

  // (a . b) cons dot
  if(first.size() == 1) {
    if(first[0].type == DOT) {
      // check that only one element remaining
      if(!solitary(toks)) {
        std::cerr << "invalid . use\n";
        longjmp(repl_start, 1);
      }

      // recurse down
      Sexp *e = get_sexp(toks);
      return e;
    }
  }

  Sexp *e = new Sexp{false};
  // recurse down
  e->car = get_sexp(first);
  // recurse sideways
  e->cdr = get_list(toks);

  return e;
}

