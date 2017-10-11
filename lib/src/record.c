/*
 * record.c
 *
 *  Created on: 2017Äê10ÔÂ10ÈÕ
 *      Author: zjm09
 */
#include <fcntl.h>
#include <assert.h>
#include "../inc/record.h"

#include "../inc/pqdif_id.h"
#include "../inc/pqdif_lg.h"

#if DEBUG

int allocCount;

#define DEBUG_ITME(tags)	{.name = #tags,.guid = &tags}

	struct {
		const char *name;
		const GUID *guid;
	}DebugList[] = {
			DEBUG_ITME(tagContainer),
			DEBUG_ITME(tagRecDataSource),
			DEBUG_ITME(tagRecMonitorSettings),
			DEBUG_ITME(tagRecObservation),
			DEBUG_ITME(tagVersionInfo),
			DEBUG_ITME(tagFileName),
			DEBUG_ITME(tagCreation),
			DEBUG_ITME(tagLastSaved),
			DEBUG_ITME(tagTimesSaved),
			DEBUG_ITME(tagLanguage),
			DEBUG_ITME(tagTitle),
			DEBUG_ITME(tagSubject),
			DEBUG_ITME(tagAuthor),
			DEBUG_ITME(tagKeywords),
			DEBUG_ITME(tagComments),
			DEBUG_ITME(tagLastSavedBy),
			DEBUG_ITME(tagApplication),
			DEBUG_ITME(tagSecurity),
			DEBUG_ITME(tagOwner),
			DEBUG_ITME(tagCopyright),
			DEBUG_ITME(tagTrademarks),
			DEBUG_ITME(tagNotes),
			DEBUG_ITME(tagCompressionStyleID),
			DEBUG_ITME(tagCompressionAlgorithmID),
			DEBUG_ITME(tagCompressionChecksum),
			DEBUG_ITME(tagName),
			DEBUG_ITME(tagAddress1),
			DEBUG_ITME(tagAddress2),
			DEBUG_ITME(tagCity),
			DEBUG_ITME(tagState),
			DEBUG_ITME(tagPostalCode),
			DEBUG_ITME(tagCountry),
			DEBUG_ITME(tagPhoneVoice),
			DEBUG_ITME(tagPhoneFAX),
			DEBUG_ITME(tagEMail),
			DEBUG_ITME(tagDataSourceTypeID),
			DEBUG_ITME(tagVendorID),
			DEBUG_ITME(tagEquipmentID),
			DEBUG_ITME(tagCustomSourceInfo),
			DEBUG_ITME(tagSerialNumberDS),
			DEBUG_ITME(tagVersionDS),
			DEBUG_ITME(tagNameDS),
			DEBUG_ITME(tagOwnerDS),
			DEBUG_ITME(tagLocationDS),
			DEBUG_ITME(tagTimeZoneDS),
			DEBUG_ITME(tagCoordinatesDS),
			DEBUG_ITME(tagChannelDefns),
			DEBUG_ITME(tagInstrumentTypeID),
			DEBUG_ITME(tagInstrumentModelName),
			DEBUG_ITME(tagInstrumentModelNumber),
			DEBUG_ITME(tagOneChannelDefn),
			DEBUG_ITME(tagChannelName),
			DEBUG_ITME(tagPhaseID),
			DEBUG_ITME(tagOtherChannelIdentifier),
			DEBUG_ITME(tagGroupName),
			DEBUG_ITME(tagQuantityTypeID),
			DEBUG_ITME(tagQuantityMeasuredID),
			DEBUG_ITME(tagPhysicalChannel),
			DEBUG_ITME(tagQuantityName),
			DEBUG_ITME(tagPrimarySeriesIdx),
			DEBUG_ITME(tagSeriesDefns),
			DEBUG_ITME(tagOneSeriesDefn),
			DEBUG_ITME(tagValueTypeID),
			DEBUG_ITME(tagQuantityUnitsID),
			DEBUG_ITME(tagQuantityCharacteristicID),
			DEBUG_ITME(tagQuantitySignificantDigitsID),
			DEBUG_ITME(tagQuantityResolutionID),
			DEBUG_ITME(tagStorageMethodID),
			DEBUG_ITME(tagValueTypeName),
			DEBUG_ITME(tagHintGreekPrefixID),
			DEBUG_ITME(tagHintPreferredUnitsID),
			DEBUG_ITME(tagHintDefaultDisplayID),
			DEBUG_ITME(tagProbInterval),
			DEBUG_ITME(tagProbPercentile),
			DEBUG_ITME(tagSeriesNominalQuantity),
			DEBUG_ITME(tagEffective),
			DEBUG_ITME(tagTimeInstalled),
			DEBUG_ITME(tagTimeRemoved),
			DEBUG_ITME(tagUseCalibration),
			DEBUG_ITME(tagUseTransducer),
			DEBUG_ITME(tagChannelSettingsArray),
			DEBUG_ITME(tagNominalFrequency),
			DEBUG_ITME(tagSettingPhysicalConnection),
			DEBUG_ITME(tagOneChannelSetting),
			DEBUG_ITME(tagChannelDefnIdx),
			DEBUG_ITME(tagTriggerTypeID),
			DEBUG_ITME(tagFullScale),
			DEBUG_ITME(tagNoiseFloor),
			DEBUG_ITME(tagTriggerShapeParam),
			DEBUG_ITME(tagXDTransformerTypeID),
			DEBUG_ITME(tagXDSystemSideRatio),
			DEBUG_ITME(tagXDMonitorSideRatio),
			DEBUG_ITME(tagXDFrequencyResponse),
			DEBUG_ITME(tagCalTimeSkew),
			DEBUG_ITME(tagCalOffset),
			DEBUG_ITME(tagCalRatio),
			DEBUG_ITME(tagCalMustUseARCal),
			DEBUG_ITME(tagCalApplied),
			DEBUG_ITME(tagCalRecorded),
			DEBUG_ITME(tagTriggerHighHigh),
			DEBUG_ITME(tagTriggerHigh),
			DEBUG_ITME(tagTriggerLow),
			DEBUG_ITME(tagTriggerLowLow),
			DEBUG_ITME(tagTriggerDeadBand),
			DEBUG_ITME(tagTriggerRate),
			DEBUG_ITME(tagObservationName),
			DEBUG_ITME(tagTimeCreate),
			DEBUG_ITME(tagTimeStart),
			DEBUG_ITME(tagTriggerMethodID),
			DEBUG_ITME(tagTimeTriggered),
			DEBUG_ITME(tagChannelTriggerIdx),
			DEBUG_ITME(tagObservationSerial),
			DEBUG_ITME(tagObservationAggregationSerial),
			DEBUG_ITME(tagDisturbanceCategoryID),
			DEBUG_ITME(tagChannelInstances),
			DEBUG_ITME(tagCharactDisturbDirection),
			DEBUG_ITME(tagCharactDisturbDirectionQuality),
			DEBUG_ITME(tagOneChannelInst),
			DEBUG_ITME(tagCharactDuration),
			DEBUG_ITME(tagSeriesInstances),
			DEBUG_ITME(tagCharactMagnitude),
			DEBUG_ITME(tagCharactFrequency),
			DEBUG_ITME(tagChanTriggerModuleInfo),
			DEBUG_ITME(tagChanTriggerModuleName),
			DEBUG_ITME(tagCrossTriggerDeviceName),
			DEBUG_ITME(tagCrossTriggerChanIdx),
			DEBUG_ITME(tagChanTriggerTypeID),
			DEBUG_ITME(tagChannelFrequency),
			DEBUG_ITME(tagChannelGroupID),
			DEBUG_ITME(tagOneSeriesInstance),
			DEBUG_ITME(tagSeriesBaseQuantity),
			DEBUG_ITME(tagSeriesScale),
			DEBUG_ITME(tagSeriesOffset),
			DEBUG_ITME(tagSeriesShareChannelIdx),
			DEBUG_ITME(tagSeriesShareSeriesIdx),
			DEBUG_ITME(tagSeriesValues),
			{.name = NULL}
	};

	char *getNameByGuid(GUID guid)
	{
		int i = 0;

		while(DebugList[i].name != NULL){
			if(PQDIF_IsEqualGUID(*DebugList[i].guid,guid))
				return (char *)DebugList[i].name;

			i++;
		}

		return NULL;
	}
