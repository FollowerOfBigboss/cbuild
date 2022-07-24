#include "../cbuild.h"


int main(int argc, char* argv[])
{
  string hellofiles[]={
    cso("hello.c")
  };
  createtarget(hello, EXECUTABLE, &createlist(hellofiles), "output/hello");
  compile_target(&hello);
  return 0;
}
