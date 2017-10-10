/*
 * tags.h
 *
 *  Created on: 2017Äê10ÔÂ9ÈÕ
 *      Author: zjm09
 */

#ifndef LIB_INC_TAGS_H_
#define LIB_INC_TAGS_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#include "../inc/pqdif_ph.h"

#define DEBUG	(0)
#define STATIC_COLLECTION_NUM	(0)

#define declareTag(tag)	extern const GUID tag

declareTag(tagContainer);
declareTag(tagRecDataSource);
declareTag(tagRecMonitorSettings);
declareTag(tagRecObservation);
declareTag(tagVersionInfo);
declareTag(tagFileName);
declareTag(tagCreation);
declareTag(tagLastSaved);
declareTag(tagTimesSaved);
declareTag(tagLanguage);
declareTag(tagTitle);
declareTag(tagSubject);
declareTag(tagAuthor);
declareTag(tagKeywords);
declareTag(tagComments);
declareTag(tagLastSavedBy);
declareTag(tagApplication);
declareTag(tagSecurity);
declareTag(tagOwner);
declareTag(tagCopyright);
declareTag(tagTrademarks);
declareTag(tagNotes);
declareTag(tagCompressionStyleID);
declareTag(tagCompressionAlgorithmID);
declareTag(tagCompressionChecksum);
declareTag(tagName);
declareTag(tagAddress1);
declareTag(tagAddress2);
declareTag(tagCity);
declareTag(tagState);
declareTag(tagPostalCode);
declareTag(tagCountry);
declareTag(tagPhoneVoice);
declareTag(tagPhoneFAX);
declareTag(tagEMail);
declareTag(tagDataSourceTypeID);
declareTag(tagVendorID);
declareTag(tagEquipmentID);
declareTag(tagCustomSourceInfo);
declareTag(tagSerialNumberDS);
declareTag(tagVersionDS);
declareTag(tagNameDS);
declareTag(tagOwnerDS);
declareTag(tagLocationDS);
declareTag(tagTimeZoneDS);
declareTag(tagCoordinatesDS);
declareTag(tagChannelDefns);
declareTag(tagInstrumentTypeID);
declareTag(tagInstrumentModelName);
declareTag(tagInstrumentModelNumber);
declareTag(tagOneChannelDefn);
declareTag(tagChannelName);
declareTag(tagPhaseID);
declareTag(tagOtherChannelIdentifier);
declareTag(tagGroupName);
declareTag(tagQuantityTypeID);
declareTag(tagQuantityMeasuredID);
declareTag(tagPhysicalChannel);
declareTag(tagQuantityName);
declareTag(tagPrimarySeriesIdx);
declareTag(tagSeriesDefns);
declareTag(tagOneSeriesDefn);
declareTag(tagValueTypeID);
declareTag(tagQuantityUnitsID);
declareTag(tagQuantityCharacteristicID);
declareTag(tagQuantitySignificantDigitsID);
declareTag(tagQuantityResolutionID);
declareTag(tagStorageMethodID);
declareTag(tagValueTypeName);
declareTag(tagHintGreekPrefixID);
declareTag(tagHintPreferredUnitsID);
declareTag(tagHintDefaultDisplayID);
declareTag(tagProbInterval);
declareTag(tagProbPercentile);
declareTag(tagSeriesNominalQuantity);
declareTag(tagEffective);
declareTag(tagTimeInstalled);
declareTag(tagTimeRemoved);
declareTag(tagUseCalibration);
declareTag(tagUseTransducer);
declareTag(tagChannelSettingsArray);
declareTag(tagNominalFrequency);
declareTag(tagSettingPhysicalConnection);
declareTag(tagOneChannelSetting);
declareTag(tagChannelDefnIdx);
declareTag(tagTriggerTypeID);
declareTag(tagFullScale);
declareTag(tagNoiseFloor);
declareTag(tagTriggerShapeParam);
declareTag(tagXDTransformerTypeID);
declareTag(tagXDSystemSideRatio);
declareTag(tagXDMonitorSideRatio);
declareTag(tagXDFrequencyResponse);
declareTag(tagCalTimeSkew);
declareTag(tagCalOffset);
declareTag(tagCalRatio);
declareTag(tagCalMustUseARCal);
declareTag(tagCalApplied);
declareTag(tagCalRecorded);
declareTag(tagTriggerHighHigh);
declareTag(tagTriggerHigh);
declareTag(tagTriggerLow);
declareTag(tagTriggerLowLow);
declareTag(tagTriggerDeadBand);
declareTag(tagTriggerRate);
declareTag(tagObservationName);
declareTag(tagTimeCreate);
declareTag(tagTimeStart);
declareTag(tagTriggerMethodID);
declareTag(tagTimeTriggered);
declareTag(tagChannelTriggerIdx);
declareTag(tagObservationSerial);
declareTag(tagObservationAggregationSerial);
declareTag(tagDisturbanceCategoryID);
declareTag(tagChannelInstances);
declareTag(tagCharactDisturbDirection);
declareTag(tagCharactDisturbDirectionQuality);
declareTag(tagOneChannelInst);
declareTag(tagCharactDuration);
declareTag(tagSeriesInstances);
declareTag(tagCharactMagnitude);
declareTag(tagCharactFrequency);
declareTag(tagChanTriggerModuleInfo);
declareTag(tagChanTriggerModuleName);
declareTag(tagCrossTriggerDeviceName);
declareTag(tagCrossTriggerChanIdx);
declareTag(tagChanTriggerTypeID);
declareTag(tagChannelFrequency);
declareTag(tagChannelGroupID);
declareTag(tagOneSeriesInstance);
declareTag(tagSeriesBaseQuantity);
declareTag(tagSeriesScale);
declareTag(tagSeriesOffset);
declareTag(tagSeriesShareChannelIdx);
declareTag(tagSeriesShareSeriesIdx);
declareTag(tagSeriesValues);


#if DEBUG
extern int allocCount;
#endif

#if DEBUG
#define pq_alloc(size)	calloc(1,size);allocCount++;
#define pq_free(p)	free(p);allocCount--;
#else
#define pq_alloc(size)	calloc(1,size);
#define pq_free(p)	free(p);
#endif

typedef struct __tags{
	struct __tags *next;
#if STATIC_COLLECTION_NUM
	struct __tags *child[STATIC_COLLECTION_NUM];
#else
	struct __tags **child;
	int num_of_child_is_alloc;
#endif
	GUID guid;
	int element_type;
	int phy_type;
	int data_len;
#if DEBUG
	const char *name;
#endif
	union{
		char *string;
		uint8_t *uint1;
		uint16_t *uint2;
		uint32_t *uint4;
		float *real4;
		double *real8;
		TIMESTAMPPQDIF *time;
		GUID *id;
		uint8_t data[8];
		int num_of_collection;
	};
}tag;

tag *createTagString(GUID guid,const char *str);
tag *createTagCollection(GUID guid,int num_of_child_is_alloc);
tag *createTagScalar(GUID guid,int phy,void *vector);
tag *createTagVector(GUID guid,int phy,void *vector,size_t vector_len);
tag *createTagTimestamp(GUID guid,struct timespec s);
tag *createTagGUID(GUID guid,GUID v);
void collectionAdd(tag *father,tag *child);
tag *findTagInCollection(tag *collection,GUID guid);
void collectionFree(tag *coll);
void vectorFree(tag *p);
void scalarFree(tag *p);

#endif /* LIB_INC_TAGS_H_ */