#endif


SIZE4 padSizeTo4Bytes(SIZE4 sizeOrig)
{
	SIZE4 remainder;

	remainder = (sizeOrig % 4);

	if (remainder == 0)
		return sizeOrig;

	return sizeOrig + (4 - remainder);
}

static void linkIn(PQAlloc *p,void *obj, size_t siz)
{
	MEMNODE * pNode;

	pNode = (MEMNODE *) pq_alloc(sizeof(MEMNODE));
	pNode->obj = obj;
	pNode->siz = siz;
	pNode->pNext = 0;

	pNode->lpos = p->lMemTotal + p->idxOffset;
	p->lMemTotal += siz;
	p->idxFilePosition = p->lMemTotal + p->idxOffset;

	if (p->pmemLast)
		p->pmemLast->pNext = pNode;
	else
		p->pmemFirst = pNode;
	pNode->pPrev = p->pmemLast;
	p->pmemLast = pNode;
}

void DestroyList(PQAlloc *p)
{
	MEMNODE *pNode;
	MEMNODE *pNext;

	pNode = p->pmemFirst;
	while (pNode) {
		pNext = pNode->pNext;

		if (pNode->obj)
			pq_free(pNode->obj);
		pq_free(pNode);

		pNode = pNext;
	}

	memset(p,0,sizeof(PQAlloc));
}

