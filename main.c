//
//  学生成绩管理系统.c
//  小学期作业
//
//  Created by LanXKay on 2018/9/10.
//  Copyright  2018 LanXKay. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//定义学生结构体
typedef struct student{
    int id;//学号
    char name[20];//姓名
    int cgrade;//c语言成绩
    int egrade;//英语成绩
    int mgrade;//数学成绩
    int total;//总分
}student;

//定义单链表中节点的类型
typedef struct node{
    student data;
    struct node *next;
}Node, *Link;

//函数声明
void Menu(void);
Link Add(Link);
Link SortId(Link);
Link SearchName(Link, char*);
Link SearchId(Link, int);
void PrintData(Link);
void Modify(Link, char*);
void DelName(Link, char*);
void DelId(Link, int);
void Count(Link);
void TestId(Link, Link);
int IdRepeat(int, Link);
void Testgra(Link, char);
void Save(Link);
void Output(Link);


//创建用户提示菜单
void Menu(void)
{
    int i;
    printf("★");
    for(i=0; i<36; i++)
        printf("-");
    printf("★");
    printf("\n");
    printf("|            学生成绩管理系统          |\n");
    printf("|                                      |\n");
    printf("|1.输入学生信息          2.查询学生信息|\n");
    printf("|                                      |\n");
    printf("|3.输出学生信息          4.更新学生信息|\n");
    printf("|                                      |\n");
    printf("|5.统计学生信息          6.退出系统    |\n");
    printf("★");
    for(i=0; i<36; i++)
        printf("-");
    printf("★");
    printf("\n");
}

//输入学生信息
Link Add(Link pHead)
{
    Link s = (Link) malloc(sizeof(Node));//创建节点s
    
    //将学生信息输入到节点s的data中
    printf("请输入学生的信息：\n");
    printf("姓名：");
    scanf("%s", s->data.name);
    printf("学号：");
    TestId(s, pHead);
    printf("数学成绩：");
    Testgra(s, 'm');
    printf("英语成绩：");
    Testgra(s, 'e');
    printf("c语言成绩：");
    Testgra(s, 'c');
    s->data.total = s->data.cgrade + s->data.egrade + s->data.mgrade;
    printf("\n输入成功。\n");
    return s;
}

//修改\验证学号
void TestId(Link s, Link pHead)
{
    int id, flag=1;
    while(flag){
        if( (scanf("%d", &id)) == 1 && id>=2015000000 && id<= 2019000000){
            if( IdRepeat(id, pHead) == 0){
                s->data.id = id;
                flag = 0;
            }
            else printf("您输入的学号已存在，请重新输入：");
        }
        else printf("您输入的学号有误，请输入正确的学号:");
    }
}

//检查输入（更改）的学号是否重复，若重复则返回1否则返回0
int IdRepeat(int id, Link pHead)
{
    Link p = pHead->next;
    int i=0;
    while(p){
        if(id == p->data.id) i=1;
        p = p->next;
    }
    return i;
}

//修改\验证成绩
void Testgra(Link s, char x)
{
    int g, flag=1;
    while(flag){
        if( (scanf("%d", &g)) == 1 && g>=0 && g<=100){
            switch(x){
                case 'm': s->data.mgrade = g; break;
                case 'e': s->data.egrade = g; break;
                case 'c': s->data.cgrade = g; break;
            }
            s->data.total =  s->data.total = s->data.cgrade + s->data.egrade + s->data.mgrade;
            flag = 0;
        }
        else printf("您输入的成绩有误，请输入正确的成绩:");
    }
}

//学生信息排序（根据学号）
Link SortId(Link pHead)
{
    Link p,q;
    Link t = (Link) malloc(sizeof(Node));
    
    for(p=pHead->next;p!=NULL;p=p->next)
    {
        for(q=p->next;q!=NULL;q=q->next)
        {
            if(p->data.id > q->data.id)
            {
                t->data=p->data;
                p->data=q->data;
                q->data=t->data;
            }
        }
    }
    return pHead;
}

