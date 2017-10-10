/*
 * pqalloc.c
 *
 *  Created on: 2017Äê10ÔÂ10ÈÕ
 *      Author: zjm09
 */

#include "../inc/tags.h"
#include "../inc/name_id.h"
#include "../inc/pqalloc.h"

SIZE4 padSizeTo4Bytes(SIZE4 sizeOrig)
{
	SIZE4 remainder;

	remainder = (sizeOrig % 4);

	//  Already multiple of 4?
	if (remainder == 0)
		return sizeOrig;

	//  Pad it
	return sizeOrig + (4 - remainder);
}

void PQAlloc_Initialize(PQAlloc *p)
{
	p->bShowMessage = 0;
	p->lMemTotal = 0;
	p->lCrc32Compressed = 0;
	p->idxOffset = 0;
	p->pmemFirst = 0;
	p->pmemLast = 0;
}

void PQAlloc_Reinitialize(PQAlloc *p, long offset)
{
	PQAlloc_DestroyList(p);
	PQAlloc_Initialize(p);
	p->idxOffset = offset;
}

void *allocate1(PQAlloc *p, size_t siz)
{
    size_t  siz_obj;
    void    *obj;

    siz_obj = siz;

    obj = calloc( 1, siz );
    PQAlloc_LinkIn(p, obj, siz_obj);

    return obj;
}

void *allocate2(PQAlloc *p, size_t siz, long *pidx)
{
    *pidx = p->lMemTotal + p->idxOffset;

    return allocate1(p, siz);

}

void * addCollection1(PQAlloc *p, UINT4 count, long idx, SIZE4 size)
{
	struct c_collection * pcoll = NULL;
	struct c_collection_element * parrayElement = NULL;

	size = sizeof(c_collection) + (count * sizeof(c_collection_element));
	size = padSizeTo4Bytes(size);

	pcoll = (c_collection *) allocate2(p, size, idx);
	if (pcoll) {
		/*  Init the collection header */
		pcoll->count = count;

		/*  Find the beginning of the array */
		parrayElement = (c_collection_element *) (((char *) pcoll)
				+ sizeof(*pcoll));
	}

	return parrayElement;
}

void * addCollection(PQAlloc *p, UINT4 count, long idx, SIZE4 size,
		GUID tag, c_collection_element *ce)
{
	struct c_collection_element * parrayElement = NULL;

	parrayElement = addCollection1(p, count, idx, size);
	if (parrayElement) {
		/*  Set up the collection element properly */
		ce->tagElement = tag;
		ce->typeElement = ID_ELEMENT_TYPE_COLLECTION;
		ce->typePhysical = 0; /*  ??? */
		ce->isEmbedded = FALSE;
		ce->reserved = 0;
		ce->link.linkElement = idx;
		ce->link.sizeElement = size;
	}

	return parrayElement;
}

UINT4 * addScalarUINT4(PQAlloc *p, UINT4 value, long idx, SIZE4 size,
		GUID tag, c_collection_element *ce)
{
	UINT4 * pValue;

	/*  This is not more than 8 bytes --  */
	/*  no additional space is allocated. */
	size = 0;
	idx = idx;

	/*  Set up the collection element properly */
	ce->tagElement = tag;
	ce->typeElement = ID_ELEMENT_TYPE_SCALAR;
	ce->typePhysical = ID_PHYS_TYPE_UNS_INTEGER4;
	ce->isEmbedded = TRUE;
	ce->reserved = 0;
	pValue = (UINT4 *) (ce->valueEmbedded);
	*pValue = value;

	return pValue;
}

