/*
 * tags.c
 *
 *  Created on: 2017Äê10ÔÂ9ÈÕ
 *      Author: zjm09
 */

#include <time.h>

#include "../inc/tags.h"

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

#define tagAlloc()	 \
	({tag *___t = pq_alloc(sizeof(tag)); \
	if(___t == NULL) \
		return NULL ;\
	(___t);\
	})

tag *createTagCollection(GUID guid,int num_of_child_is_alloc)
{
	tag *t = tagAlloc();

	t->element.tagElement = guid;
	t->element.typeElement = ID_ELEMENT_TYPE_COLLECTION;

#if !STATIC_COLLECTION_NUM
	t->num_of_child_is_alloc = num_of_child_is_alloc;
	t->child = pq_alloc(sizeof(tag*)*num_of_child_is_alloc);
#endif

#if DEBUG
	t->name = getNameByGuid(guid);
#endif

	return t;
}

void vectorFree(tag *p)
{
	if(p->element.isEmbedded == 0){
		pq_free(p->data);
	}

	pq_free(p);
}

tag *createTagVector(GUID guid,int phy,void *vector,size_t vector_len)
{
	tag *t = tagAlloc();

	t->element.tagElement = guid;
	t->element.typeElement = ID_ELEMENT_TYPE_VECTOR;
	t->element.typePhysical = phy;
	t->element.link.sizeElement = vector_len;

#if DEBUG
	t->name = getNameByGuid(guid);
#endif

	switch(phy){
		case ID_PHYS_TYPE_BOOLEAN1:
		case ID_PHYS_TYPE_CHAR1:
		case ID_PHYS_TYPE_INTEGER1:
		case ID_PHYS_TYPE_UNS_INTEGER1:{
				if(vector_len <= 8){
					memcpy(t->element.valueEmbedded,vector,vector_len);
					t->element.isEmbedded = 1;
				}else{
					t->data = pq_alloc(vector_len);
					memcpy(t->data,vector,vector_len);
				}
			}break;

		case ID_PHYS_TYPE_BOOLEAN2:
		case ID_PHYS_TYPE_CHAR2:
		case ID_PHYS_TYPE_INTEGER2:
		case ID_PHYS_TYPE_UNS_INTEGER2:{
				t->element.link.sizeElement *= 2;
				if(vector_len <= 4){
					memcpy(t->element.valueEmbedded,vector,vector_len*2);
					t->element.isEmbedded = 1;
				}else{
					t->data = calloc(1,vector_len*2);
					memcpy(t->data,vector,vector_len*2);
				}
			}break;
		case ID_PHYS_TYPE_BOOLEAN4:
		case ID_PHYS_TYPE_INTEGER4:
		case ID_PHYS_TYPE_UNS_INTEGER4:
		case ID_PHYS_TYPE_REAL4:{
				t->element.link.sizeElement *= 4;
				if(vector_len <= 2){
					memcpy(t->element.valueEmbedded,vector,vector_len*4);
					t->element.isEmbedded = 1;
				}else{
					t->data = calloc(1,vector_len*4);
					memcpy(t->data,vector,vector_len*4);
				}
			}break;

		case ID_PHYS_TYPE_REAL8:
		case ID_PHYS_TYPE_COMPLEX8:{
				t->element.link.sizeElement *= 8;
				if(vector_len == 1){
					memcpy(t->element.valueEmbedded,vector,8);
					t->element.isEmbedded = 1;
				}else{
					t->data = calloc(1,vector_len*8);
					memcpy(t->data,vector,vector_len*8);
				}
			}break;

//		case ID_PHYS_TYPE_TIMESTAMPPQDIF:
//			t->time = pq_alloc(sizeof(TIMESTAMPPQDIF));
//			memcpy(t->time,vector,sizeof(TIMESTAMPPQDIF));
//			break;
		case ID_PHYS_TYPE_COMPLEX16:
//		case ID_PHYS_TYPE_GUID:
			t->data = pq_alloc(sizeof(GUID));
			memcpy(t->data,vector,sizeof(GUID));
			break;
	}

	return t;
}

void scalarFree(tag *p)
{
	if(p->element.typePhysical == ID_PHYS_TYPE_TIMESTAMPPQDIF ||
			p->element.typePhysical == ID_PHYS_TYPE_COMPLEX16 ||
			p->element.typePhysical == ID_PHYS_TYPE_GUID){
		pq_free(p->data);
	}

	pq_free(p);
}


