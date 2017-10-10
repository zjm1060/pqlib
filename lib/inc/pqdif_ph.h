/*
**  PQDIF - Power Quality Data Interchange Format
**  Version 1.6
**
**  PHYSICAL FORMAT DEFINITIONS
**  ======================================================================
**  This file contains the complete definitions for the physical
**  format of a PQDIF file. It contains no information about the
**  _logical_ structure, which is defined in PQDIF_LG.H
**  
**  ======================================================================
**  The current version of this file and related information
**  can be found at URL:
**
**  http://grouper.ieee.org/groups/1159/3/docs.html
**  
**  ======================================================================
*/
#ifndef PQDIF_PH_H
#define PQDIF_PH_H


//  The structures must be 1-byte packed.
#ifdef __BORLANDC__
    #pragma pack( 1 )
#elif _MSC_VER
    #pragma pack( push, 1 )
#else
    #pragma pack( 1 )
#endif


/*
**  PHYSICAL TYPE IDs AND DEFINITIONS
**  ======================================================================
**  The physical types are intended to be fully portable. 
**  ======================================================================
*/

/*
**  Physical representation IDs
**
**  NOTE:   Larger objects such as strings and BLOBs (Binary Large OBject)
**          are represented as vectors of other primitive types.
**
**  Examples
**  --------
**      ASCII string    Vector of ID_PHYS_TYPE_CHAR1, NULL-terminated
**                      (i.e., the last character must be a NULL, to 
**                      correspond to a C-style string).
**
**      Unicode string  Vector of ID_PHYS_TYPE_CHAR2.
**
**      BLOB            vector of ID_PHYS_TYPE_INTEGER1 or
**                      ID_PHYS_TYPE_UNS_INTEGER1.
*/
#define ID_PHYS_TYPE_BOOLEAN1           1
#define ID_PHYS_TYPE_BOOLEAN2           2
#define ID_PHYS_TYPE_BOOLEAN4           3

#define ID_PHYS_TYPE_CHAR1              10  //  ASCII
#define ID_PHYS_TYPE_CHAR2              11  //  Unicode

//  Signed integers
#define ID_PHYS_TYPE_INTEGER1           20
#define ID_PHYS_TYPE_INTEGER2           21
#define ID_PHYS_TYPE_INTEGER4           22

//  Unsigned integers
#define ID_PHYS_TYPE_UNS_INTEGER1       30
#define ID_PHYS_TYPE_UNS_INTEGER2       31
#define ID_PHYS_TYPE_UNS_INTEGER4       32

//  Real/complex
#define ID_PHYS_TYPE_REAL4              40
#define ID_PHYS_TYPE_REAL8              41
#define ID_PHYS_TYPE_COMPLEX8           42  //  Two REAL4s: real, imag
#define ID_PHYS_TYPE_COMPLEX16          43  //  Two REAL8s: real, imag

//  Date/time variations
#define ID_PHYS_TYPE_TIMESTAMPPQDIF     50  //  Physical: TIMESTAMPPQDIF (total 12 bytes)

//  GUID
#define ID_PHYS_TYPE_GUID               60  //  Physical: GUID (total 16 bytes)


/*
**  Portable primitive type definitions
*/
typedef char            BOOL1;
typedef short           BOOL2;
typedef long            BOOL4;

typedef char            CHAR1;  //  ASCII string character
typedef short           CHAR2;  //  Unicode string character

typedef char            INT1;
typedef short           INT2;
typedef long            INT4;

typedef unsigned char   UINT1;
typedef unsigned short  UINT2;
typedef unsigned long   UINT4;

typedef float           REAL4;
typedef double          REAL8;

typedef struct _complex8
    {
    REAL4   real;
    REAL4   image;
    } COMPLEX8;

typedef struct _complex16
    {
    REAL8   real;
    REAL8   image;
    } COMPLEX16;

/*
**  Types used in structures (but not used as primitives for elements)
*/
typedef long            LINKABS4;
typedef long            LINKREL4;
typedef long            SIZE4;


