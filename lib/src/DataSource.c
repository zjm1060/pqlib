/*
 * DataSource.c
 *
 *  Created on: 2017Äê10ÔÂ9ÈÕ
 *      Author: zjm09
 */

#include <time.h>
#include "../inc/name_id.h"
#include "../inc/DataSource.h"

static void DataSourceTagAdd(DataSource *c,tag *t)
{
	if(c->tags == NULL){
		c->tags = t;
	}else{
		t->next = c->tags;
		c->tags = t;
	}

	c->num_of_tags ++;
}

DataSource *DataSourceCreate(GUID DsType,int numOfChannelDefs)
{
	DataSource *ds = calloc(1,sizeof(DataSource));
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


void DataSourceFree(DataSource *ds)
{
	tag *root = ds->tags;
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

tag *OneChannelDef(int MeasuredId,int PhaseId,GUID QuanityTypeID,int numOfSeries)
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

void OneChannelAttached(DataSource *ds,tag *OneChannelDef,int index)
{
	tag *ChannelDefns = NULL;

#if STATIC_COLLECTION_NUM
	if(index >= STATIC_COLLECTION_NUM){
		fprintf(stderr,"out of STATIC_COLLECTION_NUM");
		return;
	}
#endif

	ChannelDefns = ds->tags;
	while(ChannelDefns) {
		if(PQDIF_IsEqualGUID(ChannelDefns->guid,tagChannelDefns)){

			collectionAdd(ChannelDefns,OneChannelDef);

			return ;

		}

		ChannelDefns = ChannelDefns->next;
	}
}

#if 1
int main(void)
{
	// create datasource by ID_DS_TYPE_MEASURE has 4 channeldefs
	DataSource *ds = DataSourceCreate(ID_DS_TYPE_MEASURE,1);

	// create oneChannelDefs by ID_QT_WAVEFORM has 1 seriesDefs
	tag *OneChannel= OneChannelDef(ID_QM_VOLTAGE,ID_PHASE_AN,ID_QT_WAVEFORM,1);
	collectionAdd(OneChannel,createTagString(tagChannelName,"test channle 1"));
	tag *OneSeries = OneSeriesDef(ID_QU_SECONDS,
			ID_SERIES_VALUE_TYPE_TIME,
			ID_QC_INSTANTANEOUS,
			ID_SERIES_METHOD_SCALED|ID_SERIES_METHOD_INCREMENT);

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
