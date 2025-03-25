/**********************************************************************
 * @file   santa_claus.c                                              *
 * @author Papaioannou Antonis <papaioan@csd.uoc.gr>            *
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
struct present *stock_tree=NULL;
struct present *stock_sentinel=NULL;
struct child *Age_categories[N];
struct district *district_list = NULL;
struct present *array[3];
//struct present *hasharray[district_list->children_cnt];
//struct present *guard_node = NULL;
 
char *tokens[128];
int asint[LEN(tokens)];
 
int buy_present(int pid, int stock_cnt) {
    //if(pid<0||stock_cnt<0) return 0;
    stock_tree=insert_present(stock_tree, pid, stock_cnt);
   
   
    //inorder(temp,pid,stock_cnt);
    printf("B %d %d\n", pid, stock_cnt);
    //int x= print_inorder(temp);
    // printf("%d\n",x);
    //insert_present(pid,stock_cnt);
    return 1;
}
 
struct present* insert_present( struct present *p, int pid, int stock_cnt )
{
    struct present *temp = p;
    struct present *new_node;
       
    if(temp->pid==-1) {
            new_node=malloc(sizeof(struct present));
            new_node->request_cnt=0;
            new_node->lc=temp;
            new_node->rc=temp;
            new_node->pid=pid;
        new_node->stock_cnt=stock_cnt;
        new_node->parent=temp->parent;
        temp->parent = new_node;
            temp=new_node;
     }
    else if(pid==temp->pid){
            temp->stock_cnt+=stock_cnt;
    }
        else if(pid<temp->pid){
     temp->lc=insert_present(temp->lc, pid, stock_cnt);
    } else {
     temp->rc=insert_present(temp->rc, pid, stock_cnt);
    }
        return temp;
}
 
void print_inorder(struct present *p)
{
   
    if(p->pid==-1)
    return;
       
    print_inorder(p->lc);
 
    printf("Present ID = %d\n",p->pid);
     
    print_inorder(p->rc);
}
 
  /*void inorder(struct present *p,int pid,int stock_cnt){
      if (p->pid==-1) {
          insert_present(pid,stock_cnt);
          return;
      }
      inorder(p->lc,pid,stock_cnt);
      //printf("Presents:");
     
      visit(p);
      inorder(p->rc,pid,stock_cnt);
   }*/
  struct present* inorderrec(struct present *p,struct present *prev,int pid1,int pid2,int pid3){
      int flags[3]={0};
      if(p->pid==-1) return stock_tree;
      p->lc=inorderrec(p->lc,prev,pid1,pid2,pid3);
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
        p->rc=inorderrec(p->rc,p,pid1,pid2,pid3);
        if (flags[0]==0) p=insert_present(p, pid1, 10);
    if (flags[1]==0) p=insert_present(p, pid2, 10);
    if (flags[2]==0) p=insert_present(p, pid3, 10);
 
    return ;
  }
 /*void visit(struct present *p){
     
   // printf("Presents=");
     printf("%d %d",p->pid,p->stock_cnt);
  }*/
   
 
 
int letter_received(int cid, int age, int did, int pid1, int pid2, int pid3) {
    struct child*c;
    c=malloc(sizeof(struct child));
    c->cid = cid;
    c->age = age;
    c->did = did;
    c->present_choices[0]= pid1;
    c->present_choices[1] = pid2;
    c->present_choices[2] = pid3;
        //inserting the new child at the right place
        if (age<=3){
      Age_categories[0]=insert_child(c,0);
     //   c=insert_child(c,0);
    //preorder(Age_categories[0]);
        }
    else if (age<=7){
       Age_categories[1]= insert_child(c,1);
       //c= insert_child(c,1);
      //   preorder(Age_categories[1]);
    }
    else if (age<=11){
       Age_categories[2] =insert_child(c,2);
        //c= insert_child(c,2);
        // preorder(Age_categories[2]);
        }
    else if (age<=15) {     
       Age_categories[3]= insert_child(c,3);
       //insert_child(c,3);
        //preorder(Age_categories[3]);
        }
        //inorderrec(stock_tree,stock_tree->parent,pid1,pid2,pid3);
   //stock_tree=inorderrec(stock_tree,stock_tree->parent,pid1,pid2,pid3);
        //insert_district(c);
        
     printf("L %d %d %d %d %d %d\n",cid,age,did,pid1,pid2,pid3);
    
    return 1;
}
struct child *insert_child(struct child *c, int age_cat){
    struct child *temp,*prev=c,*nd;
    //temp=malloc(sizeof(struct child));
   
   
    temp=Age_categories[age_cat];
     prev=temp;
    if(temp==NULL){
       
        temp=c;
        temp->lc=NULL;
        temp->rc=NULL;
        
    }
   
