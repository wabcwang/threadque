/*
*   Copyright (C) 2016, Íõ³¬ [wabcwang] , <wabcwang@gmail.com>.
*   All Rights Reserved.
*/
#include <iostream>
#include "table.h"

int main ()
{
    Table table;

    for(int i=0;i <10;i++)
    {
        Row *row = new Row;
        row->setValue("a",i);
        row->setValue("b",i);
        row->setValue("c",i);
        row->setValue("d",i);
        row->setValue("e",5.1);        
        table.addRow(row);
    }

    Row *row=table.getRow(0);
    if(NULL != row)
    {
        std::cout<<"a:"<<row->getValue("a")<<" ";
        std::cout<<"b:"<<row->getValue("b")<<" ";
        std::cout<<"c:"<<row->getValue("c")<<" ";
        std::cout<<"d:"<<row->getValue("d")<<" ";
        std::cout<<"e:"<<row->getValue("e")<<" ";
        std::cout<<std::endl;
    }
    int i =row->getInt("e");
    std::cout<<"int-e:"<<i<<std::endl;
    
    float f =row->getFloat("e");
    std::cout<<"float-e:"<<f<<std::endl;

    double d =row->getDouble("e");
    std::cout<<"double-e:"<<d<<std::endl;
    
    long l =row->getLong("e");
    std::cout<<"long-e:"<<l<<std::endl;

    table.deleteRow(2);
    for(int i=0;i <table.size();i++)
    {
        row=table.getRow(i);
        if(NULL != row)
        {
            std::cout<<"a:"<<row->getValue("a")<<" ";
            std::cout<<"b:"<<row->getValue("b")<<" ";
            std::cout<<"c:"<<row->getValue("c")<<" ";
            std::cout<<"d:"<<row->getValue("d")<<" ";
            std::cout<<"e:"<<row->getValue("e")<<" ";
            std::cout<<std::endl;
        }
    }
    
    row=table.pop_back();
    std::cout<<"a:"<<row->getValue("a")<<" size:"<<table.size()<<std::endl;
    delete row;

    row=table.getRow(0);  
    std::cout<<"a:"<<row->getValue("a")<<std::endl;

    table.deleteRow(4,6);
    for(int i=0;i <table.size();i++)
    {
        row=table.getRow(i);
        if(NULL != row)
        {
            std::cout<<"a:"<<row->getValue("a")<<" ";
            std::cout<<"b:"<<row->getValue("b")<<" ";
            std::cout<<"c:"<<row->getValue("c")<<" ";
            std::cout<<"d:"<<row->getValue("d")<<" ";
            std::cout<<"e:"<<row->getValue("e")<<" ";
            std::cout<<std::endl;
        }
    }

    char *s = (char*)"a b c d e f g\n"\
              "1 ? 1 1 1 1 1\n"\
              "2 2 2 2 2 2\n"\
              "33 33 33 33 33 33 33 ?\n";
    
    Table table_test(s);
    for(int i=0;i <table_test.size();i++)
    {
        row=table_test.getRow(i);
        if(NULL != row)
        {
            std::cout<<"a:"<<row->getValue("a")<<" ";
            std::cout<<"b:"<<row->getValue("b")<<" ";
            std::cout<<"c:"<<row->getValue("c")<<" ";
            std::cout<<"d:"<<row->getValue("d")<<" ";
            std::cout<<"e:"<<row->getValue("e")<<" ";            
            std::cout<<"f:"<<row->getValue("f")<<" ";
            std::cout<<"g:"<<row->getValue("g")<<" ";
            std::cout<<std::endl;
        }
    }

    /*Table test = table_test;
    for(int i=0;i <test.size();i++)
    {
        row=test.getRow(i);
        //if(NULL != row)
        {
            std::cout<<"a:"<<row->getValue("a")<<" ";
            std::cout<<"b:"<<row->getValue("b")<<" ";
            std::cout<<"c:"<<row->getValue("c")<<" ";
            std::cout<<"d:"<<row->getValue("d")<<" ";
            std::cout<<"e:"<<row->getValue("e")<<" ";            
            std::cout<<"f:"<<row->getValue("f")<<" ";
            std::cout<<"g:"<<row->getValue("g")<<" ";
            std::cout<<std::endl;
        }
    } */   
    return 0;
}

