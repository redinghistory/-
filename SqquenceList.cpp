#include<iostream>
#include<cstdlib>
using namespace std;

/**
 * shunxu表的动态分配存储结构
 */
#define LIST_INIT_SIZE 100  //初始化长度
#define LISTINREMENT 10     //长度增量
typedef int ElemType;//定义元素类型，//在实际考试中可以不写
typedef struct {
    ElemType *elem; //存储空间基址
    int length; //当前长度
    int listsize;   //当前分配的存储容量，以sizeof(ElemType)为单位
}SqList;


/**
 * 构造一个空的线性表，传入一个线性表类型的引用，对其进行初始化
 * @param L 线性表引用
 * @return 创建成功返回true
 */
bool InitList(SqList &L){
    L.elem=(ElemType*)malloc(LISTINREMENT*sizeof(ElemType)); //为线性表分配数据空间
    if(!L.elem){
        exit(-2); //内存分配出现错误
    }
    L.length=0; //刚开始线性表元素为空，长度为零
    L.listsize=LIST_INIT_SIZE; //设置初始化的线性表容量

    return true;
}

/**
 * 将元素e插入到顺序表L的指定位序i中
 * @param L 顺序表
 * @param i 指定的位序
 * @param e 给定的要插入的元素
 * @return 插入成功返回true
 */
bool ListInsert(SqList &L,int i,ElemType e){
    if(i<1||i>L.length+1){ //要插入的位置不合法
        return true;
    }
    if(L.length>=L.listsize){//当前存储空间已满，增加分配
        ElemType *newbase=(ElemType*)realloc(L.elem,(L.listsize+LISTINREMENT)*sizeof(ElemType));
        if(!newbase){
            exit(-2); //分配存储空间出错
        }
        L.elem=newbase; //新基址
        L.listsize+=LISTINREMENT;   //增加容量
    }


    //插入

    for(int j=L.length-1;j>=i-1;j--){   //从结尾到i，每个数据元素都向后移动一位
        L.elem[j+1]=L.elem[j];
    }

    L.elem[i-1]=e;      //插入
    L.length++;     //长度+1

    return true;
}
/**
 * 删除顺序表中指定位序的元素，并带回被删除元素的值
 * @param L 顺序表
 * @param i 指定 的位序
 * @param e 将被删除元素的值带回
 * @return
 */
bool ListDelete(SqList &L,int i,ElemType &e){

    if(i<1||i>L.length){//要删除的位序不合法
        return false;
         }
    for(int j=i-1;j<L.length-1;j++){  //从第i+1个元素开始到结尾，全部向前移动一位
        L.elem[j]=L.elem[j+1];
    }
    L.length--; //长度-1

    return true;


}

/**
 * 比较函数，判断两个数据元素是否相等
 * @param a
 * @param b
 * @return
 */
bool equal(ElemType a,ElemType b){
   return a==b?true:false;
}
/**
 * 在顺序表L中找出第一个与元素e满足compare函数关系的元素的位序
 * 若找到则返回元素位序，没找到就返回0
 * @param L
 * @param e
 * @param compare
 * @return
 */
int LocatElem(SqList &L,ElemType e,bool (*compare)(ElemType,ElemType)){
    int i=1;
    while(i<=L.length&&!(*compare)(e,L.elem[i-1])){
        i++;
    }
    if(i<=L.length){
        return i;
    }else{
        return 0;
    }
}
/**
 * 销毁顺序表
 * @param L
 * @return
 */
bool DestoryList(SqList &L){
    free(L.elem); //释放存储空间
    L.length=0; //长度设置为0
    L.listsize=0;   //容量设置为0
    return  true;
}
/**
 * 清空顺序表
 * @param L
 * @return
 */
bool ClearList(SqList &L){
    L.length=0;
    return true;
}
/**
 * 判单顺序表是否为空，若为空返回true,非空返回false
 * @param L
 * @return
 */
bool Empty(SqList &L){
    if(L.length==0){
        return true;
    }else{
        return false;
    }
}
/**
 * 返回顺序表长度
 * @param L
 * @return
 */
int Length(SqList &L){
    return L.length;
}
/**
 * 返回顺序表中第i个元素的值给e
 * @param L
 * @param i
 * @param e
 * @return
 */
bool GetElem(SqList &L,int i,ElemType &e){
    if(i<1||i>L.length){
        return false;
    }else{
        e=L.elem[i-1];
        return true;
    }
}
/**
 * 前驱
 * @param L 顺序表
 * @param cur 元素位序
 * @param e 带回前驱的值
 * @return
 */
bool Prior(SqList &L,int cur,ElemType &e){
    if(cur<2||cur>L.length){    //第一个元素没前驱
        return false;
    }
    e=L.elem[cur-2];
    return true;
}
/**
 * 后继
 * @param L 顺序表
 * @param cur 元素位序
 * @param e 带回后继的值
 * @return
 */
bool Next(SqList &L,int cur,ElemType &e){
    if(cur<1||cur>=L.length){   //最后一个元素没后继
        return false;
    }
    e=L.elem[cur];
    return true;
}

/**
 * 遍历顺序表
 * 对顺序表每一个元素调用函数visit,一旦调用失败，返回false
 * @param L
 * @param visit
 * @return
 */
bool Traverse(SqList &L,bool (*visit)(ElemType e)){
    for(int i=0;i<L.length;i++){
        if(!visit(L.elem[i])){
            return false;
        }
    }
    return true;
}

/**
 * 将所有属于b，但是不属于a的元素添加到顺序表a中
 * @param a
 * @param b
 */
void Union(SqList &a,SqList &b){
    ElemType temp;
    ElemType &e=temp;
    for(int i=1;i<b.length;i++){
        GetElem(b,i,e);
        if(!LocatElem(a,e,equal)){
            ListInsert(a,++a.length,e);
        }
    }
}

/**
 * 顺序表a,b中的元素按值非递减有序，将a和b合并到c，使得c也按值非递减有序
 * @param a
 * @param b
 * @param c
 */
void MergeList(SqList &a,SqList &b,SqList &c){
    InitList(c);
    int i=1,j=1,k=0;
    ElemType e1,e2;
    while((i<=a.length)&&(j<=b.length)){
        GetElem(a,i,e1);
        GetElem(b,i,e2);
        if(e1<=e2){
            ListInsert(c,++k,e1);
        }else{
            ListInsert(c,++k,e2);
        }
    }

    while(i<=a.length){
        GetElem(a,i,e1);
        ListInsert(c,++k,e1);
    }

    while(j<=b.length){
        GetElem(b,j,e2);
        ListInsert(c,++k,e2);
    }
}

