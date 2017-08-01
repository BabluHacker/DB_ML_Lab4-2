#include<bits/stdc++.h>
using namespace std;
#define MAX 50

int numberOfPointers;

struct Block{

    int tNodes;

    Block *parentBlock;

    string value[MAX];

    Block *childBlock[MAX];
    Block(){
        tNodes = 0;
        parentBlock = NULL;
        for(int i=0; i<MAX; i++){
            value[i] = "zzzzzzzzzzzzzzzzzzz";
            childBlock[i] = NULL;
        }
    }
};

Block *rootBlock = new Block();

void splitLeaf(Block *curBlock){
    int x, i, j;


    if(numberOfPointers%2)
        x = (numberOfPointers+1)/2;
    else x = numberOfPointers/2;


    Block *rightBlock = new Block();


    curBlock->tNodes = x;

    rightBlock->tNodes = numberOfPointers-x;

    rightBlock->parentBlock = curBlock->parentBlock;

    for(i=x, j=0; i<numberOfPointers; i++, j++){

        rightBlock->value[j] = curBlock->value[i];

        curBlock->value[i] = "zzzzzzzzzzzzzzzzzzz";
    }

    string val = rightBlock->value[0];


    if(curBlock->parentBlock==NULL){

        Block *parentBlock = new Block();

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


void splitNonLeaf(Block *curBlock){
    int x, i, j;

    x = numberOfPointers/2;


    Block *rightBlock = new Block();


    curBlock->tNodes = x;

    rightBlock->tNodes = numberOfPointers-x-1;

    rightBlock->parentBlock = curBlock->parentBlock;


    for(i=x, j=0; i<=numberOfPointers; i++, j++){

        rightBlock->value[j] = curBlock->value[i];

        rightBlock->childBlock[j] = curBlock->childBlock[i];

        curBlock->value[i] = "zzzzzzzzzzzzzzzzzzz";
        if(i!=x)curBlock->childBlock[i] = NULL;
    }
    string val = rightBlock->value[0];

    memcpy(&rightBlock->value, &rightBlock->value[1], sizeof(string)*(rightBlock->tNodes+1));
    memcpy(&rightBlock->childBlock, &rightBlock->childBlock[1], sizeof(rootBlock)*(rightBlock->tNodes+1));


    for(i=0;curBlock->childBlock[i]!=NULL;i++){
        curBlock->childBlock[i]->parentBlock = curBlock;
    }
    for(i=0;rightBlock->childBlock[i]!=NULL;i++){
        rightBlock->childBlock[i]->parentBlock = rightBlock;
    }


    if(curBlock->parentBlock==NULL){

        Block *parentBlock = new Block();

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

void insertNode(Block *curBlock, string val){

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

bool dataFound;

void print(vector < Block* > Blocks){
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
        if(curBlock->value[j]=="zzzzzzzzzzzzzzzzzzz" && curBlock->childBlock[j]!=NULL)
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

int main(){
    string num[50];// = {1,4,7,10,17,21,31,25,19,20,28,42};

    numberOfPointers = 4;

    FILE *p;


    vector < Block* > Blocks;


    int ch;
    int i = 0;
    int totalValues = 0;

    printf("1.Insert a value\n2.Print the tree\n");

    while(scanf("%d", &ch)!=EOF){


        if(ch==1){
            //scanf("%d", &num[i]);
            cin >> num[i];
            cout << "****** "<<num[i] << " * inserted *****\n"<<endl;

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
