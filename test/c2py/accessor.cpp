inline long kk;

struct B{ 
  long k;
};

struct A { 
  B b;
  long i;
 public : 

  long const &  get() const { return i;}
  long const &  get_no1() const { return b.k;}
  long const &  get_no2() { i+=1; return i;}
  long const &  get_no3() {return kk;}
  
};

// match the function :
// 
// clang-query> m cxxMethodDecl(has(compoundStmt(has(returnStmt(has(memberExpr().bind("2")))))))

//https://clang.llvm.org/doxygen/classclang_1_1MemberExpr.html
// 2 -> getMemberDecl () ->getName();

// clang-query> m cxxMethodDecl(has(compoundStmt(has(returnStmt(has(memberExpr(has(cxxThisExpr())).bind("2")))))))

