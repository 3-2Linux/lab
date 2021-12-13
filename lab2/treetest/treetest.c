#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

struct StudentData {

	char student_name[10];
	int midterm_score;
	int endterm_score;

};

struct StudentData *root = NULL;

int compare(const void *cp1, const void*cp2) {
	return strcmp(((struct StudentData *)cp1)->student_name,((struct StudentData*)cp2)->student_name);
}

void print_node(const void *nodeptr, VISIT order, int level)
{
	if (order == preorder || order == leaf)
		printf("이름 = %-20s, 중간점수  = %d 기말점수 = %d \n",(*(struct StudentData **)nodeptr)->student_name,(*(struct StudentData **)nodeptr)->midterm_score,(*(struct StudentData **)nodeptr)->endterm_score);
}


int main() {
	int i,student_number;
	struct StudentData **ret;
    
	printf("학생 수를 입력해주세요 : ");
	scanf("%d",&student_number);

	if(student_number <=0) 
		abort();
    
	struct StudentData *tree[student_number];

	for(i = 0; i<sizeof(tree) / sizeof(struct StudentData *); i++) {
	
		tree[i] = malloc(sizeof(struct StudentData));
		printf("트리에 추가할 사용자 명을 입력해주세요(이름, 중간점수, 기말점수) \n");
		scanf("%s %d %d",tree[i]->student_name,&tree[i]->midterm_score,&tree[i]->endterm_score); 

		ret = (struct StudentData **) tsearch((void *) tree[i],(void **) &root, compare);
		printf("\"%s\" 님이 ", (*ret)->student_name);
		
		if (*ret == tree[i])
			printf("트리에 추가되었습니다.\n");
		else
			printf("트리에 이미 존재합니다.\n");
			
	}
	
	twalk((void *) root, print_node);

	 for (int i = 0; i < sizeof(tree) / sizeof(struct StudentData *); i++)    
        free(tree[i]);    
	
}