//查询学生信息（通过名字）
Link SearchName(Link pHead,char* name)
{
    Link s = pHead->next;
    while((s != NULL) && (strcmp(s->data.name, name)!= 0) )
        s = s->next;
    if(s == NULL){
        printf("\n您所查询的姓名不存在。\n");
        return NULL;
    }
    else{
        printf("\n结果如下：\n\n%d    %s\t数学成绩：%d\t英语成绩：%d\tC语言成绩：%d\t总分：%d\n",
               s->data.id, s->data.name, s->data.mgrade, s->data.egrade, s->data.cgrade,s->data.total);
        return s;
    }
}

//查询学生信息（通过学号）
Link SearchId(Link pHead, int id)
{
    Link s = pHead->next;
    while( (s != NULL) && (s->data.id != id))
        s = s->next;
    if(s == NULL){
        printf("\n你所查询的学号不存在。\n");
        return NULL;
    }
    else{
        printf("\n结果如下：\n\n%d    %s\t数学成绩：%d\t英语成绩：%d\tC语言成绩：%d\t总分：%d\n",
               s->data.id, s->data.name, s->data.mgrade, s->data.egrade, s->data.cgrade,s->data.total);
        return s;
    }
}

//输出学生信息
void PrintData(Link pHead)
{
    Link p =pHead->next;
    if(pHead->next == NULL)
        printf("\n学生信息为空。\n");
    else{
        printf("\n所有学生信息如下：\n");
        while(p){
            printf("%d    %s\t数学成绩：%d\t英语成绩：%d\tC语言成绩：%d\t总分：%d\n",
                   p->data.id,p->data.name,p->data.mgrade,p->data.egrade,p->data.cgrade,p->data.total);
            p=p->next;
        }
    }
}

//修改学生信息（通过名字）
void Modify(Link pHead,char *name)
{
    int subject;
    Link q=pHead->next;
    while(strcmp(q->data.name, name)!= 0 && q->next != NULL)
        q=q->next;
    if(strcmp(q->data.name, name)!= 0)
        printf("\n您所希望修改的学生的名字不存在，请输入正确的名字！\n");
    else{
        printf("\n请输入您希望修改的该学生的数据的对应数字：\n0.学号\t1.数学\t2.英语\t3.C语言\n");
        printf("请输入：");
        scanf("%d", &subject);
        switch(subject){
            case 0:{
                printf("请输入更改后的学号:");
                TestId(q, pHead);
                SortId(pHead);
                printf("\n修改成功！\n\n");
            }break;
            case 1:{
                printf("请输入更改后的成绩:");
                Testgra(q, 'm');
                printf("\n修改成功！\n\n");
            }break;
            case 2:{
                printf("请输入更改后的成绩:");
                Testgra(q, 'e');
                printf("\n修改成功！\n\n");
            }break;
            case 3:{
                printf("请输入更改后的成绩:");
                Testgra(q, 'c');
                printf("\n修改成功！\n\n");
            }break;
            default: printf("请输入正确的操作。");break;
        }
    }
}

//删除学生信息（通过名字）
void DelName(Link pHead,char* name)
{
    Link p = pHead;
    Link q = pHead->next;
    while((q != NULL) && (strcmp(q->data.name, name))!= 0 )
    {
        q = q->next;
        p = p->next;
    }
    if(q == NULL)
        printf("\n您所希望删除的姓名不存在\n");
    else{
        p->next = q->next;
        printf("\n删除完毕!\n");
        free(q);
    }
}

//删除学生信息（通过学号）
void DelId(Link pHead,int id)
{
    Link p = pHead;
    Link q = pHead->next;
    while((q != NULL) && q->data.id != id )
    {
        q = q->next;
        p = p->next;
    }
    if(q == NULL)
        printf("\n您所希望删除的姓名不存在\n");
    else{
        p->next = q->next;
        printf("\n删除完毕!\n");
    }
}

