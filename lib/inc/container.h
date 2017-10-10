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

#include "record.h"



Record *ContainerCreate(void);
void ContainerFree(Record *c);

#endif /* LIB_INC_CONTAINER_H_ */
