#include "httplib.h"
#include <boost/filesystem.hpp>

#define SERVER_ADDR "0.0.0.0"
#define SERVER_PORT 9000
#define SERVER_BACKUP_DIR SERVER_BASE_DIR"/list/"
#define SERVER_BASE_DIR "www"
using namespace httplib;
namespace bf = boost::filesystem;

class CloudServer{
  private:
    Server srv;
  public:
    CloudServer(){
      bf::path base_path(SERVER_BASE_DIR);
      if(!bf::exists(base_path)){
        bf::create_directory(base_path);
      }
      bf::path list_path(SERVER_BACKUP_DIR);
      if(!bf::exists(list_path)){
        bf::create_directory(list_path);
      }
    }
    bool Start(){
      srv.set_base_dir(SERVER_BASE_DIR);
      srv.Get("/",GetFileList);
      srv.listen(SERVER_ADDR,SERVER_PORT);
      return true;
    }
  private:
  
    static void GetFileList(const Request &req, Response &rsp){

    }
    static void GetFileData(const Request &req,Response &rsp){}
    static void BackupFile(const Request &req,Response &rsp){}
};


int main()
{
  CloudServer srv;
  srv.Start();
  return 0;
}