BOOL4 * addScalarBOOL4(PQAlloc *p, BOOL4 value, long idx,
		SIZE4 size, GUID tag, c_collection_element *ce)
{
	BOOL4 * pValue;

	/*  This is not more than 8 bytes --  */
	/*  no additional space is allocated. */
	size = 0;
	idx = idx;

	/*  Set up the collection element properly */
	ce->tagElement = tag;
	ce->typeElement = ID_ELEMENT_TYPE_SCALAR;
	ce->typePhysical = ID_PHYS_TYPE_BOOLEAN4;
	ce->isEmbedded = TRUE;
	ce->reserved = 0;
	pValue = (BOOL4 *) (ce->valueEmbedded);
	*pValue = value;

	return pValue;
}

REAL8 * addScalarREAL8(PQAlloc *p, REAL8 value, long idx,
		SIZE4 size, GUID tag, c_collection_element * ce)
{
	REAL8 * pValue;

	/*  This is not more than 8 bytes --  */
	/*  no additional space is allocated. */
	size = 0;
	idx = idx;

	/*  Set up the collection element properly */
	ce->tagElement = tag;
	ce->typeElement = ID_ELEMENT_TYPE_SCALAR;
	ce->typePhysical = ID_PHYS_TYPE_REAL8;
	ce->isEmbedded = TRUE;
	ce->reserved = 0;
	pValue = (REAL8 *) (ce->valueEmbedded);
	*pValue = value;

	return pValue;
}



TIMESTAMPPQDIF * addScalarTimeStamp(PQAlloc *p, TIMESTAMPPQDIF value,
		long *pidx, SIZE4 size, GUID tag, c_collection_element *ce)
{
	struct c_scalar * pscalar;
	TIMESTAMPPQDIF * pValue;

	/*  Since this is more than 8 bytes, we need */
	/*  to allocate more space-> */
	size = sizeof(TIMESTAMPPQDIF);
	size = padSizeTo4Bytes(size);

	pscalar = (struct c_scalar *) allocate2(p, size, *pidx);
	if (pscalar) {
		/*  Init the scalar header */
		/*  (Nothing there) */

		/*  Copy over the string portion */
		pValue = (TIMESTAMPPQDIF *) (((char *) pscalar));
		*pValue = value;

		/*  Set up the collection element properly */
		ce->tagElement = tag;
		ce->typeElement = ID_ELEMENT_TYPE_SCALAR;
		ce->typePhysical = ID_PHYS_TYPE_TIMESTAMPPQDIF;
		ce->isEmbedded = FALSE;
		ce->reserved = 0;
		ce->link.linkElement = pidx;
		ce->link.sizeElement = size;
	}

	return pValue;
}

GUID * addScalarGUID(PQAlloc *p, GUID value, long *pidx, SIZE4 size,
		GUID tag, c_collection_element *ce)
{
	struct c_scalar * pscalar;
	GUID * pValue;

	/*  Since this is more than 8 bytes, we must allocate more space-> */
	size = sizeof(GUID);
	size = padSizeTo4Bytes(size);

	pscalar = (struct c_scalar *) allocate2(p, size, pidx);
	if (pscalar) {
		/*  Init the scalar header */
		/*  (Nothing there) */

		/*  Copy over the string portion */
		pValue = (GUID *) (((char *) pscalar));
		*pValue = value;

		/*  Set up the collection element properly */
		ce->tagElement = tag;
		ce->typeElement = ID_ELEMENT_TYPE_SCALAR;
		ce->typePhysical = ID_PHYS_TYPE_GUID;
		ce->isEmbedded = FALSE;
		ce->reserved = 0;
		ce->link.linkElement = *pidx;
		ce->link.sizeElement = size;
	}

	return pValue;
}

