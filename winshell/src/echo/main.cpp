#include <iostream>
#include <sstream>
#include <ctype.h>

using namespace std;

char newLine = '\n';

void noNewLine()
{
    newLine = 0;
}

void help()
{
    string command = "echo ";
    cout<<command<<"[option].. [msg].."<<endl;
    
    cout<<endl;
    
    cout<<"options:"<<endl;
    cout<<'\t'<<"-n --nonewline\tdo not print newline character at end"<<endl;
    cout<<'\t'<<"-h --help\tprint help message"<<endl;
    
    cout<<endl;
     
    cout<<"examles:"<<endl;
    cout<<'\t'<<command<<"msg"<<endl;
    cout<<'\t'<<command<<"msg1 msg2"<<endl;
    cout<<'\t'<<command<<"-n msg"<<endl;
    cout<<'\t'<<command<<"msg -n"<<endl;
    cout<<'\t'<<command<<"--nonewline msg"<<endl;
    cout<<'\t'<<command<<"-h"<<endl;
    cout<<'\t'<<command<<"--help"<<endl;
}
void error(const stringstream &errMsg)
{
    cout<<"error\t"<<errMsg.str()<<endl;
    help();
    exit(-1);
}

void parseOptions(const string &option)
{
    stringstream errMsg;
    errMsg << "parsing "<<option<< " error!"<<endl;
    
    if(option[1] == '-')
    {
        if(option == "--nonewline")
        {
            noNewLine();
        }else if(option == "--help")
        {
            help();
        }else
        {
            error(errMsg);
        }
    }else{
        int i;
        for(i=1; i<option.size(); i++)
        {
            switch(option[i])
            {
                case 'n':
                    noNewLine();
                    break;
                case 'h':
                    help();
                    break;    
                default:
                    error(errMsg);
            }
        }
        if(i == 1)
        {
            error(errMsg);
        }
    }
}
int main(int argc, char *argv[])
{
    if(argc<2)
    {
        help();
    }
    for(int i=1; i<argc; i++)
    {
        if(argv[i][0] == '-')
        {
            parseOptions(argv[i]);
        }else{
            cout<<argv[i]<<" ";
        }
    }
    cout<<newLine;
    
    return 0; 
}
