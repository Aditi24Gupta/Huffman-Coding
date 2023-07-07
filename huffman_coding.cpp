// INCLUDING ALL THE FILES
#include<iostream>
#include<string>
#include<queue>
#include<unordered_map>
#include "node.h"
using namespace std; 

//DECLARING HASHMAPS FOR KEEPING TRACK OF COMPRESSED CHARACTERS
unordered_map<char,string> compress;
unordered_map<string,char> decompress;

//FUNCTION FOR GETTING ORIGINAL SIZE OF FILE CONTENTS OR DECOMPRESSION
int size_decompress(string code){
    string check="";
    string word="";
    for(int i=0;i<code.length();i++){
        check+=code[i];
        if(!decompress[check]){
            continue;
        }else{
            word+=decompress[check];
            check="";
        }
    }

    return (word.length()*8);
}
 
//FUNCTION FOR ASSIGNING CODES FOR CHARACTERS IN FILE
void assignment(binarytree*head,string path){
    if(head==NULL){
        return;                          //preorder traversal of binarytree
    }

    if(head->data!='&'){
        compress[head->data]=path;
        decompress[path]=head->data;
    }

    assignment(head->left,path+'0');
    assignment(head->right,path+'1');

}

//FUNCTION FOR THE TASK OF COMPRESSION
pair<int,int> text_compression(string work){
    //CALCULATE THE COUNT OF EACH CHARACTER
    int arr[26]={0};
    string unique;
    for(int i=0;i<work.length();i++){
        int index=work[i]-'a';
        if(arr[index]==0){
            unique+=work[i];
        }
        arr[index]++;
        
    }
    
    //PUSHING ELEMENTS IN MINHEAP
    priority_queue<binarytree*,vector<binarytree*>,compare> minheap;

    for(int i=0;i<unique.length();i++){
        minheap.push(new binarytree(unique[i],arr[unique[i]-'a']));
    }
 
    //HUFFMAN TREE BUILDING
    binarytree*head,*left,*right;
    while(minheap.size()!=1){
        left=minheap.top();
        minheap.pop();

        right=minheap.top();
        minheap.pop();

        head=new binarytree('&',left->data+right->data);

        head->left=left;
        head->right=right;

        minheap.push(head);
    }

    //ASSIGNMENT OF PATH
    assignment(head,"");


    //DECOMPRESSING THE DATA FOR CALCULATING ORIGINAL SIZE OF FILE
    string encode="";
    for(int k=0;k<work.length();k++){
        encode+=compress[work[k]];
    }

    int original=size_decompress(encode);
    


    //CALCULATING THE COMPRESSED SIZE OF FILE
    int sum=0;
    for(int i=0;i<unique.length();i++){
        int size=(arr[unique[i]-'a'])*(compress[unique[i]].length());
        sum+=size;
    }

   
    //CREATING PAIR 
    pair<int,int> pair;
    pair.first=original;
    pair.second=sum;

    return pair;
    

}

int main(){
    cout<<"enter the contents of file:";
    string file;
    cin>>file;
    pair<int,int> p=text_compression(file);
    cout<<"the original size of file in bits:"<<p.first<<endl;
    cout<<"Size of file after compression:"<<p.second<<endl;
    return 0;

}