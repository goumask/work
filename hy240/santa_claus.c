/**********************************************************************
 * @file   santa_claus.c                                              *
 * @author Vasileios Theodosiadis <vtheodos@ics.forth.gr>             *
 *                                                                    *
 * @brief  Main file for the needs of the Data Structures (HY-240a)   *
 * project (Fall 2015)                                                *
 * Computer Science Department, University of Crete, Greece           *
**********************************************************************/

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "santa_claus.h"

#define LEN(x) (sizeof(x) / sizeof(*(x)))

char *tokens[128];
int asint[LEN(tokens)];

struct present *stock_list = NULL; 
struct child *Age_categories[N];

struct district *district_list = NULL;

int buy_present(int pid, int stock_cnt) {
	if(pid<0 || stock_cnt<0){
		return 0;
	}

	//searching for already existing pid in stocklist
	
	struct present *temp = NULL;
	temp=stock_list;
	while(temp->pid!=-1){
		if(temp->pid==pid){ //if pid exists
			temp->stock_cnt+=stock_cnt;
			break;
		}
		temp=temp->next;
	}
	

	if(temp->pid==-1){//if pid doesnt exists inserting new node
		 insert_present(pid,stock_cnt);
	} 


	//printing output
	printf("B <%d> <%d>\n",pid,stock_cnt);
	printf("\tPresents =");
	for(temp=stock_list;temp->pid!=-1;temp=temp->next){
		printf(" <%d> ",temp->pid);
	}
	printf("\nDONE\n");
	return 1;
}

int insert_present(int pid,int stock_cnt){
	struct present *p;
	p=(struct present*) malloc(sizeof(struct present));
	p->pid=pid;
	p->stock_cnt=stock_cnt;
	if (pid==-1) //if inserting sentinel node
		p->request_cnt=-1;
	else
		p->request_cnt = 0;
	if(stock_list==NULL){	//if stock_list was empty
		p->prev=p;	//inserting sentinel node
		p->next=p;
		stock_list=p; //head now points to sentinel node

	}

	else if(stock_list->pid == -1) // only sentinel node on list
	{
		p->next = stock_list;
		p->prev = stock_list;

		stock_list->next = p;
		stock_list->prev = p;

		stock_list = p; // new node is now the new head
	}
	else //inserting new node on tail
	{
		p->prev = stock_list -> prev -> prev;
		
		stock_list->prev->prev->next = p;
		stock_list->prev->prev = p;
		p->next = stock_list -> prev;

	}

	return 0;
}

int insert_child	( struct child* c, int age_cat)
{
	struct child* temp = NULL;
	//searching for child in age_categories
	temp=Age_categories[age_cat];
	

	//inserting in an empty category
	if (temp==NULL)
	{
		Age_categories[age_cat] = c;
		c->next=NULL;
		return 0;
	}


	//inserting in head
	if (temp->cid > c->cid)
	{
		c->next = Age_categories[age_cat];
		Age_categories[age_cat] = c;
		return 0;
	}




	//inserting in the middle
	while(temp->next!=NULL)
	{
		if (temp->next->cid > c->cid)
		{
			c->next = temp->next;
			temp->next = c;
			return 0; 
		}

		temp=temp->next;
	}


	//inserting last
	temp->next = c;
	return 0;
}

int increase_req(int pid1, int pid2, int pid3)
{
	int flags[3]={0};

	//iterating the stock list
	struct present* p = NULL;
	p = stock_list;

	while (p->pid!=-1)
	{
		if (p->pid == pid1)
		{
			flags[0]=1;
			p->request_cnt++;
		}
		else if(p->pid == pid2)
		{
			flags[1]=1;
			p->request_cnt++;
		}
		else if(p->pid == pid2)
		{
			flags[2]=1;
			p->request_cnt++;
		}
		p = p->next;

	}

	if (flags[0]==0) insert_present(pid1,10);
	if (flags[1]==0) insert_present(pid2,10);
	if (flags[2]==0) insert_present(pid3,10);

	return 0;
}

