/*
 * record.h
 *
 *  Created on: 2017Äê10ÔÂ10ÈÕ
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

typedef struct c_record_mainheader c_record_mainheader;
typedef struct c_collection c_collection;
typedef struct c_collection_element c_collection_element;

#endif /* LIB_INC_RECORD_H_ */
