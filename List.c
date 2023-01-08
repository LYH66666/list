#include<stdio.h>
#include<stdlib.h>
#include"List.h"

typedef struct LIST_PROP List_prop;

struct LIST_PROP{
	void *data;
	int list_len;
	struct LIST *next;
	struct LIST *prev;
};


static List_prop* new_List_prop();
static void* free_List_prop(List_prop *self,void* (*free_data)(void*));


static List* add(List* self,void *data);
static List* del(List* self,int num,void* (*free_data)(void*));
static List* find(List* self,int num);
static List* set(List* self,void *data,int num);
static List* insert(List* self,void *data,int num);
static void* get_data(List* self);
static void show(List *self,void (*show_data)(void*));
static int len(List *self);


/*-----------------------------------------------------------------------------*/

List* new_List()
{
	List *p;
	p=(List*)malloc(sizeof(List));
	
	p->prop=new_List_prop();
	p->add=add;
	p->del=del;
	p->find=find;
	p->set=set;
	p->insert=insert;
	p->get_data=get_data;
	p->show=show;
	p->len=len;
	
	return p;
}

/*-----------------------------------------------------------------------------*/

void* free_List(List *self,void* (*free_data)(void*))
{
	if(self==NULL)
	    return self;
	List *p=self;
	List *p_next=p->prop->next;
	while(p_next!=NULL)
	{
		if(p==self)
			p->prop=free_List_prop(p->prop,NULL);
		else
			p->prop=free_List_prop(p->prop,free_data);
		free(p);
		p=p_next;
		p_next=p_next->prop->next;
	}
	if(p==self)
		p->prop=free_List_prop(p->prop,NULL);
	else
		p->prop=free_List_prop(p->prop,free_data);
	free(p);
	return NULL;
}

/*-----------------------------------------------------------------------------*/

static List_prop* new_List_prop()
{
	List_prop *p;
	p=(List_prop*)malloc(sizeof(List_prop));
	
	p->data=NULL;
	p->next=NULL;
	p->prev=NULL;
	p->list_len=0;
	
	return p;
}

/*-----------------------------------------------------------------------------*/

static void* free_List_prop(List_prop *self,void* (*free_data)(void*))
{
	if(free_data!=NULL)
		self->data=free_data(self->data);
	free(self);
	
	return NULL;
}

/*-----------------------------------------------------------------------------*/

static List* add(List* self,void *data)
{
	if(self==NULL)
	    return self;
	
	List *new_data=(List*)malloc(sizeof(List));
	new_data->prop=new_List_prop();
	List *last_p=self->prop->prev;
	
	new_data->add=NULL;
	new_data->del=NULL;
	new_data->find=NULL;
	new_data->set=NULL;
	new_data->insert=NULL;
	new_data->get_data=get_data;
	new_data->show=NULL;
	new_data->len=NULL;
	
	self->prop->prev=new_data;
	if(last_p==NULL)
	{
		self->prop->next=new_data;
		new_data->prop->prev=self;
	}
	else
	{
		last_p->prop->next=new_data;
		new_data->prop->prev=last_p;	
	}
	
	new_data->prop->data=data;
	new_data->prop->list_len=0;
	
	self->prop->list_len++;
	return self;
}

/*-----------------------------------------------------------------------------*/

static List* del(List* self,int num,void* (*free_data)(void*))
{
	if(self==NULL||self->len==0)
	    return self;
	
	List *p=self->prop->next;
	int i;
	
	if(num<0||num>self->prop->list_len-1)
	{
		return self;
	}
	for(i=0;i<num;i++)
	{
		p=p->prop->next;
	}
	
	if(p->prop->next!=NULL)
	{
		p->prop->prev->prop->next=p->prop->next;
		p->prop->next->prop->prev=p->prop->prev;
	}
	else
	{
		self->prop->prev=p->prop->prev;
		if(self->prop->prev==self)
			self->prop->prev=NULL;
		p->prop->prev->prop->next=NULL; 
	}
	p->prop=free_List_prop(p->prop,free_data);
	free(p);
	
	self->prop->list_len--;
	return self;
}

/*-----------------------------------------------------------------------------*/

static List* find(List* self,int num)
{
	if(self==NULL||self->len==0)
	    return self;
	    
	List *p=self->prop->next;
	int i;
	
	if(num<0||num>self->prop->list_len-1)
	{
		return self;
	}
	for(i=0;i<num;i++)
	{
		p=p->prop->next;
	}
	
	return p;	
}

/*-----------------------------------------------------------------------------*/

static List* set(List* self,void *data,int num)
{
	if(self==NULL||self->len==0)
	    return self;
	    
	List *p=self->prop->next;
	int i;
	
	if(num<0||num>self->prop->list_len-1)
	{
		return self;
	}
	for(i=0;i<num;i++)
	{
		p=p->prop->next;
	}
	
	p->prop->data=data;
	
	return self;
}

/*-----------------------------------------------------------------------------*/

static List* insert(List* self,void *data,int num)
{
	if(self==NULL)
	    return self;
	    
	List *p=self;
	int i;
	
	if(num<0||num>self->prop->list_len-1)
	{
		return self;
	}
	
	List *new_data=(List*)malloc(sizeof(List));
	new_data->prop=new_List_prop();

	for(i=0;i<num;i++)
	{
		p=p->prop->next;
	}
	
	List *p_next=p->prop->next;
	if(p_next!=NULL)
	{
		
		p_next->prop->prev=new_data;
		new_data->prop->next=p_next;
		p->prop->next=new_data;
		new_data->prop->prev=p;
	}
	else
	{
		p->prop->next=new_data;
		new_data->prop->prev=p;
		new_data->prop->next=NULL;
		self->prop->prev=new_data;
	}
	
	new_data->add=NULL;
	new_data->del=NULL;
	new_data->find=NULL;
	new_data->set=NULL;
	new_data->insert=NULL;
	new_data->get_data=get_data;
	new_data->show=NULL;
	new_data->len=NULL;
	
	new_data->prop->data=data;
	new_data->prop->list_len=0;
	
	self->prop->list_len++;
	return self;
}

/*-----------------------------------------------------------------------------*/

static void* get_data(List* self)
{
	if(self==NULL)
	    return NULL;    
	return self->prop->data;
}

/*-----------------------------------------------------------------------------*/

static void show(List *self,void (*show_data)(void *data))
{
	if(self==NULL)
	    return;  
	List *p=self->prop->next;
	if(p==NULL)
		printf("None!\n");
	while(p!=NULL)
	{
		show_data(p->prop->data);
		p=p->prop->next; 
	}
}

/*-----------------------------------------------------------------------------*/


static int len(List *self)
{
	if(self==NULL)
	    return 0; 
	return self->prop->list_len;
}

/*-----------------------------------------------------------------------------*/