void remove_child(struct child* c)
{
	if (c == NULL)
	{
		fprintf(stderr, "Cannot remove NULL child. Exiting abnormaly\n");
		exit(1);
	}
	int age_category = 0;
	struct child *tmp1, *tmp2 = NULL;


	//determine age_category
	if (c->age>=0 && c->age <=3)
		age_category = 0;
	else if (c->age>4 && c->age<=7)
		age_category = 1;
	else if (c->age >=8 && c->age <= 11)
		age_category = 2;
	else if (c->age >=12 && c->age <= 15)
		age_category = 3;
	else //error
	{
		fprintf(stderr, "Cannot remove child that can't belong in any age category\n");
		return;
	}

	tmp1 = Age_categories[age_category];


	//remove from head
	if (tmp1->cid == c->cid)
	{

		Age_categories[age_category] = c->next;
		free(c);
	}


	//removing from inside list
	for (; tmp1!= NULL; tmp1 = tmp1->next)
	{
		tmp2 = tmp1->next;
			
		if (tmp2 == NULL)
			return; //not found
		

		if (tmp2->cid == c->cid) // tmp2 is about to be removed
		{
				tmp1->next = tmp2->next;
				free (tmp2);

		}
	}

}




int letter_received(int cid, int age, int did, int pid1, int pid2, int pid3) {
	if (cid<0 || age<0 ||age>16 || did<0 || pid1<0 || pid2<0 || pid3<0) //invalid input
	{
		return 0;
	}

	//creating the new child
	struct child* c = NULL;
	c = (struct child*) malloc (sizeof(struct child));
	c->cid = cid;
	c->age = age;
	c->did = did;
	c->present_choices[0]= pid1;
	c->present_choices[1] = pid2;
	c->present_choices[2] = pid3;

	//inserting the new child at the right place

	if (age<=3)
		insert_child(c,0);
	else if (age<=7)
		insert_child(c,1);
	else if (age<=11)
		insert_child(c,2);
	else if (age<=15)		
		insert_child(c,3);

	//increasing request counter on presents

	increase_req(pid1, pid2, pid3);
	printf("L %d %d %d %d %d %d",cid,age,did,pid1,pid2,pid3);
	
	printf("\nDONE\n");
	return 1;
}

int get_presents(int pid1,int pid2,int pid3){
	struct present *array[3];
	array[0] = NULL;
	array[1] = NULL;
	array[2] = NULL;
	struct present *p = stock_list;
	while (p->pid!=-1){
		if (p->pid == pid1){
			if (p->stock_cnt > 0){
				array[0] = p;
			}
		}
		else if (p->pid == pid2){
			if (p->stock_cnt > 0){ 
                                array[1] = p;
			}
		}
		else if (p->pid == pid3){
			if (p->stock_cnt > 0){ 
                                array[2] = p;
                        }
		}
		p = p->next;
	}
	int index;
	for (index = 0;index < 3;index++){
		if (array[index]!= NULL){
			array[index]->stock_cnt--;
			return array[index]->pid;
		}
	}
	return -2;
}