/*
**  Portable physical time structure definition
**
**  (Modified version of time tracking used by Excel
**  Excel counts days since 1900, converts to a double
**  and adds to this a number less than 1.0 that
**  is the fractional day.  This structure enhances
**  accuracy of this method by separating out the
**  days since 1900 and seconds since midnight.)
*/
typedef struct ts
    {
    UINT4   day;        //  days since January 1, 1900 UCT
                        //  0xFFFFFFFF -> 4294967295 days -> a long time
    REAL8   sec;        //  fractional seconds since midnight of day
    } TIMESTAMPPQDIF;


/*
**  GUID (Globally Unique IDentifier) definition
**  (Used for tagging sections to identify them logically)
**
**  The Unique Universal Identifier (UUID) is also known
**  as a Globally Unique Identifier (GUID).  It is
**  a randomly generated number that due to its size,
**  is guaranteed to be unique in the universe.  This
**  guarantees that the tags will be unique and anyone
**  can generate "private" tags which will never conflict
**  with the standard tags.
**
**  GUID tags are used to mark the header of each record,
**  as well as identify the elements in the internal structures.
*/
#ifndef GUID_DEFINED
#define GUID_DEFINED
typedef struct _GUID
    {
    unsigned long  Data1;
    unsigned short Data2;
    unsigned short Data3;
    unsigned char  Data4[8];
    } GUID;
#endif /* GUID_DEFINED */


/*
**  PHYSICAL TYPE HELPER INFORMATION
**  ======================================================================
**  Time structure helpers
**
**  The following constant is the number of days between
**  1/1/1900 and 1/1/1970.  This is used to convert between
**  "C Time" and Excel style day counts
**  "C Time" is a 4 byte integer representing the number of
**  seconds elapsed since  January 1, 1970.
**  Excel time is an 8 byte real number that represents
**  the number of days elapsed since 1/1/1900.  The fractional
**  part is therefore convertable to seconds since midnight.
*/
#define EXCEL_DAYCOUNT_ADJUST   25569L
#define SECONDS_PER_DAY         86400L


/*
**  Define GUID helpers
*/
#define PQDIF_IsEqualGUID(rguid1, rguid2) (!memcmp(&rguid1, &rguid2, sizeof(GUID)))
#define PQDIF_DEFINE_GUID(name, l, w1, w2, b1, b2, b3, b4, b5, b6, b7, b8) \
        const GUID name = { l, w1, w2, { b1, b2,  b3,  b4,  b5,  b6,  b7,  b8 } }



/*
**  HIGH-LEVEL FILE STRUCTURE
**  ======================================================================
**  The top-level structure is a series of independent records with
**  header and body sections.
**
**  ======================================================================
**  Fundamental premise for file format writing: File must be capable of
**  being written to incrementally. For this reason, the basic structure
**  is a series of independent records. Additional records can be appended
**  to the file at any time.
**
**  ======================================================================
**  The top-level structure is a series of independent records with
**  header and body sections:
**  
**      +--------------------------------+
**      | Record 0 Header                |
**  /---+--------------------------------+
**  |   | Record 0 Body                  |
**  |   +--------------------------------+
**  \-->+--------------------------------+
**      | Record 1 Header                |
**  /---+--------------------------------+
**  |   | Record 1 Body                  |
**  |   +--------------------------------+
** ... ...
**  \-->+--------------------------------+
**      | Record n Header                |
**      +--------------------------------+
**      | Record n Body                  |
**      +--------------------------------+
**  
**  ======================================================================
**  Note that each record header has a LINKABS4 -- an absolute offset in
**  the file -- to the next record. This allows new records to be inserted
**  in the middle of the file, and obsolete records to be deleted.
**
**  ======================================================================
**  All references which are defined by the type LINKREL4 are offsets 
**  within the record body itself -- they are not absolute offsets to the 
**  entire file. Thus, each record body is independent of the others. Only
**  the record header need be modified if a record is moved, deleted, or
**  inserted.
**
**  ======================================================================
*/


/*
**  Record header
**
**  The header contains a GUID signature (for testing corruptness), 
**  header size, the size of the record that follows, record tag, and
**  fill bytes to make the header 64 bytes in length
*/
struct c_record_mainheader
    {
    GUID        guidRecordSignature;    //  Signature to verify a valid header

    GUID        tagRecordType;          //  Tag to identify the record type
                                        //  (This also identifies the first
                                        //  collection in the record.)

    SIZE4       sizeHeader;             //  Size of this header in bytes

    SIZE4       sizeData;               //  Size of the body in bytes (record data 
                                        //  that follows header)

    LINKABS4    linkNextRecord;         //  Offset to the next record -- absolute 
                                        //  reference within the file. If 0, this 
                                        //  is the last record in the file.

    UINT4       checksum;               //  Optional checksum (such as a 32-bit CRC)
                                        //  of the record body to verify decompression.

    UINT4       auiReserved[ 4 ];       //  Reserved to fill structure to 64 bytes
                                        //  -- should be filled with 0
    };



