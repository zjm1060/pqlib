/*
 * DataSource.h
 *
 *  Created on: 2017Äê10ÔÂ9ÈÕ
 *      Author: zjm09
 */

#ifndef LIB_INC_DATASOURCE_H_
#define LIB_INC_DATASOURCE_H_

#include "tags.h"
#include "container.h"

//typedef struct{
//	tag **tags;
//	int num_of_collection;
//	int num_of_child_is_alloc;
//}DataSource;

Record *DataSourceCreate(GUID DsType,int numOfChannelDefs);
void DataSourceFree(Record *ds);
tag *OneChannelDef(quantity_measure_id_t MeasuredId,phase_id_t PhaseId,GUID QuanityTypeID,int numOfSeries);
tag *OneSeriesDef(int QuantityUnitsID,GUID ValueTypeID,GUID QuantityCharacteristicID,int StorageMethodID);
void OneSeriesAttached(tag *OneChannel,tag *OneSeries,int index);
void OneChannelAttached(Record *ds,tag *OneChannelDef,int index);

#endif /* LIB_INC_DATASOURCE_H_ */