void insert_district(struct child *c){
	struct district *d_prev = NULL;
	struct district *d = NULL;
	struct present_assign* pa_iter = NULL ;
	struct district *new_d = NULL;

        new_d = (struct district*) malloc(sizeof(struct district));
        new_d->did = c->did;
        new_d->assignL = (struct present_assign*) malloc(sizeof(struct present_assign));
        new_d->assignL->cid = c->cid;
        new_d->next = NULL;
        
	if (district_list == NULL){ //inserting in an empty list
//		district_list =(struct district*) malloc(sizeof(struct district));
//		district_list->next = NULL;
//		district_list->did = c->did;
//		district_list->assignL =(struct present_assign*) malloc(sizeof(struct present_assign));
//		district_list->assignL->cid = c->cid;
            new_d->assignL->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);
            district_list = new_d;
//            district_list->assignL->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);
	}

	else{ //list is not empty
		d_prev = district_list;
		d = district_list->next;
//		new_d = (struct district*) malloc(sizeof(struct district));
//		new_d->did = c->did;
//		new_d->assignL = (struct present_assign*) malloc(sizeof(struct present_assign));
//		new_d->assignL->cid = c->cid;
//		new_d->next = NULL;
//		
                
		if (d == NULL){
                    //eisagwgi stin arxi
			if (d_prev->did > c->did){
				new_d->next = d_prev;
                                d_prev->next = NULL;
				new_d->assignL->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);
                                district_list = new_d;

			}
			else if (d_prev->did == c->did){
				pa_iter = d_prev->assignL;
				while (pa_iter->next!=NULL){
					pa_iter = pa_iter->next;
				}
				pa_iter->next = (struct present_assign*)malloc(sizeof(struct present_assign));
				pa_iter->next->cid = c->cid;
				pa_iter->next->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);
				pa_iter->next->next = NULL;
			}
			else{
				d_prev->next = new_d;
				new_d->assignL->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);

			}
		}
		else{
			int flag = 0;
			while(d!=NULL){	
				if (d->did > c->did){
					flag++;
					new_d->next = d;
					d = new_d;
					new_d->assignL->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]); 
                                        return;
				}
				else if (d->did == c->did){
					flag++;
					pa_iter = d->assignL;
					while (pa_iter->next!=NULL){
						pa_iter = pa_iter->next;
					}
					pa_iter->next = (struct present_assign*)malloc(sizeof(struct present_assign));
        	                        pa_iter->next->cid = c->cid;
	                                pa_iter->next->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);

                	                pa_iter->next->next = NULL;
                                        return;

				}

				d_prev =d_prev->next;
				d = d->next;
			}
			if (flag == 0){
				d_prev->next = new_d;
				new_d->assignL->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);

			}
		}
	}
}

int prepare_presents(void) {
	
	struct child *child_iter=NULL;
	int iter;
        //trexoume oles tis iliakes katigories
	for (iter = 0;iter < 4; iter++){
		child_iter = Age_categories[iter];
		while (child_iter!=NULL){
			//printf("\n");
			insert_district(child_iter);
			child_iter = child_iter->next;
		}
	}
	printf("District: \n");
	struct district *d = district_list;
	struct present_assign *pa_iter = NULL;
				
	while(d!=NULL){
		printf("%d\n",d->did);
		pa_iter = d->assignL;
		
		while (pa_iter!=NULL){
					
			printf("\tAssignment:%d %d\n",pa_iter->cid,pa_iter->pid);
			pa_iter = pa_iter->next;
		}
		d=d->next;
	}
	printf("\nDone\n");
	return 1;
}

int give_feedback(int cid, int s_degree) {
	
	if(s_degree<1 || s_degree>5){
		return 0;
	}
	struct district *d=district_list;
	struct present_assign *pa_iter=NULL;
	
			while(d!=NULL){
				pa_iter = d->assignL;
				while (pa_iter!=NULL){
				
					if(pa_iter->cid==cid && pa_iter->pid!=-2){
						pa_iter->s_degree=s_degree;
						printf("F %d %d %d\n",pa_iter->pid,pa_iter->cid,pa_iter->s_degree);
                                                printf("\nDone\n");
						return 1;
					}
					if(pa_iter->pid==-2){
						pa_iter->s_degree=1;
						printf("F %d %d %d\n",pa_iter->pid,cid,s_degree);
                                                printf("\nDone\n");
						return 1;
					}
					pa_iter=pa_iter->next;
				}				
				d=d->next;
			}
	//printf("F %d %d %d\n",pa_iter->pid,cid,s_degree);
	printf("\nDone\n");
	return 1;
}

int analytics(void) {
	struct present *temp = NULL;
	temp=InsertionSort(stock_list);
	
	printf("A:\n");
	while(temp->pid!=-1){
		printf("%d %d\n",temp->pid,temp->request_cnt);
                temp=temp->next;
	}
	printf("\nDone\n");
            
	return 1;
}