static void *allocate1(PQAlloc *p, size_t siz)
{
    size_t  siz_obj;
    void    *obj;

    siz_obj = siz;

    obj = pq_alloc( siz );
    linkIn(p, obj, siz_obj);

    return obj;
}

void *allocate(PQAlloc *p, size_t siz, long *pidx)
{
    *pidx = p->lMemTotal + p->idxOffset;

    return allocate1(p, siz);

}

collection_t *CreateCollection(PQAlloc *p,int count,size_t *size,long *idx)
{
	collection_t *c;
//	long idx;

    *size = sizeof( c_collection ) + ( count * sizeof( c_collection_element ) );
    *size = padSizeTo4Bytes( *size );

	c = allocate(p,*size,idx);

	c->collection.count = count;

	for (int i = 0; i < count; ++i) {
		c->element[i].reserved = 1;
	}

	return c;
}

static c_collection_element *element(collection_t *c,GUID guid)
{
//	if(index >= c->collection.count){
//		fprintf(stderr,"out of collection count!\n");
//		return NULL;
//	}

	for (int i = 0; i < c->collection.count; ++i) {
		if(c->element[i].reserved == 1){
			c->element[i].reserved = 0;
			return &c->element[i];
		}
	}

	fprintf(stderr,"out of collection count:%s!\n",getNameByGuid(guid));
	return NULL;
}

collection_t *addCollection(PQAlloc *p,collection_t *c,GUID guid,int count)
{
	size_t size;
	long idx;

	c_collection_element *e = element(c,guid);

	if(e){
		collection_t *c1 = CreateCollection(p,count,&size,&idx);

		e->tagElement = guid;
		e->typeElement = ID_ELEMENT_TYPE_COLLECTION;
		e->typePhysical = 0;
		e->isEmbedded = 0;

		e->link.sizeElement = size;
		e->link.linkElement = idx;

		return c1;
	}

	return NULL;
}

UINT1 *addScalarUINT1(PQAlloc *p,collection_t *c,GUID guid,UINT1 value)
{
	c_collection_element *e = element(c,guid);

	UINT1 *pValue;

	e->isEmbedded = 1;
	e->tagElement = guid;
	e->typeElement = ID_ELEMENT_TYPE_SCALAR;
	e->typePhysical = ID_PHYS_TYPE_UNS_INTEGER1;
    pValue = (UINT1 *)( e->valueEmbedded );
    *pValue = value;

    return pValue;
}

