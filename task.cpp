#include <bits/stdc++.h>
#include <Windows.h>
#include <sstream>
#include <iostream>
using namespace std;

int add(int n, string s) //add
{
    if(n<0){
        cout<<"Can't be added! Enter a positive integer for priority (greater than 0)!";
    }
    else{
        int priority;
        string temp;
        vector<int> p;
        unordered_map<int, string> umap;
        ifstream read;
        read.open("text.txt");
        
        while(getline(read, temp))
        {
            int pos = temp.find(" ");
            string sub = temp.substr(0, pos);
            stringstream con(sub);
            int priority = 0;
            con >> priority;
            p.push_back(priority);
            umap[priority]=temp;
        }
       
        read.close();
        
        bool check=false; 

        for(int i=0;i<p.size();i++)
        {
            if(n==p[i])
            check=true; 
        }

        if(check==false)
        {
            p.push_back(n);
            umap[n]=to_string(n)+" "+s;

            sort(p.begin(), p.end());
            
            ofstream write;
            write.open("text.txt");
            for(int i=0;i<p.size();i++)
            {
                write<<umap.at(p[i])<<endl;
            }
            cout<<"Added task: "<<"\""<<s<<"\" with priority "<<n<<endl;
            write.close();
        }
        else
        {
            umap[n]=to_string(n)+" "+s;
            sort(p.begin(), p.end());
            ofstream write;
            write.open("text.txt");
            
            for(int i=0;i<p.size();i++)
            {
                write<<umap.at(p[i])<<endl;
            }
            cout<<"Added task: "<<"\""<<s<<"\" with priority "<<n<<endl;
            write.close();
        }   
    }
    return 0;
}

int del(int k) // delete
{
    int priority;
    string temp;
    vector<int> p;
    unordered_map<int, string> umap;
    vector<int>::iterator it;
    ifstream read;
    read.open("text.txt");

    while(getline(read, temp))
    {
        int pos = temp.find(" ");
        string sub = temp.substr(0, pos);
        stringstream con(sub);
        int priority = 0;
        con >> priority;
        p.push_back(priority);
        umap[priority]=temp;
    }
    sort(p.begin(), p.end());
    read.close();
    if(k>p.size() ||k<1)
    {
        cout<<"Error: task with index #"<<k<<" does not exist. Nothing deleted."<<endl;
    }
    else
    {
        ofstream write;
        write.open("text.txt");
        for(int i=0;i<p.size();i++)
        {
            if(i!=k-1)
            {
                write<<umap.at(p[i])<<endl;
            }
        }
        cout<<"Deleted task #"<<k<<endl;
    }  
    return 0;
}

int done(int k) // done
{
    int priority;
    string temp, x;
    vector<int>::iterator it;
    vector<int> p, p1;
    unordered_map<int, string> umap, umap1;
    ifstream read;
    read.open("text.txt");

    while(getline(read, temp))
    {
        int pos = temp.find(" ");
        string sub = temp.substr(0, pos);
        stringstream con(sub);
        int priority = 0;
        con >> priority;
        p.push_back(priority);
        umap[priority]=temp;
    }
    sort(p.begin(), p.end());
    read.close();
    if(k>p.size()||k<1)
    {
        cout<<"Error: no incomplete item with index "<<k<<" exists.";
    } 
    else
    {
        ofstream write1,write2;
        write1.open("text.txt");
        write2.open("completed.txt",ios::app);
        for(int i=0;i<p.size();i++)
        {
            if(i==k-1)
            {
                x=umap.at(p[i]);
                cout<<"Marked item as done."<<endl;
            }
            else
            {
                write1<<umap.at(p[i])<<endl;
            }
        }
        write1.close();
        write2<<x<<endl;
        write2.close();

        ifstream read;
        read.open("completed.txt");
        while(getline(read, temp))
        {
            int pos = temp.find(" ");
            string sub = temp.substr(0, pos);
            stringstream con(sub);
            int priority = 0;
            con >> priority;
            p1.push_back(priority);
            umap1[priority]=temp;
        }
        sort(p1.begin(), p1.end());
        read.close();
        write2.open("completed.txt");
        for(int i=0;i<p1.size();i++)
        {
            write2<<umap1.at(p1[i])<<endl;
            
        }
        write2.close();
    }
    
    return 0;
}

