#include <Windows.h>
#include <iostream>
#include <boost/container/small_vector.hpp>
#include <boost/thread.hpp>
#include <boost/foreach.hpp>
static int n;
static int sleepTime;

void worker(boost::container::small_vector<int, 10000> iArr) {
    boost::container::small_vector<int, 10000> newArr = iArr;
    for (int i = 0; i < n; i++) {
        if (newArr[i] % 10 == 1) {
            std::cout << newArr[i] << std::endl;
        }
        boost::this_thread::sleep(boost::posix_time::milliseconds(sleepTime));
    }
}
int main() {
    std::cin >> n;
    boost::container::small_vector<int, 10000> newArr;
    for (int i = 0; i < n; i++) {
        int temp;
        std::cin >> temp;
        newArr.push_back(temp);
    }
    sleepTime = 10;
    boost::thread Worker(worker, newArr);
    Worker.join();
    return 0;
}