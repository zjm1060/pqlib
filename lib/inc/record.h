/*
 * record.h
 *
 *  Created on: 2017年10月10日
 *      Author: zjm09
 */

#ifndef LIB_INC_RECORD_H_
#define LIB_INC_RECORD_H_

#include <zlib.h>
#include "tags.h"

typedef struct MemNode MEMNODE;

struct MemNode {
	void * obj;
	size_t siz;
	long lpos;

	MEMNODE * pPrev;
	MEMNODE * pNext;
};

typedef struct stPQAlloc {
	MEMNODE * pmemFirst;
	MEMNODE * pmemLast;

	long lMemTotal; 		/*  Total size of objects managed in allocator  */
	long lCrc32Compressed; 	/*  CRC of the objects (if compression is used)	*/
	long idxFilePosition; 	/*  next available position in pseudo file		*/
	long idxOffset; 		/*  Offset to be added to the idx				*/
							/*  parameter returned by allocate				*/
							/*  Used to allow resetting allocators			*/
							/*  but return correct file offset				*/
} PQAlloc;

#define PQAlloc_Default	{NULL,NULL,0,0,0,0}

typedef struct{
//	PQAlloc p;	// 集合分配器
	c_collection collection;
	c_collection_element element[0];
}collection_t;

typedef struct{
	collection_t collection;
}Body_t;

typedef struct{
	c_record_mainheader header;
	Body_t body;
}Record_t;

collection_t *CreateCollection(PQAlloc *p,int count,size_t *size,long *idx);
collection_t *addCollection(PQAlloc *p,collection_t *c,GUID guid,int count);
UINT1 *addScalarUINT1(PQAlloc *p,collection_t *c,GUID guid,UINT1 value);
UINT2 *addScalarUINT2(PQAlloc *p,collection_t *c,GUID guid,UINT2 value);
UINT4 *addScalarUINT4(PQAlloc *p,collection_t *c,GUID guid,UINT4 value);
REAL4 *addScalarREAL4(PQAlloc *p,collection_t *c,GUID guid,REAL4 value);
REAL8 *addScalarREAL8(PQAlloc *p,collection_t *c,GUID guid,REAL8 value);
BOOL1 *addScalarBOOL1(PQAlloc *p,collection_t *c,GUID guid,BOOL1 value);
BOOL2 *addScalarBOOL2(PQAlloc *p,collection_t *c,GUID guid,BOOL2 value);
BOOL4 *addScalarBOOL4(PQAlloc *p,collection_t *c,GUID guid,BOOL4 value);
TIMESTAMPPQDIF *addScalarTimeStamp(PQAlloc *p, collection_t *c, GUID guid, TIMESTAMPPQDIF value);
GUID *addScalarGUID(PQAlloc *p, collection_t *c, GUID guid, GUID value);
UINT1 *addVectorUINT1(PQAlloc *p,collection_t *c,GUID guid,int count);
UINT2 *addVectorUINT2(PQAlloc *p,collection_t *c,GUID guid,int count);
UINT4 *addVectorUINT4(PQAlloc *p,collection_t *c,GUID guid,int count);
char *addVectorString(PQAlloc *p, collection_t *c, GUID guid, char *sz);
long saveRecord(int fd,PQAlloc *p,GUID guid,long idx,int haveNextRecord,int compression);

void DestroyList(PQAlloc *p);

#endif /* LIB_INC_RECORD_H_ */
