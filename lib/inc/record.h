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

typedef struct{
	tag **tags;
	int num_of_collection;
	int num_of_child_is_alloc;
}Record;

typedef struct stPQAlloc {

	long lMemTotal; 		/*  Total size of objects managed in allocator  */
	long lCrc32Compressed; 	/*  CRC of the objects (if compression is used)	*/
	long idxFilePosition; 	/*  next available position in pseudo file		*/
	long idxOffset; 		/*  Offset to be added to the idx				*/
							/*  parameter returned by allocate				*/
							/*  Used to allow resetting allocators			*/
							/*  but return correct file offset				*/
} PQAlloc;

typedef struct{
	PQAlloc p;	// 集合分配器
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


#endif /* LIB_INC_RECORD_H_ */