UINT2 *addScalarUINT2(PQAlloc *p,collection_t *c,GUID guid,UINT2 value)
{
	c_collection_element *e = element(c,guid);

	UINT2 *pValue;

	e->isEmbedded = 1;
	e->tagElement = guid;
	e->typeElement = ID_ELEMENT_TYPE_SCALAR;
	e->typePhysical = ID_PHYS_TYPE_UNS_INTEGER2;
    pValue = (UINT2 *)( e->valueEmbedded );
    *pValue = value;

    return pValue;
}

UINT4 *addScalarUINT4(PQAlloc *p,collection_t *c,GUID guid,UINT4 value)
{
	c_collection_element *e = element(c,guid);

	UINT4 *pValue;

	e->isEmbedded = 1;
	e->tagElement = guid;
	e->typeElement = ID_ELEMENT_TYPE_SCALAR;
	e->typePhysical = ID_PHYS_TYPE_UNS_INTEGER4;
    pValue = (UINT4 *)( e->valueEmbedded );
    *pValue = value;

    return pValue;
}

REAL4 *addScalarREAL4(PQAlloc *p,collection_t *c,GUID guid,REAL4 value)
{
	c_collection_element *e = element(c,guid);

	REAL4 *pValue;

	e->isEmbedded = 1;
	e->tagElement = guid;
	e->typeElement = ID_ELEMENT_TYPE_SCALAR;
	e->typePhysical = ID_PHYS_TYPE_REAL4;
    pValue = (REAL4 *)( e->valueEmbedded );
    *pValue = value;

    return pValue;
}

REAL8 *addScalarREAL8(PQAlloc *p,collection_t *c,GUID guid,REAL8 value)
{
	c_collection_element *e = element(c,guid);

	REAL8 *pValue;

	e->isEmbedded = 1;
	e->tagElement = guid;
	e->typeElement = ID_ELEMENT_TYPE_SCALAR;
	e->typePhysical = ID_PHYS_TYPE_REAL8;
    pValue = (REAL8 *)( e->valueEmbedded );
    *pValue = value;

    return pValue;
}

BOOL1 *addScalarBOOL1(PQAlloc *p,collection_t *c,GUID guid,BOOL1 value)
{
	c_collection_element *e = element(c,guid);

	BOOL1 *pValue;

	e->isEmbedded = 1;
	e->tagElement = guid;
	e->typeElement = ID_ELEMENT_TYPE_SCALAR;
	e->typePhysical = ID_PHYS_TYPE_BOOLEAN1;
    pValue = (BOOL1 *)( e->valueEmbedded );
    *pValue = value;

    return pValue;
}

BOOL2 *addScalarBOOL2(PQAlloc *p,collection_t *c,GUID guid,BOOL2 value)
{
	c_collection_element *e = element(c,guid);

	BOOL2 *pValue;

	e->isEmbedded = 1;
	e->tagElement = guid;
	e->typeElement = ID_ELEMENT_TYPE_SCALAR;
	e->typePhysical = ID_PHYS_TYPE_BOOLEAN2;
    pValue = (BOOL2 *)( e->valueEmbedded );
    *pValue = value;

    return pValue;
}

BOOL4 *addScalarBOOL4(PQAlloc *p,collection_t *c,GUID guid,BOOL4 value)
{
	c_collection_element *e = element(c,guid);

	BOOL4 *pValue;

	e->isEmbedded = 1;
	e->tagElement = guid;
	e->typeElement = ID_ELEMENT_TYPE_SCALAR;
	e->typePhysical = ID_PHYS_TYPE_BOOLEAN4;
    pValue = (BOOL4 *)( e->valueEmbedded );
    *pValue = value;

    return pValue;
}

