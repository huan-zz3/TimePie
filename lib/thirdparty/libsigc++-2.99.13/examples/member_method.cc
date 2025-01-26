/* Copyright 2003 - 2016, The libsigc++ Development Team
 *
 *  Assigned to the public domain.  Use as you wish without
 *  restriction.
 */

#include <iostream>
#include <string>

#include <sigc++/sigc++.h>

/**
 * Something 类继承自 sigc::trackable，提供了一个用于打印的信号-槽机制。
 * 该类演示了如何使用 libsigc++ 库来管理信号和槽。
 */
class Something : public sigc::trackable
{
    public:
      Something();

    protected:
      /**
       * 连接到信号的函数，当信号发出时被调用。
       * @param a 信号传递的值，用于打印。
       */
      virtual void on_print(int a);

      /**
       * 定义了打印信号的类型，该信号不返回值且接受一个整数参数。
       */
      using type_signal_print = sigc::signal<void(int)>;

      /**
       * 打印信号对象，用于管理信号的连接和发出。
       */
      type_signal_print signal_print;
};

/**
 * Something 类的构造函数。
 * 将 on_print 成员函数连接到 signal_print 信号，并演示如何断开连接。
 */
Something::Something()
{
  // 将 on_print 成员函数连接到 signal_print 信号。
  auto connection = signal_print.connect(sigc::mem_fun(*this, &Something::on_print));

  // 发出信号，参数为 2。
  signal_print.emit(2);

  // 这不是必须的 - 只是为了演示如何断开连接：
  connection.disconnect();
  // 再次发出信号，参数为 3，以证明连接已经断开。
  signal_print.emit(3);
}

/**
 * 连接到信号的槽函数，当信号发出时被调用。
 * @param a 信号传递的值，用于打印。
 */
void Something::on_print(int a)
{
  std::cout << "on_print 接收到: " << a << std::endl;
}

/**
 * 程序的入口点。
 */
int main()
{
  // 创建 Something 类的一个实例。
  Something something;
  return 0;
}
