/*
 * test.c
 *
 *  Created on: 2017Äê10ÔÂ11ÈÕ
 *      Author: zjm09
 */

#include <fcntl.h>
#include <assert.h>
#include <math.h>

#include "../lib/inc/record.h"

const   double PI = 3.141592654;

void randomWave(REAL4 *paData,int nPnt)
{
	double  random;
	for (long i = 0; i < nPnt; i++) {
		random = (((double) rand()) * 100.0) / (double) RAND_MAX;
		paData[i] = 1200.0 * sin(16.0 * PI * (double) i / (double) nPnt)
				+ random;
	}

}

int main(void)
{
	size_t size;
	long idx;
	PQAlloc p = PQAlloc_Default;
//	PQAlloc datasource = PQAlloc_Default;
//	c_record_mainheader header;
	int fd;
	long idxFilePosition;

	printf("element size is: %d\n",sizeof(c_collection_element));
	printf("collection size is: %d\n",sizeof(c_collection));

	fflush(stdout);

	collection_t *c = CreateCollection(&p,5,&size,&idx);

	addVectorString(&p,c,tagFileName,"tets.pqd");
	addScalarTimeStamp(&p,c,tagCreation,(TIMESTAMPPQDIF){231310,10000.0});
	addScalarUINT4(&p,c,tagCompressionAlgorithmID,ID_COMP_ALG_ZLIB);
	addScalarUINT4(&p,c,tagCompressionStyleID,ID_COMP_STYLE_RECORDLEVEL);
	UINT4 *dp = addVectorUINT4(&p,c,tagVersionInfo,4);
	dp[0] = 1;
	dp[1] = 5;
	dp[2] = 1;
	dp[3] = 5;
	{
		fd = open("test.pqd",O_RDWR | O_CREAT | O_BINARY | O_TRUNC);
		if(fd != -1){
//			write(fd,&header,sizeof(header));
//			writeList(fd,&p,ID_COMP_ALG_NONE);

		}
	}

	idxFilePosition = saveRecord(fd,&p,tagContainer,0,1,ID_COMP_ALG_NONE);

	DestroyList(&p);

	c = CreateCollection(&p,4,&size,&idx);
	assert(addScalarGUID(&p,c,tagDataSourceTypeID,ID_DS_TYPE_MEASURE) != NULL);
	assert(addVectorString(&p,c,tagNameDS,"PQDIF Convert") != NULL);
	addScalarTimeStamp(&p,c,tagEffective,(TIMESTAMPPQDIF){231310,10000.0});

	collection_t *ChannelDefns = addCollection(&p,c,tagChannelDefns,1);assert(ChannelDefns != NULL);
	collection_t *OneChannelDefn = addCollection(&p,ChannelDefns,tagOneChannelDefn,5);assert(OneChannelDefn != NULL);
			addVectorString(&p,OneChannelDefn,tagChannelName,"Phase AN Voltage");
			addScalarUINT4(&p,OneChannelDefn,tagPhaseID,AN);
			addScalarUINT4(&p,OneChannelDefn,tagQuantityMeasuredID,VOLTAGE);
			addScalarGUID(&p,OneChannelDefn,tagQuantityTypeID,ID_QT_WAVEFORM);
			collection_t *SeriesDefns = addCollection(&p,OneChannelDefn,tagSeriesDefns,3);
			collection_t *OneSeriesDefn = addCollection(&p,SeriesDefns,tagOneSeriesDefn,4);
					addScalarUINT4(&p,OneSeriesDefn,tagQuantityUnitsID,SECONDS);
					addScalarUINT4(&p,OneSeriesDefn,tagStorageMethodID,INCREMENT);
					addScalarGUID(&p,OneSeriesDefn,tagQuantityCharacteristicID,ID_QC_RMS);
					addScalarGUID(&p,OneSeriesDefn,tagValueTypeID,ID_SERIES_VALUE_TYPE_TIME);
			OneSeriesDefn = addCollection(&p,SeriesDefns,tagOneSeriesDefn,4);
					addScalarUINT4(&p,OneSeriesDefn,tagQuantityUnitsID,VOLTS);
					addScalarUINT4(&p,OneSeriesDefn,tagStorageMethodID,VALUES);
					addScalarGUID(&p,OneSeriesDefn,tagQuantityCharacteristicID,ID_QC_INSTANTANEOUS);
					addScalarGUID(&p,OneSeriesDefn,tagValueTypeID,ID_SERIES_VALUE_TYPE_INST);
//			OneSeriesDefn = addCollection(&p,SeriesDefns,tagOneSeriesDefn,4);
//					addScalarUINT4(&p,OneSeriesDefn,tagQuantityUnitsID,VOLTS);
//					addScalarUINT4(&p,OneSeriesDefn,tagStorageMethodID,VALUES);
//					addScalarGUID(&p,OneSeriesDefn,tagQuantityCharacteristicID,ID_QC_RMS);
//					addScalarGUID(&p,OneSeriesDefn,tagValueTypeID,ID_SERIES_VALUE_TYPE_MAX);


	idxFilePosition = saveRecord(fd,&p,tagRecDataSource,idxFilePosition,1,ID_COMP_ALG_ZLIB);
	DestroyList(&p);

	c = CreateCollection(&p,6,&size,&idx);
	addVectorString(&p,c,tagObservationName,"obs");
	addScalarTimeStamp(&p,c,tagTimeCreate,(TIMESTAMPPQDIF){231310,10000.0});
	addScalarTimeStamp(&p,c,tagTimeStart,(TIMESTAMPPQDIF){231310,10000.0});
	addScalarUINT4(&p,c,tagTriggerMethodID,ID_TRIGGER_METH_CHANNEL);
	UINT4 *ChannelTriggerIdx = addVectorUINT4(&p,c,tagChannelTriggerIdx,1);
	*ChannelTriggerIdx = 0;
	collection_t *ChannelInstances = addCollection(&p,c,tagChannelInstances,1);
		collection_t *OneChannelInst = addCollection(&p,ChannelInstances,tagOneChannelInst,2);
			addScalarUINT4(&p,OneChannelInst,tagChannelDefnIdx,0);
			collection_t *SeriesInstances = addCollection(&p,OneChannelInst,tagSeriesInstances,2);
				collection_t *OneSeriesInstance = addCollection(&p,SeriesInstances,tagOneSeriesInstance,1);
					REAL4 *SeriesValues = addVectorREAL4(&p,OneSeriesInstance,tagSeriesValues,3);
					SeriesValues[0] = 1;
					SeriesValues[1] = 10240;
					SeriesValues[2] = 0.0125;
				OneSeriesInstance = addCollection(&p,SeriesInstances,tagOneSeriesInstance,1);
					SeriesValues = addVectorREAL4(&p,OneSeriesInstance,tagSeriesValues,10240);
					randomWave(SeriesValues,10240);

	idxFilePosition = saveRecord(fd,&p,tagRecObservation,idxFilePosition,0,ID_COMP_ALG_ZLIB);
	DestroyList(&p);

	close(fd);
}
