/*
*   Copyright (C) 2016, 王超 [wabcwang] , <wabcwang@gmail.com>.
*   All Rights Reserved.
*/
#include <queue>
#include <cstdlib>
#include <chrono>             // std::chrono::seconds
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

/* 多线程单向对列模板 
*  先入先出
*/
template<class T> class ThreadQue
{
private:
    queue<T>            m_queue;            //单向队列
    mutex               m_mtx_que;          //单向队列锁

    condition_variable  m_repo_not_empty;   //通知队列不为空条件变量
    mutex               m_mtx_condition;    //条件变量的锁
    bool                m_isRun;            //队列是否还在运行
        
    /* 唤醒等待处理的线程 */
    void notify()
    {
        unique_lock<std::mutex> lock_cond(m_mtx_condition);
        m_repo_not_empty.notify_all(); 
        lock_cond.unlock();
        return;
    }
    
public:
    ThreadQue()
    {
        m_isRun = true;
    }

    ~ThreadQue()
    {
        unique_lock<mutex> lock_que(m_mtx_que);
        while (true != m_queue.empty())
        {
            T obj = m_queue.front();
            delete obj;
            m_queue.pop();
        }
    }

    /*将对像加到队列尾部*/
    bool push( T obj)
    {
        /*
        *  1、对双向队列加锁，将将节点添加到队列尾部，主动解锁队列，避免队列锁范围过大
        *  2、通知所有的等待线程有新的元素添加进去。
        */

        if ( NULL == obj ){
            return false;
        }        

        unique_lock<std::mutex> lock_que(m_mtx_que);      
        m_queue.push(obj);
        lock_que.unlock();        

        notify();
        
        return true;
    }

    /* 将对像头部出列,并且由调用者负责对象的内存释放 */
    T pop()
    {

        /*
        *  1、对双向队列加锁，解锁在析构函数中会被调用
        *  2、deque的front、pop_front等必须保证队列不为空才能调用，否则会抛出异常
        *  If the container is not empty, the function never throws exceptions 
        *  (no-throw guarantee).Otherwise, it causes undefined behavior.
        */        

        T  obj = NULL;
        unique_lock<std::mutex> lock_que(m_mtx_que);
        if (true != m_queue.empty())
        {
            obj = m_queue.front();
            m_queue.pop();
        }

        return obj;
    }

    /* 等待队列不为空，入参为等待的时间长度，单位为秒 */
    bool wait_for_second(int seconds)
    {
        unique_lock<std::mutex> lock_cond(m_mtx_condition);
        m_repo_not_empty.wait_for(lock_cond,std::chrono::seconds(seconds));
        return m_isRun;
    }

    /* 通知线程退出 */
    void notify_exit()
    {
        unique_lock<std::mutex> lock_cond(m_mtx_condition);
        m_isRun = false;
        m_repo_not_empty.notify_all(); 
        return;
    }
};



