#include <iostream>
#include <string>

#include "GUI.h"
#include "Graph.h"
#include "Simple_window.h"
#include "Window.h"

using std::cout;
using std::endl;

/***********************************************************************************/
// Demo1
// 回调函数演示

/**
 * @brief 按钮的回调函数
 *
 * @param arg1 库自带的，目前用不到
 * @param arg2 Button返回attach到的Window对象的指针，基本也没用
 */
void Demo1CallBack(void* arg1, void* arg2) {
  // 点击按钮之后注意命令行，别看图形界面
  cout << "call back called" << endl;
}

void Demo1() {
  Simple_window win({0, 0}, 300, 300, "Demo1");
  // Button的回调函数必须为void (void*, void*)格式。
  Button button({0, 0}, 50, 20, "try me", Demo1CallBack);
  win.attach(button);
  win.wait_for_button();
}

/***********************************************************************************/
// Demo2
// 回调函数携带数据

/**
 * @brief 按钮回调函数，带参数
 *
 * @param arg1 同Demo1，没什么用
 * @param data_ptr 在构造时传入的参数
 */
void Demo2CallBack(void* arg1, void* data_ptr) {
  int* data = (int*)data_ptr;
  // 按键之后观察命令行
  cout << (*data)++ << endl;
}

void Demo2() {
  Simple_window win({0, 0}, 300, 300, "Demo2");

  int data = 1;
  // ButtonWithPtr能携带一个指针，在回调函数被调用时作为第二个参数传输
  ButtonWithPtr button({0, 0}, 50, 20, "try me", Demo2CallBack, &data);
  win.attach(button);
  win.wait_for_button();
}

/***********************************************************************************/
// Demo3
// 定时器功能

/**
 * @brief 定时器回调函数
 *
 * @param data 上一次调用repeat_timeout或者add_timeout时传入的指针
 */
void Demo3CallBack(void* data) {
  int* now = (int*)data;
  // 注意看命令行
  cout << (*now)++ << endl;
  // 如果需要重复调用，则需要在回调函数内使用repeat_timeout，参数同add_timeout
  Fl::repeat_timeout(1.0, Demo3CallBack, data);
}

void Demo3() {
  Simple_window win({0, 0}, 300, 300, "Demo3");
  int data = 1;
  // 此处不能使用repeat_timeout，否则会出现内存错误
  // 第一个参数等待的时间，单位为秒。第二个参数是回调函数，形式为void
  // cb(void*)类型，最后一个为传输的指针，默认为NULL
  Fl::add_timeout(1.0, Demo3CallBack, &data);
  win.wait_for_button();
}