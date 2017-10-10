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
