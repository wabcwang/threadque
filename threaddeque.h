
#include <queue>
#include <cstdlib>
#include <chrono>             // std::chrono::seconds
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

/* ���߳�˫�����ģ�� */
template<class T> class ThreadDeque
{
private:
    deque<T>            m_deque;            //˫�����
    mutex               m_mtx_que;          //˫�������

    condition_variable  m_repo_not_empty;   //֪ͨ���в�Ϊ����������
    mutex               m_mtx_condition;    //������������
    bool                m_isRun;            //�����Ƿ�������

    /* ���ѵȴ�������߳� */
    void notify()
    {
        unique_lock<std::mutex> lock_cond(m_mtx_condition);
        m_repo_not_empty.notify_all(); 
        lock_cond.unlock();
        return;
    }        

public:
    ThreadDeque()
    {
        m_isRun = true;
    }

    ~ThreadDeque()
    {             
        unique_lock<mutex> lock_que(m_mtx_que);
        while (true != m_deque.empty())
        {
            T obj = m_deque.front();
            delete obj;
            m_deque.pop_front();
        }
    }

    /*������ӵ�����β��*/
    bool push_back( T obj)
    {
        /*
        *  1����˫����м����������ڵ���ӵ�����β���������������У������������Χ����
        *  2��֪ͨ���еĵȴ��߳����µ�Ԫ����ӽ�ȥ��
        */

        if ( NULL == obj ){
            return false;
        }        

        unique_lock<std::mutex> lock_que(m_mtx_que);      
        m_deque.push_back(obj);
        lock_que.unlock();        

        notify();
        return true;
    }
    
    /*������ӵ�����ͷ��*/
    bool push_front( T obj)
    {
    
        /*
        *  1����˫����м����������ڵ���ӵ�����ͷ���������������У������������Χ����
        *  2��֪ͨ���еĵȴ��߳����µ�Ԫ����ӽ�ȥ��
        */

        if ( NULL == obj ){
            return false;
        }
        unique_lock<std::mutex> lock_que(m_mtx_que);      
        m_deque.push_front(obj);
        lock_que.unlock(); 
        
        notify();        
        return true;
    }

    /* ������ͷ������,�����ɵ����߸��������ڴ��ͷ� */
    T pop_front()
    {

        /*
        *  1����˫����м��������������������лᱻ����
        *  2��deque��front��pop_front�ȱ��뱣֤���в�Ϊ�ղ��ܵ��ã�������׳��쳣
        *  If the container is not empty, the function never throws exceptions 
        *  (no-throw guarantee).Otherwise, it causes undefined behavior.
        */        

        T  obj = NULL;
        unique_lock<std::mutex> lock_que(m_mtx_que);
        if (true != m_deque.empty())
        {
            obj = m_deque.front();
            m_deque.pop_front();
        }
        return obj;
    }

    /* ������β������,�����ɵ����߸��������ڴ��ͷ�*/
    T pop_back()
    {      

        /*
        *  1����˫����м��������������������лᱻ����
        *  2��deque��pop_back��back�ȱ��뱣֤���в�Ϊ�ղ��ܵ��ã�������׳��쳣
        *  If the container is not empty, the function never throws exceptions 
        *  (no-throw guarantee).Otherwise, it causes undefined behavior.
        */

        T  obj = NULL;
        unique_lock<std::mutex> lock_que(m_mtx_que); 
        if (true != m_deque.empty())
        {
            obj = m_deque.back();
            m_deque.pop_back();
        }
        return obj;
    }

    /* �ȴ����в�Ϊ�գ����Ϊ�ȴ���ʱ�䳤�ȣ���λΪ�� */
    bool wait_for_second(int seconds)
    {
        unique_lock<std::mutex> lock_cond(m_mtx_condition);
        m_repo_not_empty.wait_for(lock_cond,std::chrono::seconds(seconds));
        return m_isRun;
    }

    /* ֪ͨ�߳��˳� */
    void notify_exit()
    {
        unique_lock<std::mutex> lock_cond(m_mtx_condition);
        m_isRun = false;
        m_repo_not_empty.notify_all(); 
        return;
    } 
};