int ls() // list
{
    int priority;
    string temp, x;
    vector<int> p;
    unordered_map<int, string> umap;
    ifstream read;
    read.open("text.txt");

    while(getline(read, temp))
    {
        int pos = temp.find(" ");
        string sub = temp.substr(0, pos);
        stringstream con(sub);
        int priority = 0;
        con >> priority;
        p.push_back(priority);
        umap[priority]=temp;
    }
    sort(p.begin(), p.end());
    read.close();
    if(p.size()==0)
    {
        cout<<"There are no pending tasks!"<<endl;
    }
    else
    {
        for(int i=0;i<p.size();i++)
        {
            cout<<i+1<<". ";
            temp=umap.at(p[i]);
            int pos = temp.find(" ");
            for(int j=pos+1; temp[j]!='\0'; j++){
            cout<<temp[j];
            }
            cout<<" ["<<p[i]<<"]"<<endl;
        }
    }

    return 0;
}

int help() //help
{
    cout<<"Usage :-"<<endl;
    cout<<"$ ./task add 2 hello world    # Add a new item with priority 2 and text \"hello world\" to the list"<<endl;
    cout<<"$ ./task ls                   # Show incomplete priority list items sorted by priority in ascending order"<<endl;
    cout<<"$ ./task del INDEX            # Delete the incomplete item with the given index"<<endl;
    cout<<"$ ./task done INDEX           # Mark the incomplete item with the given index as complete"<<endl;
    cout<<"$ ./task help                 # Show usage"<<endl;
    cout<<"$ ./task report               # Statistics";
    return 0;
}

int report() //report
{
    int pending =0,done=0;
    string temp;
    vector<int> p, p1;
    unordered_map<int, string> umap, umap1;
    ifstream read;
    read.open("text.txt");  // text.txt contains the pending tasks;
    if(!read.eof())
    {
        while(getline(read,temp))
        {
            pending++;
            int pos = temp.find(" ");
            string sub = temp.substr(0, pos);
            stringstream con(sub);
            int priority = 0;
            con >> priority;
            p.push_back(priority);
            umap[priority]=temp;
        }
    }
    read.close();
    cout<<"Pending : "<<pending<<endl;
    for(int i=0;i<p.size();i++)
    {
        cout<<i+1<<". ";
        temp=umap.at(p[i]);
        int pos = temp.find(" ");
        for(int j=pos+1; temp[j]!='\0'; j++){
        cout<<temp[j];
        }
        cout<<" ["<<p[i]<<"]"<<endl;
    }
    cout<<endl;
    read.open("completed.txt"); // completed.txt contains the completed tasks
    if(!read.eof())
    {
        while(getline(read,temp))
        {
            done++;
            int pos = temp.find(" ");
            string sub = temp.substr(0, pos);
            stringstream con(sub);
            int priority = 0;
            con >> priority;
            p1.push_back(priority);
            umap1[priority]=temp;
        }
    }
    read.close();
    cout<<"Completed : "<<done<<endl;
    for(int i=0;i<p1.size();i++)
    {
        cout<<i+1<<". ";
        temp=umap1.at(p1[i]);
        int pos = temp.find(" ");
        for(int j=pos+1; temp[j]!='\0'; j++){
        cout<<temp[j];
        }
        cout<<endl;
    }
  

    return 0;
    
}

int main(int argc, char* argv[])
{
    SetConsoleOutputCP(65001);
    setvbuf(stdout, nullptr, _IOFBF, 1000);
    string s, s2, s3;
    int k=0;

    if(argc>1)
    s=argv[1];

    if(argc==1 || s=="help")
    {
        help(); // call help
    }
    else if(s=="add")
    {

        if(argc==2)
        {
            cout<<"Error: Missing tasks string. Nothing added!"<<endl;
        }
        else
        {
            s2=argv[2];
            s3=argv[3];
            k=stoi(s2);
            add(k, s3);
        }
        
    }
    else if(s=="del")
    {

        if(argc==2)
        {
            cout<<"Error: Missing NUMBER for deleting tasks."<<endl;
        }
        else
        {
            s2=argv[2];
            k=stoi(s2); //string to integer
            del(k);
        }
        
    }
    else if(s=="report")
    {
        report(); // call report
    }
    else if(s=="done")
    {

        if(argc==2)
        {
            cout<<"Error: Missing NUMBER for marking tasks as done."<<endl;
        }
        else
        {
            s2=argv[2];
            k=stoi(s2); 

        
            if(k>0)
            done(k);
            else
            {
                cout<<"Error: no incomplete item with index #0 exists."<<endl;
            }
            
        }
        
    }
    else if(s=="ls")
    {
        ls(); // call list
    }

    return 0;
}
