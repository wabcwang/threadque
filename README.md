#多线程队列

* threadque.h 线程单向队列
* threaddeque.h 线程双向队列
* test_que.cpp  单向队列的测试
* test_deque.cpp 双向队列的测试

##运行测试脚本
```
$ g++ -std=c++11  -Wl,--no-as-needed -pthread test_deque.cpp -g
$ ./a.out
wait for thread started
read thread started
write--cmd:0
write--cmd:1
write--cmd:2
write--cmd:3
write--cmd:4
write--cmd:5
write--cmd:6
write--cmd:7
write--cmd:8
write--cmd:9
read--cmd:0
read--cmd:1
read--cmd:2
read--cmd:3
read--cmd:4
read--cmd:5
read--cmd:6
read--cmd:7
read--cmd:8
read--cmd:9
```
