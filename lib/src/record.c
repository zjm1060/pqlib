/*
 * record.c
 *
 *  Created on: 2017Äê10ÔÂ10ÈÕ
 *      Author: zjm09
 */

#include "../inc/record.h"

long writeToFile(int fd,Record *r,int compression)
{
#if 0
	z_stream c_stream;
	uInt sizeOut = 4096;
	Bytef *bufferOut;
	long sizeFinal = 0;
	int err;

	memset( &c_stream, 0, sizeof( c_stream ) );
	c_stream.zalloc = (alloc_func)0;
	c_stream.zfree = (free_func)0;
	c_stream.opaque = (voidpf)0;
	err = deflateInit( &c_stream, Z_BEST_COMPRESSION );

	bufferOut = pq_alloc(sizeOut);
	c_stream.avail_out = sizeOut;
	c_stream.next_out = bufferOut;

	if(compression == ID_COMP_ALG_ZLIB){

	}

	err = deflate( &c_stream, Z_FINISH );
	if( c_stream.total_out > 0 ){
		sizeFinal += c_stream.total_out;
		write(fd,bufferOut,c_stream.total_out);
	}

	pq_free(bufferOut);

	err = deflateEnd(&c_stream);
#endif

}

long writeRecordHeader(int fd,c_record_mainheader *header)
{

}

long writeCollection(int fd,tag *collection,int compression)
{
	c_collection body;

	body.count = collection->num_of_collection;
}

long writeRecordBody(int fd,Record *r,int compression)
{

}

void recordSync(int fd,Record *r,GUID recordType,int compression)
{
	c_record_mainheader header;
	struct c_collection body;
	struct c_collection_element element;

	body.count = r->num_of_collection;

	header.guidRecordSignature = guidRecordSignaturePQDIF;
	header.tagRecordType = recordType;
	header.sizeHeader = 64;
	header.sizeData = 0;
	header.linkNextRecord = header.sizeHeader + header.sizeData;
}

SIZE4 padSizeTo4Bytes(SIZE4 sizeOrig)
{
	SIZE4 remainder;

	remainder = (sizeOrig % 4);

	if (remainder == 0)
		return sizeOrig;

	return sizeOrig + (4 - remainder);
}

collection_t *CreateCollection(int count,size_t *size,long idx)
{
	collection_t *c;

    *size = sizeof( c_collection ) + ( count * sizeof( c_collection_element ) );
    *size = padSizeTo4Bytes( *size );

	c = pq_alloc(*size);

	c->collection.count = count;
	c->p.idxOffset = idx + (*size);

	return c;
}

c_collection_element *element(collection_t *c,int index)
{
	return &c->element[index];
}

collection_t *addCollection(collection_t *c,GUID guid,int count,int index)
{
	size_t size;
	c_collection_element *e = element(c,index);
	collection_t *c1 = CreateCollection(count,&size,c->p.idxOffset);

	c->p.lMemTotal += size;
	c->p.idxOffset += size;

	e->tagElement = guid;
	e->typeElement = ID_ELEMENT_TYPE_COLLECTION;
	e->typePhysical = 0;
	e->isEmbedded = 0;

	e->link.sizeElement = size;
	e->link.linkElement = c->p.idxOffset;

	return c1;
}

UINT1 *addScalarUINT1(collection_t *c,GUID guid,UINT1 value,int index)
{
	c_collection_element *e = element(c,index);;

	UINT1 *pValue;

	e->isEmbedded = 1;
	e->tagElement = guid;
	e->typeElement = ID_ELEMENT_TYPE_SCALAR;
	e->typePhysical = ID_PHYS_TYPE_UNS_INTEGER4;
    pValue = (UINT1 *)( e->valueEmbedded );
    *pValue = value;

    return pValue;
}

UINT2 *addScalarUINT2(collection_t *c,GUID guid,UINT2 value,int index)
{
	c_collection_element *e = element(c,index);

	UINT2 *pValue;

	e->isEmbedded = 1;
	e->tagElement = guid;
	e->typeElement = ID_ELEMENT_TYPE_SCALAR;
	e->typePhysical = ID_PHYS_TYPE_UNS_INTEGER4;
    pValue = (UINT2 *)( e->valueEmbedded );
    *pValue = value;

    return pValue;
}

UINT4 *addScalarUINT4(collection_t *c,GUID guid,UINT4 value,int index)
{
	c_collection_element *e = element(c,index);

	UINT4 *pValue;

	e->isEmbedded = 1;
	e->tagElement = guid;
	e->typeElement = ID_ELEMENT_TYPE_SCALAR;
	e->typePhysical = ID_PHYS_TYPE_UNS_INTEGER4;
    pValue = (UINT4 *)( e->valueEmbedded );
    *pValue = value;

    return pValue;
}

UINT4 *addVectorUINT4(collection_t *c,GUID guid,int count,int index)
{
	struct c_vector *pvector;
	UINT4 *parray = NULL;
	size_t size = sizeof(c_vector) + (count * sizeof(UINT4));
	size = padSizeTo4Bytes( size );

	pvector = pq_alloc(size);
	if(pvector){
		c->p.lMemTotal += size;
		c->p.idxOffset += size;
		// TODO link the pvector to list

		c_collection_element *e = element(c,index);
		pvector->count = count;
		parray = (UINT4 *) ( ( (char *) pvector ) + sizeof( c_vector ) );

		e->tagElement = guid;
		e->typeElement = ID_ELEMENT_TYPE_VECTOR;
		e->typePhysical = ID_PHYS_TYPE_UNS_INTEGER4;
		e->isEmbedded = 0;
		e->link.sizeElement = size;
		e->link.linkElement = c->p.idxOffset;
	}

	return parray;
}

int main(void)
{
	size_t size;

	collection_t *c = CreateCollection(4,&size,0);

	addScalarUINT4(c,tagPhaseID,9,0);
	addScalarUINT4(c,tagQuantityMeasuredID,6,1);
	addScalarUINT4(c,tagQuantityMeasuredID,4,2);
	UINT4 *dp = addVectorUINT4(c,tagQuantityMeasuredID,4,3);
	dp[0] = 1;
	dp[1] = 0;
	dp[2] = 3;
	dp[3] = 6;
}
