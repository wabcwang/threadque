���̶߳���

1��threadque.h �̵߳������
2��threaddeque.h �߳�˫�����
3��test_que.cpp  ������еĲ���
4��test_deque.cpp ˫����еĲ���

���в��Խű�
$ g++ -std=c++11  -Wl,--no-as-needed -pthread test_deque.cpp
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



g++ -std=c++11  -Wl,--no-as-needed -pthread test_que.cpp