TIMESTAMPPQDIF *addScalarTimeStamp(PQAlloc *p, collection_t *c, GUID guid, TIMESTAMPPQDIF value)
{
	c_collection_element *e = element(c,guid);
    struct c_scalar *   pscalar;
    TIMESTAMPPQDIF *    pValue;
    long idx;

    size_t size = sizeof( TIMESTAMPPQDIF );
    size = padSizeTo4Bytes( size );

    if(e){
    	pscalar = (c_scalar *) allocate(p, size, &idx );
    	if(pscalar){
            pValue = (TIMESTAMPPQDIF *) ( ( (char *) pscalar ) );
            *pValue = value;

            e->tagElement = guid;
            e->typeElement = ID_ELEMENT_TYPE_SCALAR;
            e->typePhysical = ID_PHYS_TYPE_TIMESTAMPPQDIF;
            e->isEmbedded = 0;
            e->reserved = 0;
            e->link.linkElement = idx;
            e->link.sizeElement  = size;

            return pValue;
    	}
    }

    return NULL;
}

GUID *addScalarGUID(PQAlloc *p, collection_t *c, GUID guid, GUID value)
{
	c_collection_element *e = element(c,guid);
    struct c_scalar *   pscalar;
    GUID *    pValue;
    long idx;

    size_t size = sizeof( GUID );
    size = padSizeTo4Bytes( size );

    if(e){
    	pscalar = (c_scalar *) allocate(p, size, &idx );
    	if(pscalar){
            pValue = (GUID *) ( ( (char *) pscalar ) );
            *pValue = value;

            e->tagElement = guid;
            e->typeElement = ID_ELEMENT_TYPE_SCALAR;
            e->typePhysical = ID_PHYS_TYPE_GUID;
            e->isEmbedded = 0;
            e->reserved = 0;
            e->link.linkElement = idx;
            e->link.sizeElement  = size;

            return pValue;
    	}
    }

    return NULL;
}

UINT1 *addVectorUINT1(PQAlloc *p,collection_t *c,GUID guid,int count)
{
	struct c_vector *pvector;
	long idx;
	UINT1 *parray = NULL;
	size_t size = sizeof(c_vector) + (count * sizeof(UINT1));
	size = padSizeTo4Bytes( size );
	c_collection_element *e = element(c,guid);

	if(e){
		pvector = allocate(p,size,&idx);
		if(pvector){
			pvector->count = count;
			parray = (UINT1 *) ( ( (char *) pvector ) + sizeof( c_vector ) );

			e->tagElement = guid;
			e->typeElement = ID_ELEMENT_TYPE_VECTOR;
			e->typePhysical = ID_PHYS_TYPE_UNS_INTEGER1;
			e->isEmbedded = 0;
			e->link.sizeElement = size;
			e->link.linkElement = idx;

			return parray;
		}
		return NULL;
	}

	return NULL;

}

UINT2 *addVectorUINT2(PQAlloc *p,collection_t *c,GUID guid,int count)
{
	struct c_vector *pvector;
	long idx;
	UINT2 *parray = NULL;
	size_t size = sizeof(c_vector) + (count * sizeof(UINT2));
	size = padSizeTo4Bytes( size );
	c_collection_element *e = element(c,guid);

	if(e){
		pvector = allocate(p,size,&idx);
		if(pvector){
			pvector->count = count;
			parray = (UINT2 *) ( ( (char *) pvector ) + sizeof( c_vector ) );

			e->tagElement = guid;
			e->typeElement = ID_ELEMENT_TYPE_VECTOR;
			e->typePhysical = ID_PHYS_TYPE_UNS_INTEGER2;
			e->isEmbedded = 0;
			e->link.sizeElement = size;
			e->link.linkElement = idx;

			return parray;
		}
		return NULL;
	}

	return NULL;

}

