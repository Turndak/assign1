///////////////////////////////////////////
///										///
///		dll.c for CS201 assignment 0	///
///										///
///		Dakota Turner January 2017		///
///										///
///	 Creates, inserts & removes nodes   ///
///	 	from a doubly linked list		///
///	 Returns value at index and size 	///
///		of list							///
///										///
///////////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include "dll.h"

dll *newDLL(void (*d)(FILE *, void *)) //d is the display function
{
	dll *items = malloc(sizeof(dll));
    if (items == 0)
    	{
    		fprintf(stderr,"out of memory");
        	exit(-1);
        }
    items->head = 0;
    items->tail = 0;
    items->size = 0;
    items->display = d;
    return items;
}

void insertDLL(dll *items, int index, void *value) //inserts a new node into the linked list
{
	dllnode *new_node = malloc(sizeof(dllnode));	//creates and allocates new node
	new_node->value = value;
	new_node->next = NULL;
	new_node->prev = NULL;

	if (items->head == NULL || items->tail == NULL) //if no list exists
	{
			items->head = new_node;
			items->tail = new_node;
	}
	else if (items->head != NULL && index == 0) //inserts at beginning
	{
		items->head->prev = new_node;
		new_node->next = items->head;
		new_node->prev = NULL;
		items->head = new_node;	
	}
	else if(items->size == index)			//inserts at tail
	{
		new_node->next = NULL;
		new_node->prev = items->tail;
		items->tail->next = new_node;
		items->tail = new_node;				//update tail to the new node
	}
	else //if(index <= items->size)	//inserts elsewhere in the list
	{
  //   	dllnode *curr = malloc(sizeof(dll));
		// curr = items->head;
  //       for(int i = 0; i < index-1 ; ++i)
		// 	{
		// 		curr = curr->next;
		// 	}
  //      new_node->prev = curr;
  //      new_node->next = curr->next;
  //       //if there is another thing in the list
  //       if (curr->next)
  //          new_node->next->prev =new_node;
  //       curr->next =new_node;

		if(index <= items->size/2)
		{
			dllnode *curr_node, *after_node;
			curr_node = items->head;
			
			for(int i = 0; i < index-1 ; ++i)
			{
				curr_node = curr_node->next;
			}
			after_node = curr_node->next;//give after a value

			after_node->prev = new_node;
			new_node->next = after_node;
			curr_node->next = new_node;
			new_node->prev = curr_node;
		}
		else
		{
			dllnode *curr_node, *after_node;
			curr_node = items->tail;

			for(int i = 0; i < (items->size - index)-1; ++i)
			{
				// printf("%d\n", i);
				curr_node = curr_node->prev;
			}
			after_node = curr_node->prev;//give after a value
			curr_node->prev = new_node;
			after_node->next = new_node;
			new_node->prev = after_node;
			new_node->next = curr_node;			
		}
	}
	items->size++;
}

void *removeDLL(dll *items, int index)	//remove item at desired index
{
	dllnode *tmp, *nexti, *previ;		//store head in a temp

	if(items->head != NULL && index == 0)	//to remove head
	{
		tmp = items->head;
		nexti = items->head->next;
		items->head->prev = NULL;
		items->head->next = NULL;
		items->head = nexti;
		items->size--;
		return tmp->value;
		

	}
	else if (items->size-1 == index)	//removes tail/////////////////under construction//////////
	{
		tmp = items->tail;	//store tail value

		if(items->tail->prev != NULL)
		{
			previ = items->tail->prev;
			previ->next = NULL;
			items->tail = previ;
			items->size--;
		}
		else
		{
			items->tail = NULL;
			items->head = NULL;
			items->size--;
		}
		return tmp->value;
	}
	else //remove at given index
	{
		if(index <= items->size/2 && index>0)
		{
			dllnode *curr_node, *after_node;
			curr_node = items->head;
			for(int i = 0; i < index-1 ; ++i)
			{
				curr_node = curr_node->next;
			}
			after_node = curr_node->next->next;//give after a value
			tmp = curr_node->next;
			tmp->next = NULL;
			tmp->prev = NULL;
			after_node->prev = curr_node;
			curr_node->next = after_node;
			//return tmp->value;
			items->size--;
		}
		else if(index > items->size/2 && index < items->size)
		{
			dllnode *curr_node, *after_node;
			curr_node = items->tail;
			for(int i = 0; i < (items->size - index)-2; ++i)
			{
				curr_node = curr_node->prev;
				
			}
			after_node = curr_node->prev->prev;//give after a value
			tmp = curr_node->prev;
			tmp->next = NULL;
			tmp->prev = NULL;
			after_node->next = curr_node;
			curr_node->prev = after_node;	
	 		//return tmp->value;	
	 		items->size--;	
	  	}
	  	return tmp->value;
	 }
}

void unionDLL(dll *recipient, dll *donor) //combines two lists
{
	// if (donor->head == NULL)
	// {
	// 	free(donor);
	// }
	// else
	// {
	// 	recipient->tail->next = donor->head;	//sets tail pointer of recipient
	// 	donor->head->prev = recipient->tail;	//to head of donor
	// 	free(donor);							//this allows union in constatnt time	
	// }
	if (donor->head == NULL && recipient->head == NULL)
	{
		return;
	}
	else if(donor->head == NULL)
	{
		return;
	}
	else if (recipient->head == NULL && donor->head != NULL)
	{
		recipient->head = donor->head;
	}
	else
	{
		recipient->tail->next = donor->head;	//sets tail pointer of recipient	
		donor->head->prev = recipient->tail;	//to head of donor
	}
	
	recipient->tail = donor->tail;										//this allows union in constatnt time
	recipient->size += donor->size;
	donor->head = donor->tail = 0;
	donor->size = 0;
}												

void *getDLL(dll *items, int index) //returns the value at an index
{
	dllnode *tmp = items->head;
	int posi = 0;
	if(index == 0)
	{
		return tmp->value;
	}
	else if(index > (items->size)-1 || index < 0)
	{
		printf("OUT OF RANGE\n");
	}
	else{
		while(tmp != NULL && posi < index-1)
		{
			tmp = tmp->next;
			posi++;
		}
		return tmp->next->value;//display value at tmp
	}
	return tmp->value;
}

int sizeDLL(dll *items)	//returns size of the list
{
	// dllnode *tmp = items->head;	//tmp node
	// int count = 0;
	// while (tmp != NULL)			//counts the #of items in list
	// {
	// 	++count;
	// 	tmp=tmp->next;
	// }
	// return count;
	return items->size;

}

void displayDLL(FILE *fp, dll *items) //displays the list
{
	fprintf(fp,"[");
	dllnode *tmp = items->head;
	while (tmp != NULL)					//while not at the end of list
	{
		items -> display(fp, tmp->value);//display value at tmp
		if(tmp->next != NULL)			//as long as tmp's next pointer
		{								//doesn't point to null
			fprintf(fp,",");				
		}
		tmp = tmp->next;				//set tmp equal to tmp's next
	}
	fprintf(fp,"]");
}

