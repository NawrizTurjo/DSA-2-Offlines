#include <bits/stdc++.h>
#include "Red-Black-header.hpp"
using namespace std;

int main()
{
    freopen("input.txt","r",stdin);
    freopen("out.txt","w",stdout);
    RedBlackTree tree;
    string s;
    int n=1;
    while(cin>>s)
    {
        cout<<"Cmd "<<n<<": "<<s;
        n++;
        if(s=="Em")
        {
            cout<<endl;
            tree.isEmpty()?cout<<"yes\n":cout<<"no\n";
        }

        else if(s=="Clr")
        {
            cout<<endl;
            tree.clear();
        }

        else if (s=="I")
        {
            int key;
            string value;
            cin>>key>>value;
            cout<<" "<<key<<" "<<value<<endl;
            tree.insert(key,value);
            tree.printTree();
        }

        else if(s=="F")
        {
            stringstream ss;
            string str;
            getline(cin,str);
            ss<<str;
            int key;
            string value;
            ss>>key>>value;
            cout<<" "<<key;
            if(value!="")
                cout<<" "<<value;
            cout<<endl;
            tree.search(key);
        }

        else if(s=="S")
        {
            cout<<endl;
            cout<<tree.getSize()<<endl;
        }

        else if(s=="E")
        {
            int key;
            cin>>key;
            cout<<" "<<key<<endl;
            tree.deleteNode(key);
        }
        
        else if(s=="Itr")
        {
            cout<<endl;
            tree.inorder();
        }
        else break;
        if(s!="")
            cout<<endl;
    }
}