UINT4 *addVectorUINT4(PQAlloc *p,collection_t *c,GUID guid,int count)
{
	struct c_vector *pvector;
	long idx;
	UINT4 *parray = NULL;
	size_t size = sizeof(c_vector) + (count * sizeof(UINT4));
	size = padSizeTo4Bytes( size );
	c_collection_element *e = element(c,guid);

	if(e){
		pvector = allocate(p,size,&idx);
		if(pvector){
			pvector->count = count;
			parray = (UINT4 *) ( ( (char *) pvector ) + sizeof( c_vector ) );

			e->tagElement = guid;
			e->typeElement = ID_ELEMENT_TYPE_VECTOR;
			e->typePhysical = ID_PHYS_TYPE_UNS_INTEGER4;
			e->isEmbedded = 0;
			e->link.sizeElement = size;
			e->link.linkElement = idx;

			return parray;
		}
		return NULL;
	}

	return NULL;

}

REAL4 *addVectorREAL4(PQAlloc *p,collection_t *c,GUID guid,int count)
{
	struct c_vector *pvector;
	long idx;
	REAL4 *parray = NULL;
	size_t size = sizeof(c_vector) + (count * sizeof(REAL4));
	size = padSizeTo4Bytes( size );
	c_collection_element *e = element(c,guid);

	if(e){
		pvector = allocate(p,size,&idx);
		if(pvector){
			pvector->count = count;
			parray = (REAL4 *) ( ( (char *) pvector ) + sizeof( c_vector ) );

			e->tagElement = guid;
			e->typeElement = ID_ELEMENT_TYPE_VECTOR;
			e->typePhysical = ID_PHYS_TYPE_REAL4;
			e->isEmbedded = 0;
			e->link.sizeElement = size;
			e->link.linkElement = idx;

			return parray;
		}
		return NULL;
	}

	return NULL;

}

REAL8 *addVectorREAL8(PQAlloc *p,collection_t *c,GUID guid,int count)
{
	struct c_vector *pvector;
	long idx;
	REAL8 *parray = NULL;
	size_t size = sizeof(c_vector) + (count * sizeof(REAL8));
	size = padSizeTo4Bytes( size );
	c_collection_element *e = element(c,guid);

	if(e){
		pvector = allocate(p,size,&idx);
		if(pvector){
			pvector->count = count;
			parray = (REAL8 *) ( ( (char *) pvector ) + sizeof( c_vector ) );

			e->tagElement = guid;
			e->typeElement = ID_ELEMENT_TYPE_VECTOR;
			e->typePhysical = ID_PHYS_TYPE_REAL8;
			e->isEmbedded = 0;
			e->link.sizeElement = size;
			e->link.linkElement = idx;

			return parray;
		}
		return NULL;
	}

	return NULL;

}

char *addVectorString(PQAlloc *p, collection_t *c, GUID guid, char *sz)
{
	struct c_vector * pvector = NULL;
	long idx;
	char * pstr = NULL;

	size_t size = sizeof(c_vector) + strlen(sz) + 1;  //  Extra byte for NULL-term
	size = padSizeTo4Bytes(size);
	c_collection_element *e = element(c,guid);

	if(e){
		pvector = (c_vector *) allocate(p, size, &idx);
		if (pvector) {
			pvector->count = strlen(sz) + 1;

			pstr = (char *) (((char *) pvector) + sizeof(c_vector));
			strncpy(pstr, sz, strlen(sz) + 1);
			pstr[strlen(sz)] = '\0';

			e->tagElement = guid;
			e->typeElement = ID_ELEMENT_TYPE_VECTOR;
			e->typePhysical = ID_PHYS_TYPE_CHAR1;
			e->isEmbedded = 0;
			e->reserved = 0;
			e->link.linkElement = idx;
			e->link.sizeElement = size;
		}

		return pstr;
	}

	return NULL;
}

void UpdateCRC(PQAlloc *p, int compression)
{
	MEMNODE * pNode;

	//  Init CRC
	if (compression == ID_COMP_ALG_NONE) {
		p->lCrc32Compressed = 0;
		return ;
	} else if (compression == ID_COMP_ALG_ZLIB) {
		p->lCrc32Compressed = adler32(0L, Z_NULL, 0);
	}

	pNode = p->pmemFirst;
	while (pNode) {
		if (compression == ID_COMP_ALG_NONE) {
			//  Nothing!
			break;
		} else if (compression == ID_COMP_ALG_ZLIB) {
			//  Update the CRC for this block
			p->lCrc32Compressed = adler32(p->lCrc32Compressed, (Bytef *) pNode->obj,
					pNode->siz);
		} else {
			//  Not supported!
			break;
		}

		pNode = pNode->pNext;
	}
}

