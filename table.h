/*
*   Copyright (C) 2016, ���� [wabcwang] , <wabcwang@gmail.com>.
*   All Rights Reserved.
*/
#include <map>
#include <vector>
#include <set>
#include <sstream>


//#define FIELD_SEPARTOR      0x01
//#define ROW_SEPARTOR        0x02

#define FIELD_SEPARTOR      ' '
#define ROW_SEPARTOR        '\n'
class Row
{
private:
    std::map<std::string,std::string> m_row;
    std::pair<std::string,std::string> SPair(const std::string& a,const std::string& b)
    {
        return std::pair<std::string,std::string>(a,b);
    }
public:
    
    std::string getValue(const std::string& key)
    {
        return m_row[key];
    }
    int getInt(const std::string& key);
    long getLong(const std::string& key);    
    float getFloat(const std::string& key);
    double getDouble(const std::string& key);
    void setValue(const std::string& key, const std::string& value);
    void setValue(const std::string& key, int value);
    void setValue(const std::string& key, long value);
    void setValue(const std::string& key, double value);
    void setValue(const std::string& key, float value);
};

class Table
{
private:
    std::vector<Row*>           m_row;
    std::vector<std::string>    m_field;

public:
    Table()
    {
    }
    Table(const char* in,char field_sep=FIELD_SEPARTOR, char row_sep=ROW_SEPARTOR);
    ~Table();
    void deleteRow(int index); /* ɾ��ָ���е���Ϣ��������0��ʼ */    
    void deleteRow(int begin, int end); /* ɾ��������begin��ʼ��end��������Ϣ��end��һ�в�ɾ����������0��ʼ */
    Row* getRow(int index);
    Row* pop_back();
    Row* pop_front();

    void addRow(Row* row)
    {
        m_row.push_back(row);
    }

    bool empty()
    {
        return m_row.empty();
    }
    
    Row* front()
    {
        return m_row.front();
    }
    
    int size()
    {
        return m_row.size();
    }
};
