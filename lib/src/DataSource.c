/*
 * DataSource.c
 *
 *  Created on: 2017Äê10ÔÂ9ÈÕ
 *      Author: zjm09
 */

#include <time.h>
#include "../inc/name_id.h"
#include "../inc/DataSource.h"

static void DataSourceTagAdd(Record *c,tag *t)
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

Record *DataSourceCreate(GUID DsType,int numOfChannelDefs)
{
	Record *ds = calloc(1,sizeof(Record));
	struct timespec tv;

	clock_gettime(CLOCK_REALTIME,&tv);

	if(ds){
		DataSourceTagAdd(ds,createTagGUID(tagDataSourceTypeID,DsType));
		DataSourceTagAdd(ds,createTagTimestamp(tagEffective,tv));
		DataSourceTagAdd(ds,createTagString(tagNameDS,"test"));
		DataSourceTagAdd(ds,createTagCollection(tagChannelDefns,numOfChannelDefs));

		return ds;
	}

	return NULL;
}


void DataSourceFree(Record *ds)
{
	tag *root;
	for (int i = 0; i < ds->num_of_collection; ++i) {
		root = ds->tags[i];
		if(root->element.typeElement == ID_ELEMENT_TYPE_VECTOR){
			vectorFree(root);
		}else if(root->element.typeElement == ID_ELEMENT_TYPE_SCALAR){
			scalarFree(root);
		}else if(root->element.typeElement == ID_ELEMENT_TYPE_COLLECTION){
			collectionFree(root);
		}
	}

//	pq_free(ds->tags);
}

tag *OneChannelDef(quantity_measure_id_t MeasuredId,phase_id_t PhaseId,GUID QuanityTypeID,int numOfSeries)
{
	tag *chdef = createTagCollection(tagOneChannelDefn,4);
	collectionAdd(chdef,createTagScalar(tagQuantityMeasuredID,ID_PHYS_TYPE_INTEGER4,&MeasuredId));
	collectionAdd(chdef,createTagScalar(tagPhaseID,ID_PHYS_TYPE_INTEGER4,&PhaseId));
	collectionAdd(chdef,createTagGUID(tagQuantityTypeID,QuanityTypeID));
	collectionAdd(chdef,createTagCollection(tagSeriesDefns,numOfSeries));

	return chdef;
}

tag *OneSeriesDef(int QuantityUnitsID,GUID ValueTypeID,GUID QuantityCharacteristicID,int StorageMethodID)
{
	tag *series = createTagCollection(tagOneSeriesDefn,4);
	collectionAdd(series,createTagScalar(tagQuantityUnitsID,ID_PHYS_TYPE_INTEGER4,&QuantityUnitsID));
	collectionAdd(series,createTagGUID(tagValueTypeID,ValueTypeID));
	collectionAdd(series,createTagGUID(tagQuantityCharacteristicID,QuantityCharacteristicID));
	collectionAdd(series,createTagScalar(tagStorageMethodID,ID_PHYS_TYPE_INTEGER4,&StorageMethodID));

	return series;
}

void OneSeriesAttached(tag *OneChannel,tag *OneSeries,int index)
{
#if STATIC_COLLECTION_NUM
	if(index >= STATIC_COLLECTION_NUM){
		fprintf(stderr,"out of STATIC_COLLECTION_NUM");
		return;
	}
#endif
	tag *SeriesDefns = findTagInCollection(OneChannel,tagSeriesDefns);
	if(SeriesDefns)
		collectionAdd(SeriesDefns,OneSeries);
}

void OneChannelAttached(Record *ds,tag *OneChannelDef,int index)
{
	tag *ChannelDefns = NULL;

#if STATIC_COLLECTION_NUM
	if(index >= STATIC_COLLECTION_NUM){
		fprintf(stderr,"out of STATIC_COLLECTION_NUM");
		return;
	}
#endif

	for (int i = 0; i < ds->num_of_collection; ++i) {
		ChannelDefns = ds->tags[i];
		if(PQDIF_IsEqualGUID(ChannelDefns->element.tagElement,tagChannelDefns)){

			collectionAdd(ChannelDefns,OneChannelDef);

			return ;

		}
	}
//
//	ChannelDefns = ds->tags;
//	while(ChannelDefns) {
//		if(PQDIF_IsEqualGUID(ChannelDefns->element.tagElement,tagChannelDefns)){
//
//			collectionAdd(ChannelDefns,OneChannelDef);
//
//			return ;
//
//		}
//
//		ChannelDefns = ChannelDefns->next;
//	}
}

#if 1
int main(void)
{
	// create datasource by ID_DS_TYPE_MEASURE has 4 channeldefs
	Record *ds = DataSourceCreate(ID_DS_TYPE_MEASURE,1);

	// create oneChannelDefs by ID_QT_WAVEFORM has 1 seriesDefs
	tag *OneChannel= OneChannelDef(VOLTAGE,AN,ID_QT_WAVEFORM,1);
	collectionAdd(OneChannel,createTagString(tagChannelName,"test channle 1"));
	tag *OneSeries = OneSeriesDef(ID_QU_SECONDS,
			ID_SERIES_VALUE_TYPE_TIME,
			ID_QC_INSTANTANEOUS,
			SCALED|INCREMENT);

	// Attached OneSeries to OneChannel->SeriesDefs
	OneSeriesAttached(OneChannel,OneSeries,0);

	OneSeries = OneSeriesDef(ID_QU_VOLTS,
			ID_SERIES_VALUE_TYPE_VAL,
			ID_QC_INSTANTANEOUS,
			ID_SERIES_METHOD_SCALED|ID_SERIES_METHOD_VALUES);
	OneSeriesAttached(OneChannel,OneSeries,1);

	// Attached OneChannel to ds->channelDefs
	OneChannelAttached(ds,OneChannel,0);


	DataSourceFree(ds);
}
#endif