tag *createTagScalar(GUID guid,int phy,void *vector)
{
	tag *t = tagAlloc();

	t->element.tagElement = guid;
	t->element.typeElement = ID_ELEMENT_TYPE_SCALAR;
	t->element.typePhysical = phy;

#if DEBUG
	t->name = getNameByGuid(guid);
#endif

	switch(phy){
		case ID_PHYS_TYPE_BOOLEAN1:
		case ID_PHYS_TYPE_CHAR1:
		case ID_PHYS_TYPE_INTEGER1:
		case ID_PHYS_TYPE_UNS_INTEGER1:{
				t->element.valueEmbedded[0] = *((UINT1 *)vector);
				t->element.isEmbedded = 1;
			}break;

		case ID_PHYS_TYPE_BOOLEAN2:
		case ID_PHYS_TYPE_CHAR2:
		case ID_PHYS_TYPE_INTEGER2:
		case ID_PHYS_TYPE_UNS_INTEGER2:{
				t->element.valueEmbedded[0] = *((UINT2 *)vector);
				t->element.isEmbedded = 1;
			}break;
		case ID_PHYS_TYPE_BOOLEAN4:
		case ID_PHYS_TYPE_INTEGER4:
		case ID_PHYS_TYPE_UNS_INTEGER4:
		case ID_PHYS_TYPE_REAL4:{
				t->element.valueEmbedded[0] = *((UINT4 *)vector);
				t->element.isEmbedded = 1;
			}break;

		case ID_PHYS_TYPE_REAL8:
		case ID_PHYS_TYPE_COMPLEX8:{
				memcpy(t->element.valueEmbedded,vector,8);
				t->element.isEmbedded = 1;
			}break;

		case ID_PHYS_TYPE_TIMESTAMPPQDIF:
			t->data = pq_alloc(sizeof(TIMESTAMPPQDIF));
			memcpy(t->data,vector,sizeof(TIMESTAMPPQDIF));
			break;
		case ID_PHYS_TYPE_COMPLEX16:
		case ID_PHYS_TYPE_GUID:
			t->data = pq_alloc(sizeof(GUID));
			memcpy(t->data,vector,sizeof(GUID));
			break;
	}

	return t;
}

tag *createTagString(GUID guid,const char *str)
{
	return createTagVector(guid,ID_PHYS_TYPE_CHAR1,(void *)str,strlen(str));
}

tag *createTagTimestamp(GUID guid,struct timespec s)
{
	TIMESTAMPPQDIF t;

	t.day = s.tv_sec/SECONDS_PER_DAY;
	t.sec = s.tv_sec%SECONDS_PER_DAY + s.tv_nsec*1.0/1000000000;

	return createTagScalar(guid,ID_PHYS_TYPE_TIMESTAMPPQDIF,&t);
}

tag *createTagGUID(GUID guid,GUID v)
{
	return createTagScalar(guid,ID_PHYS_TYPE_GUID,&v);
}

void collectionAdd(tag *father,tag *child)
{
	for (int i = 0; i < father->num_of_child_is_alloc; ++i) {
		if(father->child[i] == NULL){
			father->child[i] = child;
			father->num_of_collection ++;
			return;
		}
	}

	father->num_of_child_is_alloc ++;
	father->child = realloc(father->child,sizeof(tag*)*father->num_of_child_is_alloc);

	father->child[father->num_of_child_is_alloc-1] = child;
	father->num_of_collection ++;

}

tag *findTagInCollection(tag *collection,GUID guid)
{
	tag *child;
	for (int i = 0; i < collection->num_of_collection; ++i) {
		child = collection->child[i];
		if(PQDIF_IsEqualGUID(child->element.tagElement,guid))
			return child;
	}

	return NULL;
}

void collectionFree(tag *coll)
{
	tag *child;
	for (int i = 0; i < coll->num_of_collection; ++i) {
		child = coll->child[i];
		if(child->element.typeElement == ID_ELEMENT_TYPE_COLLECTION){
			collectionFree(child);
		}else if(child->element.typeElement == ID_ELEMENT_TYPE_VECTOR){
			vectorFree(child);
		}else{
			scalarFree(child);
		}
	}

	pq_free(coll->child);

	pq_free(coll);
}