struct present *InsertionSort(struct present *p){
   struct present * temp1,*temp2;
   int key; 
   for(temp1=p->next;temp1->pid!=-1;temp1=temp1->next){
        key=temp1->request_cnt;
        temp2=temp1->prev;
        while(temp2->pid!=-1 && temp2->request_cnt < key){
//            temp2->next=temp2;
            temp2->next->request_cnt = temp2->request_cnt;

            temp2=temp2->prev;
              

        }
        temp2->next->request_cnt=key;
        
    }
    return p;
}

//copy child s to child d
void copy_child(struct child* s, struct child* d)
{
	d->cid = s->cid;
	d->age = s->age;
	d->did = s->did;
	d->present_choices[0] = s->present_choices[0];
	d->present_choices[1] = s->present_choices[1];
	d->present_choices[2] = s->present_choices[2];
	d->next = NULL;
}


void increase_age(struct child *c)
{
	c->age++;
}

void nullify_presents(struct child* c)
{
	int i=0;
	if (c==NULL)
	{
		fprintf(stderr,"Can't nullify presents on NULL child\n");
		return;
	}
	for (i=0;i<=3;++i)
	{
		c->present_choices[i]=0;
	}


}

int new_season(void) {
	/*struct child *tmp1, *tmp2 = NULL;
	int i = 0;	


	// iterating Age categories
	for (i=0;i<3; ++i)
	{
		tmp1 = Age_categories[i];

		//running each age category
		while (tmp1!=NULL)
		{
			//check if child has to change age category
			if (tmp1->age == 3	 
				|| tmp1->age == 7 
				|| tmp1->age == 11)
			{
				tmp2 = (struct child*) malloc (sizeof(struct child));
				copy_child(tmp1, tmp2);
				remove_child(tmp1);
				nullify_presents(tmp2);
				increase_age(tmp2);
				//inserting to next age category
				insert_child(tmp2, i+1);

			}
			else if(tmp1->age == 15) remove_child(tmp1);
			else
			{
				increase_age(tmp1);
				nullify_presents(tmp1);
			}
			tmp1 = tmp1->next;
		}
	}
        */
	return 1;
}

int clear_list_of_children(void) {
	struct child *temp,*prev;
	int i,k;
	int j=0;
	for(i=0;i<4;i++){
		temp=Age_categories[i];
		while(temp!=NULL){
			prev=temp;				
			if((temp->present_choices[j]==0) && (temp->present_choices[++j]==0) && (temp->present_choices[++j]==0)){
				if(prev!=NULL){
					prev->next=temp->next;
				}
				free(temp);
			}
			temp=temp->next;
		}
	}
	print_child();


        printf("\nDone\n");

	return 1;
}

int search_present(int pid) {
	struct	present *p;
	p=stock_list;
	while(p->pid!=-1){
		if(p->pid==pid){
			printf("S %d\n",p->pid);
			printf("%d %d\n",p->stock_cnt,p->request_cnt);
                       // printf("\nDone\n");
			return 1;
		}
		p=p->next;
	} 
	printf("S %d\n",pid);
	p->stock_cnt=0;
	p->request_cnt=0;
	printf("%d %d\n",p->stock_cnt,p->request_cnt);
	return 1;
}

int print_district(void) {
	/*struct district *d;
	struct present_assign *p;
	d=district_list;
	printf("\nDistricts:\n");
	while(d!=NULL){
		printf("%d\n",d->did);
		p=d->assignL;
		printf("Assignment:");
		while(p!=NULL){
			printf("%d %d ",p->cid,p->pid);
			p=p->next;
		}
		d=d->next;
		printf("\n");
	}
	printf("Done\n");*/
	return 1;
}

int print_stock(void) {
	struct present *p = stock_list;
	printf("Stock = ");
	while (p->pid!=-1){
		if (p->stock_cnt == 0){
			printf("%d ",p->pid);
		}
		p = p->next;
	}
	printf("\n");
	return 1;
}

