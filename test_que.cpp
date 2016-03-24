// condition_variable::wait_for example
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <chrono>             // std::chrono::seconds
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable, std::cv_status
#include "threadque.h"
#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

#include <unistd.h>

//入队列参数结构
struct SendMsgStruct
{
    int sCmd;   //命令类型
    int sValue; //可以是SQL,一般为字符串内容
};

ThreadQue<SendMsgStruct*> m_vMsgQue;
bool g_bisrun = true;
bool g_bisok = false;

void read_value() {
    
    g_bisok=true;
    std::cout<<"read thread started\r\n";
    while( true == g_bisrun){
        //std::cout<<"read thread waiting....\r\n";
        m_vMsgQue.wait_for_second(2);
        //std::cout<<"read thread reading....\r\n";
        
        SendMsgStruct *tmp = NULL;
        while(NULL != (tmp= m_vMsgQue.pop())){
            std::cout<<"read--cmd:"<<tmp->sCmd<<"\r\n";
            delete tmp;
        }
        int j = (rand() % 10) + 1;
        usleep(j*100000);
        std::cout<<j<<"\r\n";
    }
    return;
}

int main ()
{
    std::thread th (read_value);

    while(true != g_bisok)
    {
        std::cout<<"wait for thread started\r\n";
        usleep(100);
    }
    
    for(int i=0;i <10; i++)
    {
        int j = (rand() % 10)+1;
        SendMsgStruct *tmp=new SendMsgStruct;
        tmp->sCmd= i;
        tmp->sValue = j;
        usleep(j*100000);
        std::cout<<"write--cmd:"<<tmp->sCmd<<"\r\n";
        m_vMsgQue.push(tmp);
    }
    
    sleep(1);

    g_bisrun=false;
    th.join();

    return 0;
}

