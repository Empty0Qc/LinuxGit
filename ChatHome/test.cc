#include <iostream>
#include "json/json.h"

int main()
{
  std::string nick_name = "chaoqiwen";
  std::string school = "XATU";
  std::string passwd = "123456";

  Json::Value root;
  
  root["name"] = nick_name;
  root["school"] = school;
  root["passwd"] = passwd;

  Json::StyledWriter w;
  std::string s = w.write(root);

  std::cout << s << std::endl;
  return 0;
}
