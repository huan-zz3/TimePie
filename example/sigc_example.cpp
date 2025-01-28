#include "predefine.h"

// Result<int> simple_callback(){
void simple_callback(){
    std::cout<< "Simple triggered!" << std::endl;
}

void simple_callback_with_arg(int arg){
    std::cout<< "Simple triggered with arg: " << arg << std::endl;
}

void simple_callback_with_arg_and_return(int &ret, int arg){
    std::cout<< "Simple triggered with arg: " << arg << std::endl;
    ret = arg;
}

class Receiver{
    public:
        void member_callback(int value){
            std::cout<< "Member triggered!: " << value << std::endl;
        }
};
int main(){

    Signal_void signal_simple;
    auto slot_simple = Slot_void(Ptr_fun(simple_callback));
    signal_simple.connect(slot_simple);
    signal_simple.emit();

    Signal_int signal_simple_with_arg;
    auto slot_simple_with_arg = Slot_int(Ptr_fun(simple_callback_with_arg));
    signal_simple_with_arg.connect(slot_simple_with_arg);
    signal_simple_with_arg.emit(42);

    Signal_reint_int signal_simple_with_arg_return;
    auto slot_simple_with_arg_return = Slot_reint_int(Ptr_fun(simple_callback_with_arg_and_return));
    signal_simple_with_arg_return.connect(slot_simple_with_arg_return);
    int ret;
    signal_simple_with_arg_return.emit(ret, 52);
    std::cout << "simple_callback_with_arg_and_return: " << ret << std::endl;

    Receiver receiver;
    Signal_int signal_class_with_arg_receiver;
    auto slot_class_with_arg_receiver = Slot_int(Mem_fun(receiver, Receiver::member_callback));
    signal_class_with_arg_receiver.connect(slot_class_with_arg_receiver);
    signal_class_with_arg_receiver.emit(62);

    return 0;
}