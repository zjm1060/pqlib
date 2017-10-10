/*
 * container.c
 *
 *  Created on: 2017Äê10ÔÂ9ÈÕ
 *      Author: zjm09
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/container.h"

static void ContainerTagAdd(Container *c,tag *t)
{
	if(c->tags == NULL){
		c->tags = t;
	}else{
		t->next = c->tags;
		c->tags = t;
	}

	c->num_of_tags ++;
}



Container *ContainerCreate(void)
{
	Container *c = calloc(1,sizeof(Container));
	struct timespec tv;

	clock_gettime(CLOCK_REALTIME,&tv);

	if(c){
		ContainerTagAdd(c,createTagString(tagFileName,"pqdif"));
		ContainerTagAdd(c,createTagVector(tagVersionInfo,ID_PHYS_TYPE_INTEGER4,(int[4]){1,5,1,0},4));
		ContainerTagAdd(c,createTagTimestamp(tagCreation,tv));
		ContainerTagAdd(c,createTagString(tagLanguage,"English"));

		return c;
	}

	return NULL;
}

void ContainerFree(Container *c)
{
	tag *root = c->tags;
	tag *next;

	while(root){
		next = root->next;
		if(root->element_type == ID_ELEMENT_TYPE_VECTOR){
			vectorFree(root);
		}else if(root->element_type == ID_ELEMENT_TYPE_SCALAR){
			scalarFree(root);
		}else if(root->element_type == ID_ELEMENT_TYPE_COLLECTION){
			collectionFree(root);
		}
		root = next;
	}
}
