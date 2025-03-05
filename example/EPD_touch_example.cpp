#include "predefine.h"
#include "devicelayer.h"

#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include <pthread.h>	//pthread_create()

// 外部引用触摸设备结构体和IIC地址
extern GT1151_Dev Dev_Now, Dev_Old;
// 创建线程变量和标志位，用于控制线程的执行
static pthread_t t1_2in13_V4;
UBYTE flag_t_2in13_V4 = 1;
DeviceLayer deviceLayer;

void Handler_SIGINT(int signo)
{
    printf("\r\nHandler:exit\r\n");
	deviceLayer.epdriver_Sleep(); // 让电子墨水屏进入休眠模式
	deviceLayer.epdriver_Delay(2000);   // 延迟2秒
	flag_t_2in13_V4 = 0;  // 设置线程终止标志
	pthread_join(t1_2in13_V4, NULL); // 等待线程结束
    // 清理资源
    deviceLayer.epdriver_Exit();
    exit(0);             // 退出程序
}
void *pthread_irq_2in13_V4(void *arg)
{
	while(flag_t_2in13_V4) {
		if(DEV_Digital_Read(INT) == 0) { // 如果检测到触摸
			Dev_Now.Touch = 1; // 标记为有触摸
			static size_t i = 0;
			Debug( "Touched: %d\n", i++);
		} else {
			Dev_Now.Touch = 0; // 否则标记为无触摸
			// static size_t i = 0;
			// Debug( "noTouched: %d\n", i++);
			// Debug( "noTouched\n");
		}
		DEV_Delay_ms(100); // 延迟100毫秒
	}
	printf("thread:exit\r\n");
	pthread_exit(NULL);
}
int main()
{
    
    TimeRecorder::TimeRecord record;
    signal(SIGINT, Handler_SIGINT);

    // 初始化设备层
    auto result = deviceLayer.epdriver_Init(InitMode::Hardware);
    if (!result.isSuccess())
    {
        std::cerr << "Failed to initialize hardware: " << result.errormsg() << std::endl;
        return 1;
    }
    // result = deviceLayer.epdriver_Init(InitMode::Full);

    deviceLayer.epdriver_TouchInit();



    pthread_create(&t1_2in13_V4, NULL, pthread_irq_2in13_V4, NULL);

    while(1){
        if(GT_Scan()==1 || (Dev_Now.X[0] == Dev_Old.X[0] && Dev_Now.Y[0] == Dev_Old.Y[0])) {
            continue;
        }
    
        // 如果有新的触摸点，则进行相应操作
        if(Dev_Now.TouchpointFlag) {
            Dev_Now.TouchpointFlag = 0;
            Debug( "enter TouchpointFlag\n");
            // Debug("DEV_Now.X[0] = %d, DEV_Now.Y[0] = %d\n", Dev_Now.X[0], Dev_Now.Y[0]);
            // Debug("DEV_Old.X[0] = %d, DEV_Old.Y[0] = %d\n", Dev_Old.X[0], Dev_Old.Y[0]);
        }
    }


    deviceLayer.epdriver_Sleep();

    

    return 0;
}
