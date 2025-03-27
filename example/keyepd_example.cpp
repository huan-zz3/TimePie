#include "keyepd.h"
#include "devicelayer.h"
void printtouch(PointCoordinates point)
{
    printf("x:%d,y:%d\n", point.x, point.y);
}
int main()
{
    auto device = std::make_shared<DeviceLayer>();
    device->epdriver_Init(InitMode::Hardware);
    auto keyepd = std::make_shared<KeyEPD>(device);

    keyepd->signal_touch.connect(Slot_coordinate(Ptr_fun(printtouch)));

    keyepd->startTouchScan();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    keyepd->stopTouchScan();

    std::cout << "keyepd example end" << std::endl;
    return 0;
}