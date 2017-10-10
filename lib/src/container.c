/*
 * container.c
 *
 *  Created on: 2017Äê10ÔÂ9ÈÕ
 *      Author: zjm09
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../inc/tags.h"
#include "../inc/container.h"

static void ContainerTagAdd(Record *c,tag *t)
{
	for (int i = 0; i < c->num_of_child_is_alloc; ++i) {
		if(c->tags[i] == NULL){
			c->tags[i] = t;
			c->num_of_collection ++;
			return;
		}
	}

	c->num_of_child_is_alloc ++;
	c->tags = realloc(c->tags,sizeof(tag*)*c->num_of_child_is_alloc);

	c->tags[c->num_of_child_is_alloc-1] = t;
	c->num_of_collection ++;
}



Record *ContainerCreate(void)
{
	Record *c = calloc(1,sizeof(Record));
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

void ContainerFree(Record *c)
{
	tag *root;

	for (int i = 0; i < c->num_of_collection; ++i) {
		root = c->tags[i];
		if(root->element.typeElement == ID_ELEMENT_TYPE_VECTOR){
			vectorFree(root);
		}else if(root->element.typeElement == ID_ELEMENT_TYPE_SCALAR){
			scalarFree(root);
		}else if(root->element.typeElement == ID_ELEMENT_TYPE_COLLECTION){
			collectionFree(root);
		}
	}
}

void ContainerSync(int fd,Record *c)
{
	struct c_record_mainheader header;
	struct c_collection body;
	struct c_collection_element element;

	body.count = c->num_of_collection;

	header.guidRecordSignature = guidRecordSignaturePQDIF;
	header.tagRecordType = tagContainer;
	header.sizeHeader = 64;
	header.sizeData = 0;
	header.linkNextRecord = header.sizeHeader + header.sizeData;
}
