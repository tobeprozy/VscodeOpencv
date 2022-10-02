#include <iostream>
using namespace std;
 
// argc代表参数个数，argv代表实际参数值
// 调用 .exe 时，可传入多个字符串，中间以逗号分隔（传入的值储存在 argv 中）
int main(int argc, char* argv[]) {
    for(int i = 0;i < argc;i++){
        cout << argv[i] << endl;
    }
}