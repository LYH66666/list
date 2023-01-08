#include<stdio.h>
#include<stdlib.h>

#ifndef LIST_H
#define LIST_H

typedef struct LIST List;

struct LIST{
	struct LIST_PROP *prop; //属性
	struct LIST* (*add)(struct LIST*,void*); //新增节点，返回表头
	struct LIST* (*del)(struct LIST*,int,void* (*free_data)(void*)); //删除节点，返回表头，参数为自定义的释放数据函数
	struct LIST* (*find)(struct LIST*,int); //查找节点，返回节点，参数为序列号
	struct LIST* (*set)(struct LIST*,void*,int); //更改节点，返回表头，参数为新数据，序列号
	struct LIST* (*insert)(struct LIST *,void*,int); //前项插入节点，返回表头，参数为数据和序列号
	void* (*get_data)(struct LIST*); //获取节点数据，返回数据的地址
	void (*show)(struct LIST*,void (*show_data)(void*)); //输出表所有节点数据，参数为自定义的输出数据的自定义函数
	int (*len)(struct LIST*); //获取表长度	
};

List* new_List(); //实例化List
void* free_List(List *self,void* (*free_data)(void*)); //析构List

#endif //LIST_H