long writeList(int fd,PQAlloc *p,int compression)
{
	z_stream c_stream;
    uInt sizeOut = 4096;
    Bytef *bufferOut;
    int err;
    MEMNODE *pNode;
    long sizeFinal = 0;
    long crc = 0;

	if(compression == ID_COMP_ALG_ZLIB){
        //  Init ZLIB for best compression ratio
        memset( &c_stream, 0, sizeof( c_stream ) );
        c_stream.zalloc = (alloc_func)0;
        c_stream.zfree = (free_func)0;
        c_stream.opaque = (voidpf)0;
        err = deflateInit( &c_stream, Z_BEST_COMPRESSION );

        //  Allocate an output buffer big enough to handle 4096 bytes at once.
        //  NOTE:   If you are working in the 16-bit world, you may not be able
        //          to do this. You may have to break it up into <64K blocks.
        bufferOut = pq_alloc(sizeOut);
        c_stream.avail_out = sizeOut;
        c_stream.next_out = bufferOut;

        crc = adler32(0L, Z_NULL, 0);
	}

	pNode = p->pmemFirst;
	if(pNode == NULL){

	}

	while(pNode){
		if( compression == ID_COMP_ALG_NONE ){
			write(fd,pNode->obj,pNode->siz);
		}else if(compression == ID_COMP_ALG_ZLIB){
			c_stream.next_in = (Bytef *) pNode->obj;
			c_stream.avail_in = (uInt) pNode->siz;

			while( c_stream.avail_in > 0 ){
				err = deflate( &c_stream, Z_NO_FLUSH );
				if( c_stream.total_out > (sizeOut/2) ){
					sizeFinal += c_stream.total_out;
					crc = adler32(crc, bufferOut,c_stream.total_out);
					write(fd,bufferOut,c_stream.total_out);
					c_stream.avail_out = sizeOut;
					c_stream.next_out = bufferOut;
					c_stream.total_out = 0;
				}
			}
		}
		pNode = pNode->pNext;
	}

	if( compression == ID_COMP_ALG_ZLIB ){
		do{
			err = deflate( &c_stream, Z_FINISH );
			if( c_stream.total_out > 0 ){
				sizeFinal += c_stream.total_out;
				crc = adler32(crc, bufferOut,c_stream.total_out);
				write(fd,bufferOut,c_stream.total_out);
				c_stream.avail_out = sizeOut;
				c_stream.next_out  = bufferOut;
				c_stream.total_out = 0;
			}

			if(err == Z_STREAM_END)
				break;
		}while(err == Z_OK);

		p->lMemTotal = sizeFinal;
		p->lCrc32Compressed = crc;

		pq_free(bufferOut);

		err = deflateEnd(&c_stream);
	}

	return p->idxFilePosition;
}

long saveRecord(int fd,PQAlloc *p,GUID guid,long idx,int haveNextRecord,int compression)
{
	c_record_mainheader header;
	long idxFilePosition = idx;

	header.guidRecordSignature = guidRecordSignaturePQDIF;
	header.tagRecordType = guid;
	header.sizeHeader = 64;
	header.sizeData = p->lMemTotal;

	lseek(fd,idxFilePosition+64,SEEK_SET);
	idx = writeList(fd,p,compression);
	header.sizeData = p->lMemTotal;

	if(haveNextRecord)
		header.linkNextRecord = p->lMemTotal + 64 + idxFilePosition;
	else
		header.linkNextRecord = 0;

//	UpdateCRC(p,compression);
	header.checksum = p->lCrc32Compressed;

	lseek(fd,idxFilePosition,SEEK_SET);
	write(fd,&header,sizeof(header));
	idxFilePosition += header.sizeHeader + header.sizeData;

	return idxFilePosition;
}

