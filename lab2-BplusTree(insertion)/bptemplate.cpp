#include<bits/stdc++.h>
using namespace std;
#define MAX 50
//string  MAX_VALUE= "zzzzzzzzzzz";



template <class T>
class bp{


    int numberOfPointers;

    bool dataFound;
    public:
        T maximum;

    struct Block{

        int tNodes;

        Block *parentBlock;

        T value[MAX];

        Block *childBlock[MAX];
        Block(){

        }
    };
    Block *rootBlock = new Block();


    public:
        bp(T maxx){
            maximum = maxx;
        }
        void get(){
            cout<< maximum<<endl;
        }

        void splitLeaf(Block *curBlock);
        void splitNonLeaf(Block *curBlock);
        void insertNode(Block *curBlock, T val);
        void print(vector < Block* > Blocks);
        void setStruct(Block *block);
        void start( );

//////////////

};

template <class T>
void bp<T>::setStruct(Block *block){
    block->tNodes = 0;
    block->parentBlock = NULL;
    for(int i=0; i<MAX; i++){
        block->value[i] = maximum;
        block->childBlock[i] = NULL;
        cout<< block->value[i] <<endl;
    }
}

template <class T>
void bp<T>::splitLeaf(Block *curBlock){
    int x, i, j;


    if(numberOfPointers%2)
        x = (numberOfPointers+1)/2;
    else x = numberOfPointers/2;


    Block *rightBlock = new Block();
    setStruct(rightBlock);

    curBlock->tNodes = x;

    rightBlock->tNodes = numberOfPointers-x;

    rightBlock->parentBlock = curBlock->parentBlock;

    for(i=x, j=0; i<numberOfPointers; i++, j++){

        rightBlock->value[j] = curBlock->value[i];

        curBlock->value[i] = maximum;
    }

    T val = rightBlock->value[0];


    if(curBlock->parentBlock==NULL){

        Block *parentBlock = new Block();
        setStruct(parentBlock);

        parentBlock->parentBlock = NULL;

        parentBlock->tNodes=1;

        parentBlock->value[0] = val;

        parentBlock->childBlock[0] = curBlock;
        parentBlock->childBlock[1] = rightBlock;

        curBlock->parentBlock = rightBlock->parentBlock = parentBlock;

        rootBlock = parentBlock;
        return;
    }
    else{

        curBlock = curBlock->parentBlock;

        Block *newChildBlock = new Block();
        setStruct(newChildBlock);

        newChildBlock = rightBlock;

        for(i=0; i<=curBlock->tNodes; i++){
            if(val < curBlock->value[i]){
                swap(curBlock->value[i], val);
            }
        }


        curBlock->tNodes++;
        for(i=0; i<curBlock->tNodes; i++){
            if(newChildBlock->value[0] < curBlock->childBlock[i]->value[0]){
                swap(curBlock->childBlock[i], newChildBlock);
            }
        }
        curBlock->childBlock[i] = newChildBlock;

        for(i=0;curBlock->childBlock[i]!=NULL;i++){
            curBlock->childBlock[i]->parentBlock = curBlock;
        }
    }

}
template <class T>
void bp<T>::splitNonLeaf(Block *curBlock){
    int x, i, j;

    x = numberOfPointers/2;


    Block *rightBlock = new Block();
    setStruct(rightBlock);

    curBlock->tNodes = x;

    rightBlock->tNodes = numberOfPointers-x-1;

    rightBlock->parentBlock = curBlock->parentBlock;

    for(i=x, j=0; i<=numberOfPointers; i++, j++){

        rightBlock->value[j] = curBlock->value[i];

        rightBlock->childBlock[j] = curBlock->childBlock[i];

        curBlock->value[i] = maximum;
        if(i!=x)curBlock->childBlock[i] = NULL;
    }
    T val = rightBlock->value[0];

    memcpy(&rightBlock->value, &rightBlock->value[1], sizeof(T)*(rightBlock->tNodes+1));
    memcpy(&rightBlock->childBlock, &rightBlock->childBlock[1], sizeof(rootBlock)*(rightBlock->tNodes+1));


    for(i=0;curBlock->childBlock[i]!=NULL;i++){
        curBlock->childBlock[i]->parentBlock = curBlock;
    }
    for(i=0;rightBlock->childBlock[i]!=NULL;i++){
        rightBlock->childBlock[i]->parentBlock = rightBlock;
    }


    if(curBlock->parentBlock==NULL){

        Block *parentBlock = new Block();
        setStruct(parentBlock);

        parentBlock->parentBlock = NULL;

        parentBlock->tNodes=1;

        parentBlock->value[0] = val;

        parentBlock->childBlock[0] = curBlock;
        parentBlock->childBlock[1] = rightBlock;


        curBlock->parentBlock = rightBlock->parentBlock = parentBlock;


        rootBlock = parentBlock;
        return;
    }
    else{

        curBlock = curBlock->parentBlock;

        Block *newChildBlock = new Block();
        setStruct(newChildBlock);

        newChildBlock = rightBlock;

        for(i=0; i<=curBlock->tNodes; i++){
            if(val < curBlock->value[i]){
                swap(curBlock->value[i], val);
            }
        }


        curBlock->tNodes++;

        for(i=0; i<curBlock->tNodes; i++){
            if(newChildBlock->value[0] < curBlock->childBlock[i]->value[0]){
                swap(curBlock->childBlock[i], newChildBlock);
            }
        }
        curBlock->childBlock[i] = newChildBlock;
         for(i=0;curBlock->childBlock[i]!=NULL;i++){
            curBlock->childBlock[i]->parentBlock = curBlock;
        }
    }
}

