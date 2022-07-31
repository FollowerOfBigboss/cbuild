#include "../cbuild.h"


int main(int argc, char* argv[])
{

  if (argc>1)
  {
    if (strcmp(argv[1], "clean") == 0){


    }
  }

  CallProcess("ls", "");

  string hellofiles[]={
    cso("hello.c")
  };
  createtarget(hello, EXECUTABLE, &createlist(hellofiles), "output/hello");
  compile_target(&hello);
  return 0;
}