        /*if(c->age<4){
            age_cat=0;
        }
        else if(c->age<8){
            age_cat=1;
        }
        else if(c->age<12){
            age_cat=2;
        }
        else if(c->age<16){
            age_cat=3;
        }*/
      if (c==NULL) return NULL;
     if(prev==findnextsmallest(c,age_cat)){
               nd=prev;
     }
       
    else {
     prev=findLeftmostNode(c);
     nd=prev;
    }    
        if(nd->lc!=NULL && nd->rc==NULL){
            nd->rc=c;
        }
         if(nd->rc!=NULL && nd->lc==NULL){
            nd->lc=c;
        }
     if(nd->lc!=NULL && nd->rc!=NULL) {
        nd= nextInorderSuccessor(Age_categories[age_cat], nd);
        if(nd->lc!=NULL && nd->rc==NULL){
            nd->rc=c;
        }
         if(nd->rc!=NULL && nd->lc==NULL){
            nd->lc=c;
        }
     }
    c->lc=insert_child(c->lc,age_cat);
    c->rc=insert_child(c->rc,age_cat);
    return c;
}
 
/*struct district* insert_district(struct child *c){
    struct district *d_prev,*d,*new_d;
    struct present_assign* pa_iter = NULL ;
   
   new_d = (struct district*) malloc(sizeof(struct district));
        new_d->did = c->did;
        new_d->assignHT = (struct present_assign*) malloc(sizeof(struct present_assign));
        new_d->assignHT->cid-> = c->cid;
        new_d->next = NULL;
        if (district_list == NULL){
            new_d->assignHT=NULL;
                // new_d->assignHT->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);
            district_list = new_d;
        }
        else{ //list is not empty
        d_prev = district_list;
        d = district_list->next;
//      new_d = (struct district*) malloc(sizeof(struct district));
//      new_d->did = c->did;
//      new_d->assignL = (struct present_assign*) malloc(sizeof(struct present_assign));
//      new_d->assignL->cid = c->cid;
//      new_d->next = NULL;
//     
               
        if (d == NULL){
                    //eisagwgi stin arxi
            if (d_prev->did > c->did){
                new_d->next = d_prev;
                                d_prev->next = NULL;
                                new_d->assignHT=NULL;
                //new_d->assignHT->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);
                                district_list = new_d;
 
            }
            else if (d_prev->did == c->did){
                                d_prev->children_cnt+=1;
                pa_iter = d_prev->assignHT;
                //while (pa_iter->next!=NULL){
                //  pa_iter = pa_iter->next;
                //}
                //pa_iter->next = (struct present_assign*)malloc(sizeof(struct present_assign));
                //pa_iter->next->cid = c->cid;
                //pa_iter->next->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);
                //pa_iter->next->next = NULL;
            }
            else{
                d_prev->next = new_d;
                //new_d->assignΗΤ->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);
 
            }
        }
        else{
            int flag = 0;
            while(d!=NULL){
                if (d->did > c->did){
                    flag++;
                    new_d->next = d;
                    d = new_d;
                                        new_d->assignHT=NULL;
                    //new_d->assignHT->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);
                                        return;
                }
                else if (d->did == c->did){
                                         d->children_cnt+=1;
                    flag++;
                    pa_iter = d->assignHT;
                    //while (pa_iter->next!=NULL){
                    //  pa_iter = pa_iter->next;
                    //}
                    //pa_iter->next = (struct present_assign*)malloc(sizeof(struct present_assign));
                                    //pa_iter->next->cid = c->cid;
                              //      pa_iter->next->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);
 
                                    //pa_iter->next->next = NULL;
                                        //return;
 
                }
 
                d_prev =d_prev->next;
                d = d->next;
            }
            if (flag == 0){
                d_prev->next = new_d;
                                new_d->assignHT=NULL;
                //new_d->assignHT->pid = get_presents(c->present_choices[0],c->present_choices[1],c->present_choices[2]);
 
            }
        }
    }
        }*/
 
   
    void preorder(struct child *c,int age_cat){
        //int age_cat;
        if (c==NULL) return;
         printf("%d child cid: %d\n",age_cat,c->cid);
      preorder(c->lc,age_cat);
      
      preorder(c->rc,age_cat);
   }
   
   
 struct child* nextInorderSuccessor(struct child* root, struct child* find) {
    if (!root || !find) return NULL;
 
    //if a node has right child
    //loop to the left most child (of the right child)
    //if none, return right child
    //if no right child (2 situations):
    //if current node is left child of parent: return parent (parent is NULL for root)
    //else if right child return grandparent
    struct child* successor = NULL;
    if (find->rc){
        successor = find->rc;
        while (successor->lc) {
            successor = successor->lc;
        }
    }
    else {
        //this is a modified find on the "find" node
        //where when the node to be found is smaller than
        //it's parent node, the successor pointer is
        //updated to point to the parent
        while (root) {
            if (find->cid < root->cid) {
                successor = root;
                root = root->lc;
            }
            else if (find->cid > root->cid) {
                root = root->rc;
            }
            else {
                break;
            }
        }
         }
    return successor;
}
struct child *findnextsmallest(struct child*c,int age_cat){
    struct child* temp,*lock;
    int difference=0,min=0;
    Age_categories[age_cat]=c;
    temp=Age_categories[age_cat];
    if(c->cid<temp->cid){
        while(temp->lc!=NULL){
            if(c->cid>temp->cid){
                difference=c->cid-temp->cid;
                if(difference<min){
                    min=difference;
                    lock=temp;
                }
            }
            temp=temp->lc;
        }
    }
   