template <class T>
void bp<T>::insertNode(Block *curBlock, T val){

    for(int i=0; i<=curBlock->tNodes; i++){
        if(val < curBlock->value[i] && curBlock->childBlock[i]!=NULL){
            insertNode(curBlock->childBlock[i], val);
            if(curBlock->tNodes==numberOfPointers)
                splitNonLeaf(curBlock);
            return;
        }
        else if(val < curBlock->value[i] && curBlock->childBlock[i]==NULL){
            swap(curBlock->value[i], val);
            //swap(curBlock->childBlock[i], newChildBlock);
            if(i==curBlock->tNodes){
                    curBlock->tNodes++;
                    break;
            }
        }
    }

    if(curBlock->tNodes==numberOfPointers){

            splitLeaf(curBlock);

    }
}

template <class T>
void bp<T>::print(vector < Block* > Blocks){
    vector < Block* > newBlocks;

    for(int i=0; i<Blocks.size(); i++){
        Block *curBlock = Blocks[i];

        cout <<"[|";
        int j;
        for(j=0; j<curBlock->tNodes; j++){
            cout << curBlock->value[j] << "|";
            if(curBlock->childBlock[j]!=NULL)
            newBlocks.push_back(curBlock->childBlock[j]);
        }
        if(curBlock->value[j]==maximum && curBlock->childBlock[j]!=NULL)
            newBlocks.push_back(curBlock->childBlock[j]);

        cout << "]  ";
    }

    if(newBlocks.size()==0){

        puts("");
        puts("");
        Blocks.clear();
        //exit(0);
    }
    else {
        puts("");
        puts("");
        Blocks.clear();
        print(newBlocks);
    }
}

template <class T>
void bp<T>::start( ){  // 0 = int, 1 = string
    setStruct(rootBlock);
    T num[50];
    numberOfPointers = 4;
    vector < Block* > Blocks;
    int ch;
    int i = 0;
    int totalValues = 0;

    printf("1.Insert a value\n2.Print the tree\n");
    while(scanf("%d", &ch)!=EOF){


        if(ch==1){
            cin >> num[i];
            //printf("**** Insert %d ****\n\n", num[i]);
            cout << "**** Insert   **  "+num[i]<<endl;
            insertNode(rootBlock, num[i]);
            i++;
            totalValues++;

        }else if(ch==2){
            Blocks.clear();
            Blocks.push_back(rootBlock);
            print(Blocks);
            puts("");

        }
    }
}
/*
int main(){
    int num[50];// = {1,4,7,10,17,21,31,25,19,20,28,42};

    numberOfPointers = 4;


    vector < Block* > Blocks;


    int ch;
    int i = 0;
    int totalValues = 0;

    printf("1.Insert a value\n2.Print the tree\n");

    while(scanf("%d", &ch)!=EOF){


        if(ch==1){
            scanf("%d", &num[i]);
            printf("**** Insert %d ****\n\n", num[i]);
            insertNode(rootBlock, num[i]);
            i++;
            totalValues++;

        }else if(ch==2){
            Blocks.clear();
            Blocks.push_back(rootBlock);
            print(Blocks);
            puts("");

        }
    }


    return 0;
}
*/
int main(){

    cout << "1. Int\n2. String"<<endl;
    int type;
    cin >> type;

    if(type == 1){
        bp<int> b(INT_MAX);
        b.get();
        b.start();
    }
    else if(type == 2){
        bp<string> b("zzzzzzzzzzz");
        b.get();
        b.start();
    }

    return 0;
}
