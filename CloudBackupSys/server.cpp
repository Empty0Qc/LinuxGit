#include <fstream>
#include <sstream>
#include "httplib.h"
#include <boost_1_69_0/boost/filesystem.hpp>
#include <iostream>

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
      //前面list出现0或者1次都算匹配

      srv.Get("/((list/){0,1}){0,1}",GetFileList);
      srv.Get("/list/(.*)",GetFileData); // * 匹配任意字符 . 匹配任意次
      srv.Put("/list/(.*)",PutFileData);
      srv.listen(SERVER_ADDR,SERVER_PORT);
      return true;
    }
  private:

    static void PutFileData(const Request &req, Response &rsp){
      if(!req.has_header("Range")){
          rsp.status = 400;
          return;
      }
      //has_header 判断是否包含 "*" 字段 
      std::string range = req.get_header_value("Range");
      int64_t range_start;
      if(RangeParse(range,range_start) == false){
        rsp.status = 400;
        return;
      }
      std::string realpath = SERVER_BASE_DIR + req.path;
      std::ofstream file(realpath,std::ios::binary | std::ios::trunc);
      if(!file.is_open()){
        std::cerr << "open file" << realpath << "error\n";
        rsp.status = 500;
        return;
      }
      //参1 ：偏移量 参2 ： 偏移的起始位置
      file.seekp(range_start,std::ios::beg);
      file.write(&req.body[0],req.body.size());
      if(!file.good()){
        std::cerr << "open file" << realpath << "error\n";
        rsp.status = 500;
        return;
      }
      file.close();
      return;
    }
    static bool RangeParse(std::string &range,int64_t &start){
      //Range: bytes=start-end 
      size_t pos1 = range.find("=");
      size_t pos2 = range.find("-");
      if(pos1 == std::string::npos || pos2 == std::string::npos){
        std::cerr << "range:[" << range << "] format error\n";
        return false;
      }
      std::stringstream rs;
      rs << range.substr(pos1 + 1,pos2 - pos1 - 1);
      rs >> start;
      return true;
    }
    static void GetFileList(const Request &req, Response &rsp){
      bf::path list(SERVER_BACKUP_DIR);
      bf::directory_iterator item_begin(list);
      bf::directory_iterator item_end;

      std::string body;
      body = "<html><body><ol><hr />";
      for(;item_begin != item_end; ++item_begin){
        if(bf::is_directory(item_begin->status())){
          continue;
        }
        std::string file = item_begin->path().filename().string();
        std::string uri = "/list/" + file;
        body += "<h4><li>";
        body += "<a href='";
        body += uri;
        body += "'>";
        body += file;
        body += "</a></li></h4>";
        //<h4><li><a href='uri'>file</a></li></h4>
      }
      body += "<hr /></ol></body></html>";
      rsp.set_content(&body[0],"text/html");
      return;
    }
    static void GetFileData(const Request &req,Response &rsp){
      std::cerr << "into GetFileList" << std::endl;
      //1.获取文件真实路径，存在file中
      //2.判断file文件是否存在，不存在直接报错返回 404
      //3.如果文件存在，则通过二进制方式打开，如果文件打开失败，则报错返回 500
      //4.文件存在且正常打开，读取文件大小存入fsize中，然后读到body内
      //5.注意：因为httplib这个库所实现的set_content 文件传送理论上不可大于80m 则我的文件尽量小于其一半，以降低出错概率
      std::string file = SERVER_BASE_DIR + req.path;
      if(!bf::exists(file)){
        std::cerr << "file is not exists" << std::endl;
        rsp.status = 404;
        return;
      }
      std::ifstream ifile(file,std::ios::binary);
      if(!ifile.is_open()){
        std::cerr << "open file" << file << "error\n";
        rsp.status = 500;
        return;
      }
      std::string body;
      int64_t fsize = bf::file_size(file);
      body.resize(fsize);
      ifile.read(&body[0],fsize);
      if(!ifile.good()){
        std::cerr << "read file " << file << "body error\n";
        rsp.status = 500;
        return;
      }
      rsp.set_content(body,"application/octet-stream");
      //md5sum filename
      //windows cmd -------- certutil -hashfile filename  md5
    }
    static void BackupFile(const Request &req,Response &rsp){}
};


int main()
{
  CloudServer srv;
  srv.Start();
  return 0;
}