    else if(c->cid>temp->cid){
    while(temp->rc!=NULL){
        if(c->cid>temp->cid){
            difference=c->cid-temp->cid;
                if(difference<min){
                    min=difference;
                    lock=temp;
        }
    }
        temp=temp->lc;
    }
}
    return lock;
}
struct child *findLeftmostNode(struct child*c){
    if (c==NULL) return NULL;
    while(c->lc!=NULL){
        c=c->lc;
    }
    return c;
}
 
 
 
int prepare_presents(void) {
   
    /*struct child *child_iter=NULL;
    int iter;
        //trexoume oles tis iliakes katigories
    for (iter = 0;iter < 4; iter++){
        child_iter = Age_categories[iter];
        while (child_iter!=NULL){
            //printf("\n");
                        preorder(child_iter);
            insert_district(child_iter);
            //child_iter = child_iter->next;
        }
    }*/
   
               
   
    return 1;
}
/*int get_presents(int pid1,int pid2,int pid3){
        inorderpresent2(stock_tree,int pid1,int pid2,int pid3)
       int index;
    for (index = 0;index < 3;index++){
        if (array[index]!= NULL){
            array[index]->stock_cnt--;
            return array[index]->pid;
        }
    }
    return -2;
     
       
}
void inorderpresent2(struct present *p,int pid1,int pid2,int pid3){
   
    if (p->pid==-1) return;
    inorderpresent2(p->lc,int pid1,int pid2,int pid3) ;  
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
      inorderpresent2(p->lc,int pid1,int pid2,int pid3) ;  
}*/
 
int give_feedback(int cid, int did, int s_degree) {
   
    /*if(s_degree<1 || s_degree>5){
        return 0;
    }
    struct district *d=district_list;
    struct present_assign *pa_iter=NULL;
   
            while(d!=NULL){
                pa_iter = d->assignHT;
//              while (pa_iter!=NULL){
//             
//                  if(pa_iter->cid==cid && pa_iter->pid!=-2){
//                      pa_iter->s_degree=s_degree;
//                      printf("F %d %d %d\n",pa_iter->pid,pa_iter->cid,pa_iter->s_degree);
//                                                printf("\nDone\n");
//                      return 1;
//                  }
//                  if(pa_iter->pid==-2){
//                      pa_iter->s_degree=1;
//                      printf("F %d %d %d\n",pa_iter->pid,cid,s_degree);
//                                                printf("\nDone\n");
//                      return 1;
//                  }
//                  pa_iter=pa_iter->next;
//              }              
//              d=d->next;
//          }
    //printf("F %d %d %d\n",pa_iter->pid,cid,s_degree);
    printf("\nDone\n");*/
    return 1;
}
 
int analytics(int k) {
    return 1;
}
 
int new_season(void) {
    return 1;
}
 
