
#include <queue>
#include <cstdlib>
#include <chrono>             // std::chrono::seconds
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

/* ���̵߳������ģ�� 
*  �����ȳ�
*/
template<class T> class ThreadQue
{
private:
    queue<T>            m_queue;            //�������
    mutex               m_mtx_que;          //���������

    condition_variable  m_repo_not_empty;   //֪ͨ���в�Ϊ����������
    mutex               m_mtx_condition;    //������������
        

public:
    ThreadQue()
    {
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

    /*������ӵ�����β��*/
    bool push( T obj)
    {
        /*
        *  1����˫����м����������ڵ���ӵ�����β���������������У������������Χ����
        *  2��֪ͨ���еĵȴ��߳����µ�Ԫ����ӽ�ȥ��
        */

        if ( NULL == obj ){
            return false;
        }        

        unique_lock<std::mutex> lock_que(m_mtx_que);      
        m_queue.push(obj);
        lock_que.unlock();        

        unique_lock<std::mutex> lock_cond(m_mtx_condition);
        m_repo_not_empty.notify_one(); 
        lock_cond.unlock();
        //std::cout<<"push_back:"<<obj<<"\r\n";
        return true;
    }

    /* ������ͷ������,�����ɵ����߸��������ڴ��ͷ� */
    T pop()
    {

        /*
        *  1����˫����м��������������������лᱻ����
        *  2��deque��front��pop_front�ȱ��뱣֤���в�Ϊ�ղ��ܵ��ã�������׳��쳣
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
        //std::cout<<"pop_front:"<<obj<<"\r\n";
        return obj;
    }

    /* �ȴ����в�Ϊ�գ����Ϊ�ȴ���ʱ�䳤�ȣ���λΪ�� */
    void wait_for_second(int seconds)
    {
        unique_lock<std::mutex> lock_cond(m_mtx_condition);
        m_repo_not_empty.wait_for(lock_cond,std::chrono::seconds(seconds));
        return;
    }
};