char * addVectorString(PQAlloc *p, char * sz, long *pidx, SIZE4 size,
		GUID tag, c_collection_element *ce)
{
	struct c_vector * pvector = NULL;
	char * pstr = NULL;

	/*  Since this is more than 8 bytes, we must allocate more space-> */
	size = sizeof(c_vector) + strlen(sz) + 1; /*  Extra byte for NULL-term */
	size = padSizeTo4Bytes(size);

	pvector = (c_vector *) allocate2(p, size, pidx);
	if (pvector) {
		/*  Init the vector header */
		pvector->count = strlen(sz) + 1;

		/*  Copy over the string portion */
		pstr = (char *) (((char *) pvector) + sizeof(c_vector));
		strncpy(pstr, sz, strlen(sz) + 1);
		pstr[strlen(sz)] = '\0';

		/*  Set up the collection element properly */
		ce->tagElement = tag;
		ce->typeElement = ID_ELEMENT_TYPE_VECTOR;
		ce->typePhysical = ID_PHYS_TYPE_CHAR1;
		ce->isEmbedded = FALSE;
		ce->reserved = 0;
		ce->link.linkElement = *pidx;
		ce->link.sizeElement = size;
	}

	return pstr;
}

UINT4 * allocVectorUINT4(PQAlloc *p, long count, long *pidx, SIZE4 size,
		GUID tag, c_collection_element *ce)
{
	struct c_vector * pvector = NULL;
	UINT4 * parray = NULL;

	/*  Since this is more than 8 bytes, we must allocate more space-> */
	size = sizeof(c_vector) + (count * sizeof(UINT4));
	size = padSizeTo4Bytes(size);

	pvector = (c_vector *) allocate2(p, size, pidx);
	if (pvector) {
		/*  Init the vector header */
		pvector->count = count;

		/*  Find where the array starts */
		parray = (UINT4 *) (((char *) pvector) + sizeof(c_vector));

		/*  Set up the collection element properly */
		ce->tagElement = tag;
		ce->typeElement = ID_ELEMENT_TYPE_VECTOR;
		ce->typePhysical = ID_PHYS_TYPE_UNS_INTEGER4;
		ce->isEmbedded = FALSE;
		ce->reserved = 0;
		ce->link.linkElement = *pidx;
		ce->link.sizeElement = size;
	}

	return parray;

}

INT4 * allocVectorINT4(PQAlloc *p, long count, long *pidx, SIZE4 size,
		GUID tag, c_collection_element *ce)
{
	struct c_vector * pvector = NULL;
	INT4 * parray = NULL;

	/*  Since this is more than 8 bytes, we must allocate more space-> */
	size = sizeof(c_vector) + (count * sizeof(INT4));
	size = padSizeTo4Bytes(size);

	pvector = (c_vector *) allocate2(p, size, pidx);
	if (pvector) {
		/*  Init the vector header */
		pvector->count = count;

		/*  Find where the array starts */
		parray = (INT4 *) (((char *) pvector) + sizeof(c_vector));

		/*  Set up the collection element properly */
		ce->tagElement = tag;
		ce->typeElement = ID_ELEMENT_TYPE_VECTOR;
		ce->typePhysical = ID_PHYS_TYPE_INTEGER4;
		ce->isEmbedded = FALSE;
		ce->reserved = 0;
		ce->link.linkElement = *pidx;
		ce->link.sizeElement = size;
	}

	return parray;

}

REAL8 * allocVectorREAL8(PQAlloc *p, long count, REAL8 * paValues, long *pidx,
		SIZE4 size, GUID tag, c_collection_element *ce)
{
	struct c_vector * pvector = NULL;
	REAL8 * parray = NULL;

	/*  Since this is more than 8 bytes, we must allocate more space-> */
	size = sizeof(c_vector) + (count * sizeof(REAL8));
	size = padSizeTo4Bytes(size);

	pvector = (c_vector *) allocate2(p, size, pidx);
	if (pvector) {
		/*  Init the vector header */
		pvector->count = count;

		/*  Find where the array starts */
		parray = (REAL8 *) (((char *) pvector) + sizeof(c_vector));
		if (paValues) {
			long idx;
			for (idx = 0; idx < count; idx++) {
				parray[idx] = paValues[idx];
			}
		}

		/*  Set up the collection element properly */
		ce->tagElement = tag;
		ce->typeElement = ID_ELEMENT_TYPE_VECTOR;
		ce->typePhysical = ID_PHYS_TYPE_REAL8;
		ce->isEmbedded = FALSE;
		ce->reserved = 0;
		ce->link.linkElement = *pidx;
		ce->link.sizeElement = size;
	}

	return parray;
}