int clear_list_of_children(void) {
     /*printf("apotelesma katharsis............");
    int i,j,k;
    for( i=0;i<4;i++){
        for(j=0;j<3;j++){
            if(Age_categories[i]->present_choices[j]==-1){
                 remove_child(Age_categories[i],i);
                
                 
            }
            // k=print_child();
        }
       
    } 
                 // printf("%d",k);
    printf("apotelesma katharsis............");*/
    return 1;
}
struct child* remove_child(struct child *c, int age_cat){
    struct child *temp,*prev;
    temp=Age_categories[age_cat];
  Age_categories[age_cat]=c;
   
    if(temp->lc==NULL && temp->rc==NULL){
        
        free(temp);
      
   }
         
        
        
    
   
      if (c==NULL) return NULL;
    
       
    
        if(temp->lc!=NULL && temp->rc==NULL){
           free(c) ;
        }
         if(temp->rc!=NULL && temp->lc==NULL){
           temp->rc=c->rc;
            free(c);
        }
     if(temp->lc!=NULL && temp->rc!=NULL) {
        prev= nextInorderSuccessor(Age_categories[age_cat], temp);
        if(temp->lc!=NULL){
            free(temp);
        }
         if(temp->rc!=NULL){
            free(temp);
        }
     }
    c->lc=remove_child(c->lc,age_cat);
    c->rc=remove_child(c->rc,age_cat);
    return c;
}
 
int search_present(int pid) {
    searchprint_inorder(stock_tree,pid);
    return 1;
}
void searchprint_inorder(struct present *p,int pid){
    if(p->pid==-1)
    return;
       
    print_inorder(p->lc);
    printf("stockadiatheta:");
    if(p->pid==pid){
    printf("pid stock_cnt : %d  %d\n",p->pid,p->stock_cnt);
    return;
    }
    print_inorder(p->rc);
}
int print_child(void) {
    int i;
    printf("H\n");
    for(i=0;i<4;i++){
        preorder(Age_categories[i],i);
    }
    printf("\nDone\n");
    return 1;
}
 
int print_district(void) {
    return 1;
}
 
int print_stock(void) {
    print_inorder_adiatheto(stock_tree);
    return 1;
}
void print_inorder_adiatheto(struct present *p)
{
   
    if(p->pid==-1)
    return;
       
    print_inorder(p->lc);
    printf("stockadiatheta:");
    if(p->stock_cnt<=0){
    printf("Present ID = %d\n",p->pid);
    }
    print_inorder(p->rc);
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
 
int main(int argc, char *argv[]) { /*main function*/
    char *prog = argv[0];
    char *file = argv[1];
    char buf[1024];
    FILE *fp;
    int ret;
    char ev;
    int i;
 
    stock_sentinel= (struct present *) calloc(1,sizeof(struct present));
       
        stock_sentinel->lc=NULL;
    stock_sentinel->rc=NULL;
        stock_sentinel->parent=NULL;
    stock_sentinel->pid = -1;
    stock_sentinel->stock_cnt=-1;
    stock_sentinel->request_cnt=-1;
    if (file == NULL) {
        fprintf(stderr, "Usage: %s file\n", prog);
        return 1;
    }
 
    fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stderr, "fopen %s: %s\n", file, strerror(errno));
        return 1;
    }
       // insert_present(-1,-1,NULL);
    stock_tree = stock_sentinel;
    while (fgets(buf, sizeof(buf), fp) != NULL) {
        buf[strcspn(buf, "\n")] = '\0';
        tokenize(buf);
        ev = *tokens[0];
 
        switch (ev) {
        case 'B':
            ret = buy_present(asint[1], asint[2]);
            printf("\tPresent list\n");
            print_inorder(stock_tree);
            break;
        case 'L':
            
            ret = letter_received(asint[1], asint[2], asint[3], asint[4], asint[5], asint[6]);
            
            for(i=0;i<=3;i++){
                printf("\tchild array tree %d\n",i);
                preorder(Age_categories[i],i);
            }
            break;
        case 'P':
            ret = prepare_presents();
            break;
        case 'F':
            ret = give_feedback(asint[1], asint[2], asint[3]);
            break;
        case 'A':
            ret = analytics(asint[1]);
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
        default:
            fprintf(stderr, "Invalid event");
            return 1;
        }
        fprintf(stderr, "Event '%c' %s\n", ev, ret ? "passed" : "failed");
    }
    return 1;
}