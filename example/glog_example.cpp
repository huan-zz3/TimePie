//  Usage: g++ glogtest.cpp -o glogtest -lglog
//  reference: * https://blog.csdn.net/Solomon1558/article/details/52558503
//             * https://zhuanlan.zhihu.com/p/26025722

#include <iostream>
#include <string>
#include <glog/logging.h>

int main(int argc, char** argv) {
    FLAGS_alsologtostderr = 1;
    google::InitGoogleLogging(argv[0]);

    //通过SetLogDestination可能没有设置log_dir标志位的方式方便(会遗漏一些日志)
    //google::SetLogDestination(google::GLOG_INFO, "/tmp/today");

    //标志位
    FLAGS_colorlogtostderr=true;  //设置输出颜色
    // FLAGS_v = std::atoi(argv[1]); //设置最大显示等级(超过该等级将不记录log)
    FLAGS_log_dir = "./logs";

    LOG(INFO) << "Found " << google::COUNTER << " arguments!";

    // assert
    // CHECK(access(argv[2], 0) != -1) << "No such file: "<<argv[2];

    LOG(INFO) << "I am INFO!";
    LOG(WARNING) << "I am WARNING!";
    LOG(ERROR) << "I am ERROR!";

    //VLOG用来自定义日志, 可以在括号内指定log级别
    VLOG(1) << "[Custom log(VLOG)] Level 1!";
    VLOG(2) << "[Custom log(VLOG)] Level 2!";
    VLOG(3) << "[Custom log(VLOG)] Level 3!";
    VLOG(4) << "[Custom log(VLOG)] Level 4! This is used for detailed message which need not to be printed each time.";
    VLOG(5) << "[Custom log(VLOG)] Level 5! On this level messages are print as detail as possible for debugging.";
    LOG(FATAL) << "I am FATAL!";
    return 0;
}