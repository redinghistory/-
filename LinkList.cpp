/**
* 单链表
*/
#include<iostream>
#include<cstdlib>
using namespace std;

typedef int ElemType;//定义数据元素类型

/**
* 单链表结点结构
*/
typedef struct LNode{
    ElemType data; //数据域
    struct LNode *next; //指针域
}LinkNode,*Position,*LinkList;

/**
 * 分配结点，用node指向分配的结点空间，并对结点赋值e
 * @param node
 * @param e
 * @return
 */
bool MakeNode(LinkNode *node,ElemType &e){
    node=(LinkNode*) malloc(sizeof(LinkNode));
    if(!node){
        exit(-2);
    }
    node->data=e;
    node->next= NULL;
    return true;
}
/**
 * 释放结点存储空间
 * @param node
 * @return
 */
bool FreeNode(LinkNode *node){
    free(node);
    node=NULL;
    return true;
}

/**
 * 初始化单链表L
 * @param L
 * @return
 */
bool Init(LinkList &L){
    L=(LinkNode*) malloc(sizeof(LNode));
    if(!L){
        exit(-2);
    }

    L->next=NULL;
    return true;
}

/**
 * 销毁单链表
 * @param L
 * @return
 */
bool Destory(LinkList &L){
    LinkNode *ptr=L->next;
   while(ptr){ //从头到尾，依次释放各个结点的存储空间
       free(L);
       L=ptr;
       ptr=ptr->next;
   }
   free(L);//释放最后一个结点的存储空间
   L=NULL;
   return true;
}
/**
 * 清空单链表，保存头结点
 * @param L
 * @return
 */
bool Clear(LinkList &L){
    LinkNode *temp,*ptr=L->next; //除首结点外，全部释放存储空间，首结点指针域指向NULL
   while(ptr){
       temp=ptr;
       ptr=ptr->next;
       free(temp);
   }
   L->next=NULL;
   return true;
}

/**
 * 在单链表表首插入结点,作为首元结点
 * 将node结点插入到单链表L的头结点之后，作为第一个结点
 * @param L 单链表
 * @param node 要插入的结点
 * @return 插入成功返回true
 */
bool InsertFirst(LinkList &L,LinkNode *node){
    node->next=L->next;
    L->next=node;
    return true;

}

/**
 * 删除首元结点，并以q返回
 * @param L
 * @param q
 * @return
 */
bool DeleteFirst(LinkList &L,LinkList &q){
    q=L->next;
    L->next=L->next->next;
    return true;
}

/**
 * 追加单链表
 * 将s所指的一串结点链接在单链表L的最后一个结点之后
 * @param L
 * @param S
 * @return
 */
bool Append(LinkList &L,LinkList &S){
    LinkNode *ptr=L;
    while(ptr->next){
        ptr=ptr->next;
    }
    ptr->next=S;
}

/**
 * 删除单链表的尾结点
 * @param L
 * @param q
 * @return
 */
bool Remove(LinkList &L,LinkList &q){
    LinkNode *ptr=L;

    while(ptr->next&&ptr->next->next){ //第一个条件是为了确保第二个条件成立
        ptr=ptr->next;
    }
    q=ptr->next;
    ptr->next=NULL;
    return true;
}

/**
 * 后插
 * 在指定单链表结点p后面插入结点s
 * @param L 单链表
 * @param p 指定的结点
 * @param s 要插入的结点
 * @return
 */
bool InsertAfter(LinkList &L,LinkNode* p,LinkNode *s){
    s->next=p->next;
    p->next=s;
    return true;
}

/**
 * 前插
 * 在指定单链表结点p前面插入结点s
 * 后插之后将两个结点值互换就可以实现前插
 * @param L 单链表
 * @param p 指定的结点
 * @param s 要插入的结点
 * @return
 */
bool InsertBefore(LinkList &L,LinkNode* p,LinkNode *s){
    s->next=p->next;
    p->next=s;

    //后插之后将两结点的值互换
    ElemType temp;
    temp=s->data;
    s->data=p->data;
    p->data=temp;
    return true;
}
/**
 * 修改结点值
 * 已知p指向单链表中的一个结点，将此结点值修改为e
 * @param p
 * @param e
 * @return
 */
bool SetCurrentElem(LinkNode*p,ElemType &e){
    p->data=e;
    return true;
}

/**
 * 取给定结点的值
 * @param p
 * @return
 */
ElemType& GetCurrentElem(LinkNode *p){
    return p->data;
}

/**
 * 判断单链表是否为空
 * @param L
 * @return
 */
bool Empty(LinkList &L){
    if(L->next==NULL){
        return true;
    } else{
        return false;
    }
}

/**
 * 求单链表L的长度
 * @param L
 * @return 单链表长度
 */
int Length(LinkList&L){
    int length=0;
    LinkNode *p=L;
    while(p->next){
        length++;
        p=p->next;
    }
    return length;
}

/**
 * 求单链表头结点的长度（注意不是首元结点）
 * @param L
 * @return
 */
LinkNode* GetHead(LinkList &L){
    return L;
}
/**
 * 返回指向单链表最后一个结点的指针
 * @param L
 * @return
 */
LinkNode* GetLast(LinkList &L){
    LinkNode *p=L;
    while(p->next){
        p=p->next;
    }
    return p;
}
/**
 * 返回指向前驱的指针
 * @param L
 * @param p
 * @return
 */
LinkNode* Prior(LinkList &L,LinkNode *p){
    LinkNode * ptr=L;
    while(ptr){
        if(ptr->next==p){
            return ptr;
        }
        ptr=ptr->next;
    }
    return ptr;
}

 /**
  * 后继
  * @param L
  * @param p
  * @return
  */
LinkNode *Next(LinkList &L,LinkNode *p){
    LNode *ptr=L;
    while(ptr){
        if(ptr==p){
            return ptr->next;
        }
        ptr=ptr->next;
    }
    return ptr;
}

/**
 * 寻找指定 位序的结点
 * @param L  单链表
 * @param i 指定的位序
 * @param p 指向指定位序的指针
 * @return
 */
bool Locate(LinkList &L,int i, LinkNode *p){
    int counter=0;
    LinkNode *ptr=L;
    while(counter<i&&p->next){
        ptr=ptr->next;
        counter++;
    }
    p=ptr;
}

/**
 * 返回单链表中第一个和e满足compare关系的结点指针
 * @param L 单链表
 * @param e
 * @param compare 比较关系的函数
 * @return
 */
LinkNode* LocateElem(LinkList&L,ElemType e,bool(*compare)(ElemType a,ElemType b)){
    LinkNode *ptr=L;
    while(ptr){
        ptr=ptr->next;
        if(compare(e,ptr->data)){
            return ptr;
        }
    }
    return NULL;
}
/**
 * 遍历单链表元素
 * 对每一个单链表元素调用visit函数
 * @param L
 * @param visit
 * @return
 */
bool Traverse(LinkList &L,bool(*visit(ElemType e))){
    LinkNode *node=L->next;
    while(node){
        if(!visit(node->data)){
            return false;
        }
    }
    return true;
}

/**
 * 在第i个结点之前之后插入元素e
 * @param L
 * @param i
 * @param e
 * @return
 */
bool Insert(LinkList &L,int i,ElemType e){
    LinkNode *node,*s;
    if(!Locate(L,i-1,node)){
        return -1;
    }
    if(!MakeNode(s,e)){
        return false;
    }
    InsertBefore(L,node,s);
    return true;
}