//统计学生信息
void Count(Link pHead)
{
    Link p = (Link) malloc(sizeof(Node));
    p=pHead->next;
    int tMax=p->data.total;
    int mMax=p->data.mgrade;
    int eMax=p->data.egrade;
    int cMax=p->data.cgrade;//定义总分，数学，英语，C语言最高分
    float mAver;
    float eAver;
    float cAver;//定义各科平均分
    float mSum=0;
    float eSum=0;
    float cSum=0;
    int len = 0;
    printf("\n统计数据如下：\n\n");
    //总分第一名
    printf("总分第一名：\n");
    for(p=pHead->next;p!=NULL;p=p->next)
        if(tMax < p->data.total) tMax=p->data.total;
    for(p=pHead->next;p!=NULL;p=p->next)
        if(tMax==p->data.total) printf("%d    %s\t总分：%d\n",p->data.id,p->data.name,p->data.total);
    printf("\n");
    
    //单科第一名
    printf("数学第一名：\n");
    for(p=pHead->next;p!=NULL;p=p->next)
        if(mMax < p->data.mgrade) mMax=p->data.mgrade;
    for(p=pHead->next;p!=NULL;p=p->next)
        if(mMax==p->data.mgrade) printf("%d    %s\t分数：%d\n",p->data.id,p->data.name,p->data.mgrade);
    printf("\n");
    
    printf("英语第一名：\n");
    for(p=pHead->next;p!=NULL;p=p->next)
        if(eMax < p->data.egrade) eMax=p->data.egrade;
    for(p=pHead->next;p!=NULL;p=p->next)
        if(eMax==p->data.egrade) printf("%d    %s\t分数：%d\n",p->data.id,p->data.name,p->data.egrade);
    printf("\n");
    
    printf("C语言第一名：\n");
    for(p=pHead->next;p!=NULL;p=p->next)
        if(cMax < p->data.cgrade) cMax=p->data.cgrade;
    for(p=pHead->next;p!=NULL;p=p->next)
        if(cMax==p->data.cgrade) printf("%d    %s\t分数：%d\n",p->data.id,p->data.name,p->data.cgrade);
    printf("\n");
    
    //平均分
    for(p=pHead->next;p!=NULL;p=p->next)
    {
        mSum += p->data.mgrade;
        eSum += p->data.egrade;
        cSum += p->data.cgrade;
        len++;
    }
    mAver = mSum/len;
    eAver = eSum/len;
    cAver = cSum/len;
    printf("数学平均分：%.2f\n",mAver);
    printf("英语平均分：%.2f\n",eAver);
    printf("C语言平均分：%.2f\n",cAver);
    
    //不及格人数
    int math=0,eng=0,c=0;//定义不及格人数
    for(p=pHead->next;p!=NULL;p=p->next)
    {
        if(p->data.mgrade < 60) math++;
        if(p->data.egrade < 60) eng++;
        if(p->data.cgrade < 60) c++;
    }
    printf("\n不及格人数为：\n数学： %d\t英语： %d\tC语言：%d\n",math,eng,c);
}

//保存至文件
void Save(Link pHead)
{
    FILE *fp;
    Link p;
    
    if((fp=fopen("C:\\Users\\94483\\Desktop\\理学院1班_2017212439+理学院1班_2017212437\\source_code\\Stu_Score.txt","w+"))==NULL)
    {
        printf("cannot open a file.\n");
        return ;
    }
    p = pHead->next;
    while(p)
    {
        if(p == pHead->next)
            fprintf(fp,"%d      %s    %d    %d    %d    %d\n",
                    p->data.id,p->data.name,p->data.mgrade,p->data.egrade,p->data.cgrade,p->data.total);
        else
            fprintf(fp,"%d      %s    %d    %d    %d    %d\n",
                    p->data.id,p->data.name,p->data.mgrade,p->data.egrade,p->data.cgrade,p->data.total);
        p = p->next;
    }
    fclose(fp);
}

//输出文件数据至链表
void Output(Link pHead)
{
    FILE *fp;
    if((fp=fopen("C:\\Users\\94483\\Desktop\\理学院1班_2017212439+理学院1班_2017212437\\source_code\\Stu_Score.txt","r"))==NULL)
    {
        printf("cannot open a file.\n");
        return ;
    }//打开文件
    
    char ch;
    Link q = pHead;
    q->next = NULL;
    if((ch=fgetc(fp))==EOF)
    {
        pHead->next = NULL;
    }
    else
    {
        while(!feof(fp))
        {
            Link p =(Link)malloc(sizeof(Node));
            fscanf(fp,"%d%s%d%d%d%d ",&p->data.id,p->data.name,&p->data.mgrade,&p->data.egrade,&p->data.cgrade,&p->data.total);
            q->next = p;
            p->next = NULL;
            q = p;
        }
    }
    fclose(fp);
}
