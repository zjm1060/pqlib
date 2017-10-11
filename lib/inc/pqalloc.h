/*
 * pqalloc.h
 *
 *  Created on: 2017Äê10ÔÂ10ÈÕ
 *      Author: zjm09
 */

#ifndef LIB_INC_PQALLOC_H_
#define LIB_INC_PQALLOC_H_

#define BOOL    short
#define DWORD   unsigned long
#define TRUE    1
#define FALSE   0

typedef struct MemNode MEMNODE;

struct MemNode {
	void * obj;
	size_t siz;
	long lpos;

	MEMNODE * pPrev;
	MEMNODE * pNext;
};


typedef struct stPQAlloc {
	/*    private:*/
	MEMNODE * pmemFirst;
	MEMNODE * pmemLast;

	/*    protected:*/
	/*    public:	*/

	BOOL bShowMessage;
	long lMemTotal; 		/*  Total size of objects managed in allocator  */
	UINT4 lCrc32Compressed; 	/*  CRC of the objects (if compression is used)	*/
	long idxFilePosition; 	/*  next available position in pseudo file		*/
	long idxOffset; 		/*  Offset to be added to the idx				*/
							/*  parameter returned by allocate				*/
							/*  Used to allow resetting allocators			*/
							/*  but return correct file offset				*/

} PQAlloc;

void PQAlloc_Initialize(PQAlloc *p);
void PQAlloc_Reinitialize(PQAlloc *p, long offset);
void * addCollection(PQAlloc *p, UINT4 count, long idx, SIZE4 size,
		GUID tag, c_collection_element *ce);
UINT4 * addScalarUINT4(PQAlloc *p, UINT4 value, long idx, SIZE4 size,
		GUID tag, c_collection_element *ce);
BOOL4 * addScalarBOOL4(PQAlloc *p, BOOL4 value, long idx,
		SIZE4 size, GUID tag, c_collection_element *ce);
REAL8 * addScalarREAL8(PQAlloc *p, REAL8 value, long idx,
		SIZE4 size, GUID tag, c_collection_element * ce);
TIMESTAMPPQDIF * addScalarTimeStamp(PQAlloc *p, TIMESTAMPPQDIF value,
		long *pidx, SIZE4 size, GUID tag, c_collection_element *ce);
GUID * addScalarGUID(PQAlloc *p, GUID value, long *pidx, SIZE4 size,
		GUID tag, c_collection_element *ce);
char * addVectorString(PQAlloc *p, char * sz, long *pidx, SIZE4 size,
		GUID tag, c_collection_element *ce);
UINT4 * allocVectorUINT4(PQAlloc *p, long count, long *pidx, SIZE4 size,
		GUID tag, c_collection_element *ce);
INT4 * allocVectorINT4(PQAlloc *p, long count, long *pidx, SIZE4 size,
		GUID tag, c_collection_element *ce) ;
REAL8 * allocVectorREAL8(PQAlloc *p, long count, REAL8 * paValues, long *pidx,
		SIZE4 size, GUID tag, c_collection_element *ce) ;
INT1 * allocVectorINT1(PQAlloc *p, long count, long *pidx, SIZE4 size,
		GUID tag, c_collection_element *ce);
TIMESTAMPPQDIF * allocVectorTimeStamp(PQAlloc *p, long count, long *pidx,
		SIZE4 size, GUID tag, c_collection_element *ce);


#endif /* LIB_INC_PQALLOC_H_ */