int advanced_analytics(void) {
   /*struct district *d;
   struct present_assign *pa;
    d=district_list;
   
    while(d!=NULL){
     printf("%d ",d->did);
        pa=d->assignL;
        pa=InsertionSort();
        while(pa!=NULL){
            if(pa->s_degree=5){
                 printf("%d ",pa->pid);
            }
            pa=pa->next;
        }
    
    d=d->next;
        printf("\n");
    }*/
    return 1;
}

void tokenize(char *s) { /*tokenization of input arguments*/
	char *p, *last;
	int i = 0;
	for ((p = strtok_r(s, " ", &last)); p;
	    (p = strtok_r(NULL, " ", &last))) {
		if (i < LEN(tokens) - 1) {
			tokens[i] = p;
			asint[i] = atoi(p);
			i++;
		}
	}
	tokens[i] = NULL;
}



void initialize_project()
{
	int i;
	insert_present(-1,-1);//insert guardian node to presents
	for( i=0; i<N; ++i)
	{
		Age_categories[i]=NULL;
	}

}

int print_child()
{
	int i=0;
	struct child *tmp1 = NULL;
	//age categories
	for (;i<4;++i)
	{
		switch (i){
			case 0:
				printf("\n\t0-3:\t");
				break;
			case 1:
				printf("\n\t4-7:\t");
				break;
			case 2:
				printf("\n\t8-11:\t");
				break;
			case 3:
				printf("\n\t12-15:\t");
				break;
			default: break;
		}

		for (tmp1 = Age_categories[i]; tmp1!=NULL; tmp1=tmp1->next)
		{
			printf("%d:%d ", tmp1->cid, tmp1->age);
		}
	}
	printf("\n");
	return 1;
}


int main(int argc, char *argv[]) { /*main function*/
	char *prog = argv[0];
	char *file = argv[1];
	char buf[1024];
	FILE *fp;
	int ret;
	char ev;

	if (file == NULL) {
		fprintf(stderr, "Usage: %s file\n", prog);
		return 1;
	}

	fp = fopen(file, "r");
	if (fp == NULL) {
		fprintf(stderr, "fopen %s: %s\n", file, strerror(errno));
		return 1;
	}

	initialize_project();


	while (fgets(buf, sizeof(buf), fp) != NULL) {
		buf[strcspn(buf, "\n")] = '\0';
		tokenize(buf);
		ev = *tokens[0];

		switch (ev) {
		case 'B':
			ret = buy_present(asint[1], asint[2]);
			break;
		case 'L':
			ret = letter_received(asint[1], asint[2], asint[3], asint[4], asint[5], asint[6]);
			break;
		case 'P':
			ret = prepare_presents();
			break;
		case 'F':
			ret = give_feedback(asint[1], asint[2]);
			break;
		case 'A':
			ret = analytics();
			break;
		case 'N':
			ret = new_season();
			break;
		case 'C':
			ret = clear_list_of_children();
			break;
		case 'S':
			ret = search_present(asint[1]);
			break;
		case 'H':
			ret = print_child();
			break;
		case 'I':
			ret = print_district();
			break;
		case 'T':
			ret = print_stock();
			break;
		case 'D':
			ret = advanced_analytics();
			break;
		default:
			fprintf(stderr, "Invalid event");
			return 1;
		}
		fprintf(stderr, "Event '%c' %s\n", ev, ret ? "passed" : "failed");
	}
	print_child();
	return 1;
}

/*

Sample events:

B 20 10
B 30 15
B 40 20
B 10 5
B 11 5
B 12 5
B 13 5
B 14 5
L 10 2 3021 10 11 12
L 11 14 30231 10 11 12
L 15 1 30261 10 11 12
L 14 2 30271 10 11 12
L 100 4 30271 10 11 30
L 102 11 30271 20 30 40
L 112 11 30271 11 30 40
L 122 11 30271 11 30 40
L 127 14 30281 11 30 40
L 150 15 30241 11 30 40
L 151 15 30251 11 30 40
P
F 10 2
F 11 5
F 151 5
F 102 3
A
N
H
I
T
D
*/

/*I would like to thank the PhD candidates of the Department, who have been TAs of the course, Papaioannou Antonios and Zakkak Foivos for the provided material*/