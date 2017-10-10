/*
**  PQDIF - Power Quality Data Interchange Format
**  Version 1.6
**
**
**  LOGICAL FORMAT DEFINITIONS
**  ======================================================================
**  This file contains the complete specifications for the logical
**  format of a PQDIF file. It is based on the _physical_ structure of
**  the file, which is defined in PQDIF_PH.H
**
**  ======================================================================
**  The current version of this file and related information
**  can be found at URL:
**
**  http://grouper.ieee.org/groups/1159/3/docs.html
**
**  ======================================================================
**
**  LOGICAL HIERARCHY OF RECORDS
**  ======================================================================
**  The records that make up PQDIF are currently of four different kinds:
**  Container, Data Source, Monitor Settings, and Observation.
**
**  There are absolute links from one record to another (these are
**  different from links within a record, which are relative within the
**  record). When these links are followed, the records form a logical
**  hierarchy:
**
**    +-----------+
**    | Container |
**    +-----------+
**        |
**        |   +---------------+
**        +---| Data Source 1 |
**        |   +---------------+
**        |       |
**        |       |   +--------------------+
**        |       +---| Monitor Settings 1 |
**        |       |   +--------------------+
**        |       |       |
**        |       |       |   +---------------+
**        |       |       +---| Observation 1 |
**        |       |       |   +---------------+
**        |       |       |   +---------------+
**        |       |       +---| Observation 2 |
**        |       |       |   +---------------+
**        |       |      ...
**        |       |       |   +---------------+
**        |       |       +---| Observation n |
**        |       |           +---------------+
**        |       |
**        |       |   +--------------------+
**        |       +---| Monitor Settings 2 |
**        |       |   +--------------------+
**        |      ...
**        |       |   +--------------------+
**        |       +---| Monitor Settings n |
**        |       |   +--------------------+
**        |      ...
**        |   +---------------+
**        +---| Data Source 2 |
**        |   +---------------+
**       ...
**        |   +---------------+
**        +---| Data Source n |
**        |   +---------------+
**       ...
**
**  The first record in a PQDIF file must be of the Container type.
**  This data in this record describes attributes of the items 
**  contained within the PQDIF file.
**
**  The container record is then followed by a Data Source
**  record which can be followed by one or more Data Source
**  records or Observation records.  A Data Source record
**  describes the source of the data that is contained in the
**  Observation records that follow it.
**  
**  Note that Monitor Settings records are optional; in their absence,
**  Observation records fall directly under the appropriate
**  Data Source record.
*/
#ifndef PQDIF_LG_H
#define PQDIF_LG_H

/*
**  RECORD HEADER
**  ======================================================================
**  The first item in a PQDIF File (and in each record) is a 128 bit
**  GUID which serves as a unique signature for both the file as a whole
**  and each record.
**
**  Every record must have this GUID.
*/
const GUID guidRecordSignaturePQDIF = { /* 4a111440-e49f-11cf-9900-505144494600 */
    0x4a111440,
    0xe49f,
    0x11cf,
    {0x99, 0x00, 0x50, 0x51, 0x44, 0x49, 0x46, 0x00}
  };


/*
**  TAG FOR ANY RECORD
**  ======================================================================
**  The following tag can be used to leave space in a collection. To leave 
**  a collection item blank, specify it as a scalar of less than 8 bytes
**  (such as a UINT4), and specify it as embedded.
*/
const GUID tagBlank =  //  
    { 0x89738618, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };
    // {89738618-F1C3-11cf-9D89-0080C72E70A3}


//  ======================================================================
//  Do not modify anything after the following comment:
//  {{{{ AUTO-GENERATED CONSTANTS }}}}

