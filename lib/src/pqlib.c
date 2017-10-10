/*
 * pqlib.c
 *
 *  Created on: 2017Äê10ÔÂ9ÈÕ
 *      Author: zjm09
 */

#include "../inc/pqlib.h"

pqdif *pqdif_create(const char *path)
{
	pqdif *pq = pq_alloc(sizeof(pqdif));

	pq->Container = ContainerCreate();
	pq->DataSource = DataSourceCreate(ID_DS_TYPE_MEASURE,1);

	return pq;
}

void pqdif_sync(pqdif *pq)
{

}

void pqdif_free(pqdif *pq)
{
	ContainerFree(pq->Container);
	DataSourceFree(pq->DataSource);

	pq_free(pq);
}

