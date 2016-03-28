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
.....
```

#内存数据表映射

* table.h
* table.cpp
* test_table.cpp

##运行测试脚本
```
$ g++ table.cpp test_table.cpp -o table
$ ./table
a:0 b:0 c:0 d:0 e:5.1 
int-e:5
float-e:5.1
double-e:5.1
long-e:5
......
```