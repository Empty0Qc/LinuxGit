#include "httplib.h"
#include <iostream>

void Helloworld(const httplib::Request &req, httplib::Response &rsp)
{
  std::cerr << "Hello " <<std::endl;
  rsp.set_content("<html><h1>Hello World</h1></html>","text/html");
}

int main()
{
  httplib::Server srv;
  srv.set_base_dir("./www");
 
  srv.Get("/",Helloworld);

  srv.listen("0.0.0.0",9000);
  return 0;
}
