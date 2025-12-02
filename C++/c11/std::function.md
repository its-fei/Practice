# std::function

## 概念:
std::function 是一个函数对象包装器 (Function Wrapper)，它可以存储、复制和调用任何目标可调用对象（包括普通函数、Lambda 表达式、仿函数/函数对象、类的静态/非静态成员函数，以及 std::bind 的结果），只要它们的签名兼容。

简单来说，它提供了一个统一的类型来表示任何类型的函数。


## 使用场景和示例:


| 场景   | 描述 | 示例代码     |
|:-------|:----:|:--------:|
| 函数作为参数 | 将函数（或 Lambda 表达式）作为参数传递给其他函数，实现回调机制或策略模式。   | 回调函数：在图形界面库中，将点击按钮时要执行的动作存储起来。     |
| 统一类型存储 | 将不同类型的可调用对象（函数指针、Lambda、仿函数）存储在一个统一的容器（如 std::vector）中。   | 事件调度器：存储一组等待执行的任务。     |
| 类的成员函数 | 存储类的成员函数，以便稍后调用。   | 多态行为：存储指向不同对象方法的指针。     |



### 示例：回调函数 (Callback)

```
#include <iostream>
#include <functional>
#include <vector>

// 1. 定义一个需要回调的函数
void execute_action(std::function<void(int)> callback) {
    std::cout << "--- 执行操作前 ---" << std::endl;
    int data = 42;
    // 2. 调用外部传入的回调函数
    if (callback) {
        callback(data);
    }
    std::cout << "--- 执行操作后 ---" << std::endl;
}

// 3. 示例：普通函数
void print_result(int value) {
    std::cout << "普通函数回调: 接收到值 " << value << std::endl;
}

void std_function_example() {
    std::cout << "--- 场景一：使用普通函数 ---" << std::endl;
    execute_action(print_result);

    std::cout << "\n--- 场景二：使用 Lambda 表达式 ---" << std::endl;
    // 4. 示例：Lambda 表达式
    auto lambda_callback = [](int v) {
        std::cout << "Lambda 回调: 对值 " << v << " 进行处理." << std::endl;
    };
    execute_action(lambda_callback);
}
```