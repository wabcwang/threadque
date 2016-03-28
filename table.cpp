/*
*   Copyright (C) 2016, 王超 [wabcwang] , <wabcwang@gmail.com>.
*   All Rights Reserved.
*/
#include "table.h"

int Row::getInt(const std::string& key)
{
    int iret = 0;
    std::stringstream stream(m_row[key]);  
    stream>>iret; 
    return iret;
} 

long Row::getLong(const std::string& key)
{
    long lret = 0;
    std::stringstream stream(m_row[key]);  
    stream>>lret; 
    return lret;
}

float Row::getFloat(const std::string& key)
{
    float fret = 0;
    std::stringstream stream(m_row[key]);  
    stream>>fret; 
    return fret;
}

double Row::getDouble(const std::string& key)
{
    double dret = 0;
    std::stringstream stream(m_row[key]);  
    stream>>dret; 
    return dret;
}

void Row::setValue(const std::string& key, const std::string& value)
{
    m_row.insert(SPair(key,value));
    return;
}

void Row::setValue(const std::string& key, int value)
{
    std::stringstream value_stream;  
    value_stream<<value;
    m_row.insert(SPair(key,value_stream.str()));
    return;
}

void Row::setValue(const std::string& key, long value)
{
    std::stringstream value_stream;  
    value_stream<<value;
    m_row.insert(SPair(key,value_stream.str()));
    return;
}

void Row::setValue(const std::string& key, double value)
{
    std::stringstream value_stream;  
    value_stream<<value;
    m_row.insert(SPair(key,value_stream.str()));
    return;
}

void Row::setValue(const std::string& key, float value)
{
    std::stringstream value_stream;  
    value_stream<<value;
    m_row.insert(SPair(key,value_stream.str()));
    return;
}

std::string& trim(std::string &s)   
{  
    if (s.empty())   
    {  
        return s;  
    }  
    s.erase(0,s.find_first_not_of(" "));  
    s.erase(s.find_last_not_of(" ") + 1);  
    return s;  
}  

Table::Table(const char* in,char field_sep, char row_sep)
{        
    int  cur_pos = 0;
    int  last_pos = 0;
    const char* temp = in;
    std::string filed = "";
    bool end_filed = false;

    for(cur_pos=0; (0 != temp[cur_pos]) && (true != end_filed); cur_pos++)
    {
        switch(temp[cur_pos])
        {
            case FIELD_SEPARTOR:    //字段分隔符
                m_field.push_back(filed);
                filed="";
                break;
            case ROW_SEPARTOR:      //行分隔符
                m_field.push_back(filed);
                filed="";
                end_filed = true;
                break;
            default:
                filed += temp[cur_pos];
                break;
        }
    }
    
    std::string value = "";
    Row *row = NULL;
    int filed_index = 0;
    for(cur_pos; 0 != temp[cur_pos]; cur_pos++)
    {
        switch(temp[cur_pos])
        {
            case FIELD_SEPARTOR:    //字段分隔符
                if(NULL == row){
                    row = new Row;  //内存耗尽的问题不考虑
                }
                
                if(filed_index < m_field.size()){
                    row->setValue(m_field[filed_index],value);
                }
                value="";
                filed_index++;
                break;
            case ROW_SEPARTOR:      //行分隔符
                if(NULL == row){
                    row = new Row;  //内存耗尽的问题不考虑
                }

                if(filed_index < m_field.size()){
                    row->setValue(m_field[filed_index],value);
                }
                
                addRow(row);
                row = NULL;                
                value = "";
                filed_index = 0;
                break;
            default:
                value += temp[cur_pos];
                break;
        }
    }
    return;
}

Table::~Table()
{
    while(true != m_row.empty())
    {
        Row* row = m_row.back();
        m_row.pop_back();
        delete row;
    }
}

/* 删除指定行的信息，索引从0开始 */
void Table::deleteRow(int index)
{
    if((index >= 0) && (index < m_row.size()) && (true != empty()))
    {
        Row* row = m_row[index];
        m_row.erase(m_row.begin()+index);
        delete row;
    }
}  

/* 删除索引从begin开始到end结束的信息，end这一行不删除，索引从0开始 */
void Table::deleteRow(int begin, int end)
{
    if((0 <= begin) && (begin < end) && (end < m_row.size()) && (true != empty()))
    {
        for(int index=begin; index<end; index++)
        {
            Row* row = m_row[index];
            m_row[index] = NULL;
            delete row;
        }
        m_row.erase(m_row.begin()+begin,m_row.begin()+end);
    }      
}

Row* Table::getRow(int index)
{
    if((index >= 0) && (index < m_row.size()) && (true != empty()))
    {        
        return m_row[index];
    }
    return NULL;
}
    
Row* Table::pop_back()
{
    if(true == empty()){
        return NULL;
    }
    
    Row* row = m_row.back();
    m_row.pop_back();
    return row; 
}
Row* Table::pop_front()
{
    if(true == empty()){
        return NULL;
    }
    
    Row* row = m_row[0];
    deleteRow(0);
    return row; 
}

Row* Table::find(const std::string &key, const std::string &value)
{
    if(true == empty()){
        return NULL;
    }
    
    Row* row = NULL;
    for (std::vector<Row*>::iterator it = m_row.begin() ; it != m_row.end(); ++it)
    {
        row = *it;
        if(value == row->getValue(key))
        {
            break;
        }
        row = NULL;
    }
    return row; 
}

