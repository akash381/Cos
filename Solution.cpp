/* c++ code*/
#include<stdio.h>
#include<iostream>
#include<ctime>//for date and time
#include<string>//for string manipulations
#include <sstream>//for converting string to int
using namespace std;

int nodeNum = 0;
struct node
{
    char* timestamp;
    string data;
    int nodeNumber;
    string nodeId;
    string referenceNodeId;
    string * childReferenceNodeId;
    string genesisReferenceNodeId;
    string HashValue;
};

// To convert time to universal format
char* universalTime()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    tm *gmtm = gmtime(&now);
    dt = asctime(gmtm);
    return dt;
}

//for Data encryption
string encryptedData(string oID,float v,string oName,string eKey)
{
    string eData = "";

    //Encrypted data will be "v+eKey+oID+oName+hash"
    ostringstream str1;
    str1 << v;
    string s = str1.str();
    eData.append(s);
    eData.append(eKey);
    eData.append(oID);
    eData.append(oName);
    str1 << v/nodeNum;
    s = str1.str();
    eData.append(s);//own defined hash function
    return eData;

}

//to get Node Id
string getNodeId()
{
    string s = "";

    ostringstream str1;
    str1 << nodeNum;
    string ssss = str1.str();
    s.append(ssss);
    //considering int to be 4 bytes
    s.append(ssss);
    return s;
}

//get genesis reference ID
string getGenesisReference(node* gNode)
{

    ostringstream str1;
    str1 << &gNode;
    string s = str1.str();
    return s;
}

//get hash value
string getHashValue(node* temp)
{
    ostringstream str1;
    str1 << &temp;
    string s = str1.str();
    return s;
}

//assigning null to children
string * assignNullChildren()
{
    string *s = new string[2];
    return s;
}
//get a new node
node * getNewNode(node* gNode,string oID,float v,string oName,string eKey)
{
    node* temp = new node();

    temp->timestamp = universalTime();

    temp->data = encryptedData(oID,v,oName,eKey);

    temp->nodeNumber = nodeNum++;

    temp->nodeId = getNodeId();

    temp->referenceNodeId = "";//null parent

    temp->childReferenceNodeId = assignNullChildren();//null children

    temp->genesisReferenceNodeId = getGenesisReference(gNode);

    temp->HashValue = getHashValue(temp);

    return temp;
}
string decrypt(string s)
{
    string data = "";
    int i = 0 ;
    while(s[i]!='.')
    {
        i++;
        //data.append(s[i++]);
    }
    data.append(s,0,i-1);
    data.append(s,i+1,2);
    return data;
}

//to find value of a node
float valueOfNode(node * temp)
{
    if(temp==NULL)
        return 0;
    string s = temp->data;
    s = decrypt(s);
    stringstream geek(s);
    float x;
    geek >> x;
    return x;
}

//to get left node address
node * getLeftAdd(node* gNode)
{
    string* s = gNode->childReferenceNodeId;
    stringstream geek(s[0]);
    node* x;
    geek >> x;
    return x;

}

//to get left node address
node * getRightAdd(node* gNode)
{
    string* s = gNode->childReferenceNodeId;
    stringstream geek(s[1]);
    node* x;
    geek >> x;
    return x;

}

//to get left child
node* getLeftChild(node* gNode)
{
    if(gNode==NULL)
    {
        return gNode;
    }
    node* temp = gNode;
    return getLeftAdd(gNode);
}

//to get right child
node* getRightChild(node* gNode)
{
    if(gNode==NULL)
    {
        return gNode;
    }
    node* temp = gNode;
    return getRightAdd(gNode);
}

//to get children of a given node
node** getChildren(node* gNode)
{
    node** t ;
    node* t[0] = getLeftChild();
    node* t[1] = getRightChild();
    return node;
}

//getting child reference
string * getChildReference(string s1,string s2)
{
    string* s = {s1,s2};
    return s;
}

//to insert a node
node * insert(node* gNode,string oID,float v,string oName,string eKey)
{
    if(gNode == NULL)
    {
        return getNewNode(gNode,oID,v,oName,eKey);
    }
    node* temp = gNode;
    float value = valueOfNode(temp);
    float lValue = valueOfNode(getLeftChild(temp));
    float rValue = valueOfNode(getRightChild(temp));

    if(value>(lValue+rValue))
    {
        node* temp1 = getLeftChild(temp);
        temp1 = insert(temp1,oID,v,oName,eKey);
        //referencing the parent
        ostringstream str1;
        str1 << &temp;
        string s = str1.str();
        temp1->referenceNodeId = s;
        //changing the left child reference
        ostringstream str1;
        str1 << &temp1;
        string s = str1.str();
        temp->childReferenceNodeId = getChildReference(s,"");
    }

    return gNode;
}
float roundOff(float var)
{
    float value = (int)(var * 100 + .5);
    return (float)value / 100;
}

//verifying owner
bool verifyOwner(node* gNode,string key)
{
    string s = gNode->data;
    if(strcmp(key,keyOf(s))
    {
        cout<<"verified user\n";
        return true;
    }
    //else
    {
        cout<<"Not verified user\n";
        return false;
    }
}
int main()
{
    node* GenesisNode = NULL;

    char input = 'Y';
    while(input=='Y')
        {
        string ownerId;
        cout<<"Enter your Id : ";
        getline(cin,ownerId);
        fflush(stdin);
        int value;
        cout<<"Enter the value : ";
        cin>>value;
        fflush(stdin);
        value = roundOff(value);
        string ownerName;
        cout<<"Enter your name : ";
        getline(cin,ownerName);
        fflush(stdin);
        string encryptionKey;
        cout<<"Enter your encryption Key : ";
        getline(cin,encryptionKey);
        fflush(stdin);

        GenesisNode = insert(GenesisNode,ownerId,value,ownerName,encryptionKey);
        cout<<"Enter another entry (Y:for yes\t N:for no) : ";
        cin>>input;
    }

    cout<<"Children of a node : ";
    getChildren(GenesisNode);
    string s;
    getline(cin,s);
    cout<<"Enter key to verify : ";
    verifyOwner(GenesisNode,s);

}