/*
**  RECORD BODY STRUCTURE
**  ======================================================================
**  The record body always begins with a Collection element. This is
**  defined below in the record structure. 
**  
**  ======================================================================
**  The fundamental premise for the standard structures is to
**  assure 4 byte alignment. All of the structures conform to this 
**  premise. In addition, the data values associated with scalars and
**  vectors must be padded out to 4-byte multiples. This _total_ size
**  will be specified in the c_collection_element structure (sizeElement).
**
**  ======================================================================
**  The three main elements are:
**
**      1. Collection   Holds an array of pointers to other elements
**                      (it could contain another collection)
**      2. Scalar       Holds a single data value (of a physical type)
**      3. Vector       Holds an array of data values (of a physical type)
**  ======================================================================
*/

#define ID_ELEMENT_TYPE_COLLECTION  1
#define ID_ELEMENT_TYPE_SCALAR      2
#define ID_ELEMENT_TYPE_VECTOR      3


/*
**  The collection element
**
**  ... is made by combining a c_collection with an array of 
**  c_collection_element, which provide pointers to the
**  other elements in the collection.
*/
struct c_collection
    {
    SIZE4                   count;          //  The number of elements in this
                                            //  collection.

//  c_collection_element    ceElements[];   //  Array [count] of the elements
                                            //  in the collection.
    };

struct c_collection_element
    {
    GUID        tagElement;     //  Identifier for this element in the collection.

    //  (4) 1-byte members keep the structure 4-byte aligned.
    INT1        typeElement;    //  Type of element (ID_ELEMENT_TYPE_COLLECTION, 
                                //  _SCALAR or _VECTOR).

    INT1        typePhysical;   //  Physical type of the value which follows
                                //  (ID_PHYS_TYPE_INTEGER1, etc.). This is unused
                                //  if the element is a collection and should be
                                //  set to 0.

    BOOL1       isEmbedded;     //  FALSE (0) - use the link to find the next element
                                //  TRUE  (1) - the scalar data value is embedded
                                //              (may not be used with vectors)

    INT1        reserved;       //  Fill with 0

    //  The following 8 bytes can point to another location in the record
    //  or it can hold the actual data value (if it fits in 8 bytes).
    //  This allows small scalars to be stored with much less space overhead.
    union
        {
        //  isEmbedded  What to use
        //  ----------  -------------------------------------------------
        //  FALSE       Use link to find the next element (and its size).
        //  TRUE        Use valueEmbedded to find the data directly.
        struct
            {
            LINKREL4    linkElement;    //  Offset to the element -- this offset
                                        //  is relative within the record body.

            SIZE4       sizeElement;    //  Specifies actual size of the element
                                        //  -- should be padded to even
                                        //  multiples of 4 bytes
            } link;

        UINT1       valueEmbedded[ 8 ]; //  The scalar data value
                                        //  (less than or equal to 8 bytes)
        };
    };


/*
**  The scalar element
**
**  This structure has no members, but is included
**  for completeness.
**
**      struct c_scalar
**          {
**      //  (type)      value;          //  A single value follows of variable length, 
**                                      //  depending on the physical type.
**          };
*/

/*
**  The vector element
*/
struct c_vector
    {
    SIZE4       count;
//  (type)      values[];       //  An array of values [count] follows of 
                                //  variable length, depending on the 
                                //  physical type.
    };


/*
**  NOTE
**  ======================================================================
**  For more detailed information about how to use these physical 
**  structures to create a PQDIF file, see the logical structure header
**  file -- PQDIF_LG.H
*/

//  Return to previous packing value
#ifdef __BORLANDC__
  #include <poppack.h>
#elif _MSC_VER
    #pragma pack( pop )
#else
    #pragma pack()
#endif

#endif  //  PQDIF_PH_H
