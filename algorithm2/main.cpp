#include <stdio.h>
#include <stdlib.h>

#define false 0
#define true 1

typedef int Boolean;

struct TreeNode{
	
	struct TreeNode* leftNode;
	struct TreeNode* rightNode;

	Boolean isKey;
};

TreeNode* tHeader;

void insertNode(int b[100],int l){

	int i;

	TreeNode* tVisit;
	TreeNode* tNode;

	tVisit = tHeader;

	for(i=0;i<l;i++){
		if(b[i]==0){ //leftNode
			if(tVisit->leftNode==NULL){
				tNode = (TreeNode *)malloc(sizeof(TreeNode));
				tVisit->leftNode = tNode;
				if(i==l-1){
					tNode->isKey = true;
				}
				else{
					tNode->isKey = false;
					tVisit = tNode;
				}
				tNode->leftNode = NULL;
				tNode->rightNode = NULL;
			}
			else{
				if(i==l-1){
					tVisit->leftNode->isKey = true;
				}
				else{
					tVisit = tVisit->leftNode;
				}
			}
		}
		else { //rightNode
			if(tVisit->rightNode==NULL){
				tNode = (TreeNode *)malloc(sizeof(TreeNode));
				tVisit->rightNode = tNode;
				if(i==l-1){
					tNode->isKey = true;
				}
				else{
					tNode->isKey = false;
					tVisit = tNode;
				}
				tNode->leftNode = NULL;
				tNode->rightNode = NULL;
			}
			else{
				if(i==l-1){
					tVisit->rightNode->isKey = true;
				}
				else{
					tVisit = tVisit->rightNode;
				}
			}
		}
	}


}

Boolean removeNode(TreeNode* tVisit, int b[100],int l,int index){
	

	TreeNode* tNode;

	if(b[index]==0){ //leftNode
		if(tVisit->leftNode==NULL){
		}
		else{
			if(index==l-1){
				if(tVisit->leftNode->leftNode==NULL 
					&& tVisit->leftNode->rightNode==NULL){
						tVisit->leftNode = NULL;
						return true;
				}
				else{
					tVisit->leftNode->isKey = false;
				}

			}
			else{
				if(removeNode(tVisit->leftNode, b, l, index+1)){
					if(!tVisit->leftNode->isKey &&
						tVisit->leftNode->leftNode == NULL &&
						tVisit->leftNode->rightNode == NULL) tVisit->leftNode = NULL;
					if(tVisit->rightNode==NULL){
						return true;
					}
				}
			}
		}
	}
	else { //rightNode
		if(tVisit->rightNode==NULL){
		}
		else{
			if(index==l-1){
				if(tVisit->rightNode->leftNode==NULL 
					&& tVisit->rightNode->rightNode==NULL){
						tVisit->rightNode = NULL;
						return true;
				}
				else{
					tVisit->rightNode->isKey = false;
				}
			}
			else{
				if(removeNode(tVisit->rightNode,b,l,index+1)){
					if(!tVisit->rightNode->isKey &&
						tVisit->rightNode->leftNode == NULL &&
						tVisit->rightNode->rightNode == NULL)  tVisit->rightNode = NULL;
					if(tVisit->leftNode==NULL){
						return true;
					}
				}
			}
		}
	}
	return false;

}

void printNode(TreeNode* node){
	if(node->isKey){
		printf("K");
	}
	else{
		printf("N");
	}
}

void printNode_1(TreeNode* node){ //전위순회 root left right

	printNode(node); //root
	if(node->leftNode!=NULL) {
		printNode_1(node->leftNode);
	}
	if(node->rightNode!=NULL){
		printNode_1(node->rightNode);
	}
}

void printNode_2(TreeNode* node){ //중위순회 left root right
	
	if(node->leftNode!=NULL) {
		printNode_2(node->leftNode);
	}
	printNode(node); //root
	if(node->rightNode!=NULL){
		printNode_2(node->rightNode);
	}
}

void printNode_3(TreeNode* node){ //후위순위 left right root
	if(node->leftNode!=NULL) {
		printNode_3(node->leftNode);
	}
	if(node->rightNode!=NULL){
		printNode_3(node->rightNode);
	}
	printNode(node); //root
}

int main(){

	int n;
	int b[100];
	char c[100];
	char type;
	int l;
	int i,j;

	
	tHeader = (TreeNode *)malloc(sizeof(TreeNode));
	tHeader->isKey = false;
	tHeader->leftNode = NULL;
	tHeader->rightNode = NULL; 

	scanf("%d",&n);

	for(i=0;i<n;i++){
		scanf("%s",&c);

		l=0;
		while(c[l]!=NULL) {
			l++;
		}
		for(j=l;j>=1;j--){
			if(c[j]==48){ //'0'은 아스키코드로 48
				b[j-1]=0;
			}
			else{
				b[j-1]=1;
			}
		}
		type=c[0];

		l--;
		if(type=='+'){
			insertNode(b,l);
		}
		else{
			removeNode(tHeader,b,l,0);
		}
		
	}
	
	printNode_1(tHeader);
	printf("\n");
	printNode_2(tHeader);
	printf("\n");
	printNode_3(tHeader);
//	printf("\n");

	return 0;

}