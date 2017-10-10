/*
 * container.h
 *
 *  Created on: 2017Äê10ÔÂ9ÈÕ
 *      Author: zjm09
 */

#ifndef LIB_INC_CONTAINER_H_
#define LIB_INC_CONTAINER_H_

//#include "../inc/pqdif_ph.h"
//#include "../inc/pqdif_id.h"
//#include "../inc/pqdif_lg.h"

#include "../inc/tags.h"

typedef struct{
	tag *tags;
	int num_of_tags;

}Container;

Container *ContainerCreate(void);
void ContainerFree(Container *c);

#endif /* LIB_INC_CONTAINER_H_ */