INT1 * allocVectorINT1(PQAlloc *p, long count, long *pidx, SIZE4 size,
		GUID tag, c_collection_element *ce)
{
	struct c_vector * pvector = NULL;
	INT1 * parray = NULL;

	/*  Since this is more than 8 bytes, we must allocate more space-> */
	size = sizeof(c_vector) + (count * sizeof(INT1));
	size = padSizeTo4Bytes(size);

	pvector = (c_vector *) allocate2(p, size, pidx);
	if (pvector) {
		/*  Init the vector header */
		pvector->count = count;

		/*  Find where the array starts */
		parray = (INT1 *) (((char *) pvector) + sizeof(c_vector));

		/*  Set up the collection element properly */
		ce->tagElement = tag;
		ce->typeElement = ID_ELEMENT_TYPE_VECTOR;
		ce->typePhysical = ID_PHYS_TYPE_INTEGER1;
		ce->isEmbedded = FALSE;
		ce->reserved = 0;
		ce->link.linkElement = pidx;
		ce->link.sizeElement = size;
	}

	return parray;
}

TIMESTAMPPQDIF * allocVectorTimeStamp(PQAlloc *p, long count, long *pidx,
		SIZE4 size, GUID tag, c_collection_element *ce)
{
	struct c_vector * pvector = NULL;
	TIMESTAMPPQDIF * parray = NULL;

	/*  Since this is more than 8 bytes, we must allocate more space-> */
	size = sizeof(c_vector) + (count * sizeof(TIMESTAMPPQDIF));
	size = padSizeTo4Bytes(size);

	pvector = (c_vector *) allocate2(p, size, pidx);
	if (pvector) {
		/*  Init the vector header */
		pvector->count = count;

		/*  Find where the array starts */
		parray = (TIMESTAMPPQDIF *) (((char *) pvector) + sizeof(c_vector));

		/*  Set up the collection element properly */
		ce->tagElement = tag;
		ce->typeElement = ID_ELEMENT_TYPE_VECTOR;
		ce->typePhysical = ID_PHYS_TYPE_TIMESTAMPPQDIF;
		ce->isEmbedded = FALSE;
		ce->reserved = 0;
		ce->link.linkElement = *pidx;
		ce->link.sizeElement = size;
	}

	return parray;
}

void PQAlloc_LinkIn(PQAlloc *p,void *obj, size_t siz)
{
	MEMNODE * pNode;
	/*
	 **
	 **  Allocate a new node
	 */
	pNode = (MEMNODE *) calloc(1, sizeof(MEMNODE));
	pNode->obj = obj;
	pNode->siz = siz;
	pNode->pNext = 0;
	/*
	 **
	 **  Save position suitable for use as the file offset
	 */
	pNode->lpos = p->lMemTotal + p->idxOffset;
	p->lMemTotal += siz;
	p->idxFilePosition = p->lMemTotal + p->idxOffset;
	/*
	 **
	 **  Put in chain
	 */
	if (p->pmemLast)
		p->pmemLast->pNext = pNode;
	else
		p->pmemFirst = pNode;
	pNode->pPrev = p->pmemLast;
	p->pmemLast = pNode;
}

void PQAlloc_DestroyList(PQAlloc *p)
{
	MEMNODE *pNode;
	MEMNODE *pNext;

	pNode = p->pmemFirst;
	while (pNode) {
		pNext = pNode->pNext;

		if (pNode->obj)
			free(pNode->obj);
		free(pNode);

		pNode = pNext;
	}
	PQAlloc_Initialize(p);
}