//  Description:   Record-level tag which identifies the container record (always  the first one in the file, and there must be only one per file).
//  Element type:  Collection [ * ]
//  Physical type: (n/a)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagContainer = { 0x89738606, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Record-level tag which identifies a data source (an instrument, etc.).
//  Element type:  Collection [ * ]
//  Physical type: (n/a)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagRecDataSource = { 0x89738619, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Record-level tag which identifies a set of configuration parameters.
//  Element type:  Collection [ * ]
//  Physical type: (n/a)
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagRecMonitorSettings = { 0xb48d858c, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Record-level tag which identifies an observation -- an event, measurement, etc.
//  Element type:  Collection [ * ]
//  Physical type: (n/a)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagRecObservation = { 0x8973861a, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Specifies the format version for read/write compatibility. The four required numbers in the vector are described below.
//  Element type:  Vector [ 4 ]
//  Physical type: UINT4
//  Required/opt:  Required
//  Version:       1.0
const GUID tagVersionInfo = { 0x89738607, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Original name of the file.
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Required
//  Version:       1.0
const GUID tagFileName = { 0x89738608, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Date/time when the file was created.
//  Element type:  Scalar
//  Physical type: TIMESTAMP
//  Required/opt:  Required
//  Version:       1.0
const GUID tagCreation = { 0x89738609, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Date/time when the file was last saved.
//  Element type:  Scalar
//  Physical type: TIMESTAMP
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagLastSaved = { 0x8973860a, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   The number of times the file has been saved/modified.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagTimesSaved = { 0x8973860b, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   The language (English, etc.) of the file.
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagLanguage = { 0x8973860c, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Arbitrary title.
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagTitle = { 0x8973860d, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Arbitrary subject string
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagSubject = { 0x8973860e, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Individual/company who caused the file to be written
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagAuthor = { 0x8973860f, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Keywords for assisting searches
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagKeywords = { 0x89738610, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Arbitrary comments
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagComments = { 0x89738611, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Individual/company who last wrote to file
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagLastSavedBy = { 0x89738612, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Creating application
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagApplication = { 0x89738623, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Security descriptor information
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagSecurity = { 0x89738613, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Owner of file contents (This and some of the following fields are for copyright and trademark information)
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagOwner = { 0x89738614, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Copyright notice
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagCopyright = { 0x89738615, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Trademark notice
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagTrademarks = { 0x89738616, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   RTF formatted notes associated with this file (This corresponds to the IEEE COMTRADE .HDR file, for example).
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagNotes = { 0x89738617, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Specified how the compression is applied to the file.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagCompressionStyleID = { 0x8973861b, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Required if tagCompressionStyleID specifies that compression is turned on.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagCompressionAlgorithmID = { 0x8973861c, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   If compression style is _TOTALFILE, this is the checksum for the entire file. This feature has been deprecated under 1.5.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.5 Deprecated
const GUID tagCompressionChecksum = { 0x8973861d, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   General contact information (all optional)
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagName = { 0xb48d85a2, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   General contact information (all optional)
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagAddress1 = { 0xb48d85a3, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   General contact information (all optional)
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagAddress2 = { 0xb48d85a4, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   General contact information (all optional)
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagCity = { 0xb48d85a5, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   General contact information (all optional)
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagState = { 0xb48d85a6, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   General contact information (all optional)
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagPostalCode = { 0xb48d85a7, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   General contact information (all optional)
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagCountry = { 0xb48d85a8, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   General contact information (all optional)
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagPhoneVoice = { 0xb48d85a9, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   General contact information (all optional)
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagPhoneFAX = { 0x3d786f80, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   General contact information (all optional)
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagEMail = { 0x3d786f81, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Since this ID is a GUID, you can generate a custom ID if a standard ID is not defined.
//  Element type:  Scalar
//  Physical type: GUID
//  Required/opt:  Required
//  Version:       1.0
const GUID tagDataSourceTypeID = { 0xb48d8581, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Since this ID is a GUID, you can generate a custom ID if a standard ID is not defined.
//  Element type:  Scalar
//  Physical type: GUID
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagVendorID = { 0xb48d8582, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Since this ID is a GUID, you can generate a custom ID if a standard ID is not defined.
//  Element type:  Scalar
//  Physical type: GUID
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagEquipmentID = { 0xb48d8583, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   This collection can include the standard name, address & telephone number tags -- these apply to the vendor -- as well as tags about the instrument itself.
//  Element type:  Collection
//  Physical type: (n/a)
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagCustomSourceInfo = { 0xb48d8584, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Arbitrary string to hold data souce (instrument) serial number
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagSerialNumberDS = { 0xb48d8585, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Arbitrary string to hold data souce (instrument) version number (if applicable)
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagVersionDS = { 0xb48d8586, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Arbitrary string to hold the name of the data souce (instrument)
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Required
//  Version:       1.0
const GUID tagNameDS = { 0xb48d8587, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Arbitrary string to hold data souce (instrument) owner name
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagOwnerDS = { 0xb48d8588, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Arbitrary string to hold data souce (instrument) location information
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagLocationDS = { 0xb48d8589, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   EST, CST, etc.
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagTimeZoneDS = { 0xb48d858a, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Longitude/latitude
//  Element type:  Vector [ 2 ]
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagCoordinatesDS = { 0xb48d858b, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   The tagChannelDefns collection must be a collection where the count = the number of channel definitions. Each entry must be another collection, each having the tagOneChannelDefn tag.
//  Element type:  Collection [ # defs ]
//  Physical type: (n/a)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagChannelDefns = { 0xb48d858d, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Element type:  Scalar
//  Physical type: GUID
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagInstrumentTypeID = { 0x3d786f82, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Arbitrary string
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagInstrumentModelName = { 0x3d786f83, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Arbitrary string
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagInstrumentModelNumber = { 0x3d786f84, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Must have one or more channel definitions
//  Element type:  Collection [ * ]
//  Physical type: (n/a)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagOneChannelDefn = { 0xb48d858e, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Arbitrary string
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagChannelName = { 0xb48d8590, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Phase identifier
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Required
//  Version:       1.0
const GUID tagPhaseID = { 0xb48d8591, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Arbitrary string
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagOtherChannelIdentifier = { 0xb48d8593, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   This tag can be repeated if there are multiple groupings. The first one should be the highest-level group (example: a bus), and the next one should be a lower group (example: a feeder).
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagGroupName = { 0xb48d8594, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   The high-level description of the type of quantity which is being captured by this channel. In order to guarantee reader compatibility, the following series value types (in order) should be used (ID_SERIES_VALUE_TYPE_VAL, etc.).
//  Element type:  Scalar
//  Physical type: GUID
//  Required/opt:  Required
//  Version:       1.0
const GUID tagQuantityTypeID = { 0xb48d8592, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Identifies the physical quantity under measurement -- Voltage, Current, Power, etc. In general, there is a one-to-one correspondence between this and the units of the series, but not always.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Required
//  Version:       1.5
const GUID tagQuantityMeasuredID = { 0xc690e872, 0xf755, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   The instrument physical channel that this channel definition is associated with.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagPhysicalChannel = { 0x89738622, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Additional quantity information.
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagQuantityName = { 0xb48d8595, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Identifies the series which will be the primary. Index into the tagSeriesDefns collection.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagPrimarySeriesIdx = { 0xb48d8596, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   The tagSeriesDefns collection must be a collection where the count = the number of series definitions. Each entry must be another collection, each having the tagOneSeriesDefn tag.
//  Element type:  Collection [ # sers ]
//  Physical type: (n/a)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagSeriesDefns = { 0xb48d8598, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   One of these collections per series.
//  Element type:  Collection [ * ]
//  Physical type: (n/a)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagOneSeriesDefn = { 0xb48d859a, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   This specifies the meaning of the series data.
//  Element type:  Scalar
//  Physical type: GUID
//  Required/opt:  Required
//  Version:       1.0
const GUID tagValueTypeID = { 0xb48d859c, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   This specifies the units of the data in this series. The expected physical type for the tagSeriesValues vector is REAL4 or REAL8 (except as noted).
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Required
//  Version:       1.0
const GUID tagQuantityUnitsID = { 0xb48d859b, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   This specifies additional detail about the meaning of the series data.
//  Element type:  Scalar
//  Physical type: GUID
//  Required/opt:  Required
//  Version:       1.5
const GUID tagQuantityCharacteristicID = { 0x3d786f9e, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Defines the number of significant digits in the data represented by this series.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagQuantitySignificantDigitsID = { 0xa112f421, 0xb111, 0x11d2, { 0x9b, 0x37, 0x0, 0x40, 0x5, 0x2c, 0x2d, 0x28 } };

//  Description:   Contains a double indicating the scaled distance between two values of the quantity represented by this series (e.g. scaled A/D resolution)
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagQuantityResolutionID = { 0xfb228ee0, 0xfc8d, 0x11d2, { 0xb4, 0x9a, 0x0, 0x60, 0x8, 0xb3, 0x71, 0x83 } };

//  Description:   The legal values for this entry are masks, since they are OR-able.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Required
//  Version:       1.0
const GUID tagStorageMethodID = { 0xb48d85a1, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Arbitrary string
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagValueTypeName = { 0xb48d859d, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagHintGreekPrefixID = { 0xb48d859e, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagHintPreferredUnitsID = { 0xb48d859f, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagHintDefaultDisplayID = { 0xb48d85a0, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   For a probability series definition, this specifies its time interval (in seconds; >0).
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagProbInterval = { 0x2747d441, 0x2bd0, 0x11d2, { 0xae, 0x42, 0x0, 0x60, 0x8, 0x3a, 0x26, 0x28 } };

//  Description:   For a probability series definition, this specifies its probability percentile (in percent; 0-100).
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagProbPercentile = { 0x2747d440, 0x2bd0, 0x11d2, { 0xae, 0x42, 0x0, 0x60, 0x8, 0x3a, 0x26, 0x28 } };

//  Description:   Contains the default nominal base voltage or any or any other necessary normalizing quantity.  Display programs may use this value or the tagSeriesBaseQuantity in the series instance for displaying data in percent or per unit.
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagSeriesNominalQuantity = { 0xfa118c8, 0xcb4a, 0x11d2, { 0xb3, 0xb, 0xfe, 0x25, 0xcb, 0x9a, 0x17, 0x60 } };

//  Description:   The time that these settings become effective.
//  Element type:  Scalar
//  Physical type: TIMESTAMP
//  Required/opt:  Required
//  Version:       1.0
const GUID tagEffective = { 0x62f28183, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Element type:  Scalar
//  Physical type: TIMESTAMP
//  Required/opt:  Required
//  Version:       1.0
const GUID tagTimeInstalled = { 0x3d786f85, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Element type:  Scalar
//  Physical type: TIMESTAMP
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagTimeRemoved = { 0x3d786f86, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   If TRUE, the calibration adjustments *must* be applied to the series data before using. Otherwise the data is for informative use only.
//  Element type:  Scalar
//  Physical type: BOOL4
//  Required/opt:  Required
//  Version:       1.0
const GUID tagUseCalibration = { 0x62f28180, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   If TRUE, the transducer adjustments *must* be applied to the series data before using. Otherwise the data is for informative use only.
//  Element type:  Scalar
//  Physical type: BOOL4
//  Required/opt:  Required
//  Version:       1.0
const GUID tagUseTransducer = { 0x62f28181, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Channel specific monitor settings stuff
//  Element type:  Collection [ # chan ]
//  Physical type: (n/a)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagChannelSettingsArray = { 0x62f28182, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Nominal power system frequency for this instrument in Hertz
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagNominalFrequency = { 0xfa118c3, 0xcb4a, 0x11d2, { 0xb3, 0xb, 0xfe, 0x25, 0xcb, 0x9a, 0x17, 0x60 } };

//  Description:   Identifies the physical connection of the instrumentation or insturment transducers.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagSettingPhysicalConnection = { 0x9f256ee0, 0x803b, 0x11d3, { 0xb9, 0x2f, 0x0, 0x50, 0xda, 0x2b, 0x1f, 0x4d } };

//  Description:   One of these collections per channel.
//  Element type:  Collection [ * ]
//  Physical type: (n/a)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagOneChannelSetting = { 0x3d786f9a, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   The channel definition which these settings apply to. Index into tagChannelDefns collection of the matching data source record.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Required
//  Version:       1.0
const GUID tagChannelDefnIdx = { 0xb48d858f, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Integer ID representing which trigger fields are used.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagTriggerTypeID = { 0x62f28184, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Full scale range for this instrument channel
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagFullScale = { 0x3d786f87, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Noise floor for this instrument channel
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagNoiseFloor = { 0x3d786f89, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Parameters for shape based triggering algorithms for this channel
//  Element type:  Vector [ 3 ]
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagTriggerShapeParam = { 0x62f28188, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   PT or CT
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagXDTransformerTypeID = { 0x62f28189, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   System side part of ratio
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagXDSystemSideRatio = { 0x62f2818a, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Monitor side part of ratio
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagXDMonitorSideRatio = { 0x62f2818b, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Transducer frequency response
//  Element type:  Vector [ # freq ]
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagXDFrequencyResponse = { 0x62f2818c, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Chanel time skew
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagCalTimeSkew = { 0x62f2818d, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Channel DC offset error
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagCalOffset = { 0x62f2818e, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Channel ratio error
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagCalRatio = { 0x62f2818f, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Flag indicating that the applied/recordedt calibration arrays must be used to correct data.
//  Element type:  Scalar
//  Physical type: BOOL4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagCalMustUseARCal = { 0x62f28190, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Array of applied signals for this channel
//  Element type:  Vector [ # cal ]
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagCalApplied = { 0x62f28191, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Array of recorded actual values for the applied signal
//  Element type:  Vector [ # cal ]
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagCalRecorded = { 0x62f28192, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   High High trigger for this channel
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagTriggerHighHigh = { 0x5b12f431, 0xff54, 0x11d3, { 0xb9, 0x68, 0x0, 0x50, 0xda, 0x2b, 0x1f, 0x4d } };

//  Description:   High trigger for this channel
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagTriggerHigh = { 0x62f28186, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Low trigger for this channel
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagTriggerLow = { 0x62f28185, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Low Low trigger for this channel
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagTriggerLowLow = { 0x5b12f430, 0xff54, 0x11d3, { 0xb9, 0x68, 0x0, 0x50, 0xda, 0x2b, 0x1f, 0x4d } };

//  Description:   Deadband trigger for this channel
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagTriggerDeadBand = { 0x5b12f432, 0xff54, 0x11d3, { 0xb9, 0x68, 0x0, 0x50, 0xda, 0x2b, 0x1f, 0x4d } };

//  Description:   Rate of change trigger for this channel
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagTriggerRate = { 0x62f28187, 0xf9c4, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Name of the observation
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Required
//  Version:       1.0
const GUID tagObservationName = { 0x3d786f8a, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Time this observation was created
//  Element type:  Scalar
//  Physical type: TIMESTAMP
//  Required/opt:  Required
//  Version:       1.0
const GUID tagTimeCreate = { 0x3d786f8b, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   The start time of the observation -- the zero point where the .
//  Element type:  Scalar
//  Physical type: TIMESTAMP
//  Required/opt:  Required
//  Version:       1.0
const GUID tagTimeStart = { 0x3d786f8c, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Type of trigger which caused the observation.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Required
//  Version:       1.0
const GUID tagTriggerMethodID = { 0x3d786f8d, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Tme this observation was triggered if appropriate
//  Element type:  Scalar
//  Physical type: TIMESTAMP
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagTimeTriggered = { 0x3d786f8e, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Index into tagChannelInstances collection within this record. This specifies which channel(s) initiated the observation.
//  Element type:  Vector
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagChannelTriggerIdx = { 0x3d786f8f, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   The serial number of the observation (if generated by an instrument, for example).
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagObservationSerial = { 0x3d786f90, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Serial number -- of specific cycle, for example -- that can be used to correlate observations.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagObservationAggregationSerial = { 0x89738621, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Currently uses the IEEE 1159 disturbance categories, but others could be used as well.
//  Element type:  Scalar
//  Physical type: GUID
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagDisturbanceCategoryID = { 0xb48d8597, 0xf5f5, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   This collection contains a set of channel instances. It is not required to contain the same number of channels as there are channel instances. This can be determined on an observation-by-observation basis.
//  Element type:  Collection [ # chan ]
//  Physical type: (n/a)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagChannelInstances = { 0x3d786f91, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Direction of disturbance represented by the data in this observation.  Value of 0 means don't know, 1 means originated from load side, 2 means originated from source side.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagCharactDisturbDirection = { 0xfa118c0, 0xcb4a, 0x11d2, { 0xb3, 0xb, 0xfe, 0x25, 0xcb, 0x9a, 0x17, 0x60 } };

//  Description:   Quality of the direction result given in another tag.  Range is from 0 (no confidence), to 100 (darn sure).
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagCharactDisturbDirectionQuality = { 0xfa118c1, 0xcb4a, 0x11d2, { 0xb3, 0xb, 0xfe, 0x25, 0xcb, 0x9a, 0x17, 0x60 } };

//  Description:   One of these collections per channel instance.
//  Element type:  Collection [ * ]
//  Physical type: (n/a)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagOneChannelInst = { 0x3d786f92, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Simple characterization value: duration of disturbance (seconds)
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagCharactDuration = { 0x2747d444, 0x2bd0, 0x11d2, { 0xae, 0x42, 0x0, 0x60, 0x8, 0x3a, 0x26, 0x28 } };

//  Description:   This collection must contain the exact number of series which were defined for the specified channel definition.
//  Element type:  Collection [ # sers ]
//  Physical type: (n/a)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagSeriesInstances = { 0x3d786f93, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Simple characterization value: magnitude of disturbance (percent: 100%=nominal)
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagCharactMagnitude = { 0x2747d443, 0x2bd0, 0x11d2, { 0xae, 0x42, 0x0, 0x60, 0x8, 0x3a, 0x26, 0x28 } };

//  Description:   Simple characterization value: frequency (Hertz)
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagCharactFrequency = { 0x2747d445, 0x2bd0, 0x11d2, { 0xae, 0x42, 0x0, 0x60, 0x8, 0x3a, 0x26, 0x28 } };

//  Description:   Contains a 32 bit integer that represents module spefic information related to the trigger reason.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagChanTriggerModuleInfo = { 0xfa118c7, 0xcb4a, 0x11d2, { 0xb3, 0xb, 0xfe, 0x25, 0xcb, 0x9a, 0x17, 0x60 } };

//  Description:   Contains the name of a device specific code or hardware module, algorithm or rule not necessarily channel based that caused this channel to be recorded
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagChanTriggerModuleName = { 0xfa118c6, 0xcb4a, 0x11d2, { 0xb3, 0xb, 0xfe, 0x25, 0xcb, 0x9a, 0x17, 0x60 } };

//  Description:   Contains the name of the device involved in an external cross trigger scenario.
//  Element type:  Vector [ * ]
//  Physical type: CHAR1
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagCrossTriggerDeviceName = { 0xfa118c5, 0xcb4a, 0x11d2, { 0xb3, 0xb, 0xfe, 0x25, 0xcb, 0x9a, 0x17, 0x60 } };

//  Description:   Contains the channel definition index of the channel that triggered in a cross trigger scenrio.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagCrossTriggerChanIdx = { 0xfa118c4, 0xcb4a, 0x11d2, { 0xb3, 0xb, 0xfe, 0x25, 0xcb, 0x9a, 0x17, 0x60 } };

//  Description:   Integer ID representing the trigger type for this channel instance.  Used only with type ID_QT_VALUELOG wit a trigger method of channel.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagChanTriggerTypeID = { 0xfa118c2, 0xcb4a, 0x11d2, { 0xb3, 0xb, 0xfe, 0x25, 0xcb, 0x9a, 0x17, 0x60 } };

//  Description:   For a channel which contains multiple instances to represent a sparse log of time-stamped frequency-domain information, this specifies the frequency for which this channel instance applies (in Hertz).  If not present, the channel characteristics are frequency independent unless further specified by the quantity characteristic.
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagChannelFrequency = { 0x2747d442, 0x2bd0, 0x11d2, { 0xae, 0x42, 0x0, 0x60, 0x8, 0x3a, 0x26, 0x28 } };

//  Description:   For a channel which contains multiple instances to represent a sparse log of time-stamped frequency-domain information, this specifies the frequency for which this channel instance applies (in Index).  The index referes to a harmonic or interharmonic group index.
//  Element type:  Scalar
//  Physical type: INT2
//  Required/opt:  Optional
//  Version:       1.5
const GUID tagChannelGroupID = { 0xf90de218, 0xe67b, 0x4cf1, { 0xa2, 0x95, 0xb0, 0x21, 0xa2, 0xd4, 0x67, 0x67 } };

//  Description:   One of these collections per series instance.
//  Element type:  Collection [ * ]
//  Physical type: (n/a)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagOneSeriesInstance = { 0x3d786f94, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Contains the nominal base voltage, or any other necessary normalizing quantity.
//  Element type:  Scalar
//  Physical type: REAL8
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagSeriesBaseQuantity = { 0x3d786f95, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   If not present, assumed to be 1. The physical type should match that of tagSeriesValues.
//  Element type:  Scalar
//  Physical type: (any type)
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagSeriesScale = { 0x3d786f96, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   If not present, assumed to be 0. Generally used as a starting point when the ID_SERIES_METHOD_INCREMENT storage method is used. The physical type should match that of tagSeriesValues.
//  Element type:  Scalar
//  Physical type: (any type)
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagSeriesOffset = { 0x3d786f97, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Identifies the channel which owns the series to be shared. An index into the tagChannelInstances collection.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagSeriesShareChannelIdx = { 0x8973861f, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Identifies the series to be shared. An index into the tagSeriesInstances collection. The tagSeriesValues vector from this series is used. This must be present if tagSeriesShareChannelIdx is used.
//  Element type:  Scalar
//  Physical type: UINT4
//  Required/opt:  Optional
//  Version:       1.0
const GUID tagSeriesShareSeriesIdx = { 0x89738620, 0xf1c3, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };

//  Description:   Contains the actual data points of the series. Required unless the data series is shared, in which case both tagSeriesShareChannelIdx and tagSeriesShareSeriesIdx should be present.
//  Element type:  Vector [ * ]
//  Physical type: (any type)
//  Required/opt:  Required
//  Version:       1.0
const GUID tagSeriesValues = { 0x3d786f99, 0xf76e, 0x11cf, { 0x9d, 0x89, 0x0, 0x80, 0xc7, 0x2e, 0x70, 0xa3 } };



#endif  //  PQDIF_LG_H


