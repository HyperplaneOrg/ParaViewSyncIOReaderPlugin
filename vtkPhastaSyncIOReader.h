/*=========================================================================

  Program:   Visualization Toolkit
  Module:    $RCSfile: vtkPhastaSyncIOReader.h,v $

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkPhastaSyncIOReader - Reader for RPI's PHASTA software
// .SECTION Description
// vtkPhastaSyncIOReader reads RPI's Scorec's PHASTA (Parallel Hierarchic
// Adaptive Stabilized Transient Analysis) dumps.  See
// http://www.scorec.rpi.edu/software_products.html or contact Scorec for
// information on PHASTA.

#ifndef __vtkPhastaSyncIOReader_h
#define __vtkPhastaSyncIOReader_h

#include "vtkUnstructuredGridAlgorithm.h"
#include "vtkPhastaSyncIOMetaReader.h"

class vtkUnstructuredGrid;
class vtkPoints;
class vtkDataSetAttributes;
class vtkInformationVector;

/////////////////////
class vtkPVXMLParser;
class vtkPhastaSyncIOReader;
//////////////////////

//BTX
struct vtkPhastaSyncIOReaderInternal;
//ETX

class VTK_EXPORT vtkPhastaSyncIOReader : public vtkUnstructuredGridAlgorithm
{
public:
  static vtkPhastaSyncIOReader *New();
  vtkTypeMacro(vtkPhastaSyncIOReader,vtkUnstructuredGridAlgorithm);
  void PrintSelf(ostream& os, vtkIndent indent);

  // Description:
  // Specify file name of Phasta geometry file to read.
  vtkSetStringMacro(GeometryFileName);
  vtkGetStringMacro(GeometryFileName);

  // Description:
  // Specify file name of Phasta field file to read.
  vtkSetStringMacro(FieldFileName);
  vtkGetStringMacro(FieldFileName);

  // Description:
  // Clear/Set info. in FieldInfoMap for object of vtkPhastaSyncIOReaderInternal
  void ClearFieldInfo();
  void SetFieldInfo(const char *paraviewFieldTag,
                    const char* phastaFieldTag,
                    int index,
                    int numOfComps,
                    int dataDependency,
                    const char* dataType);

protected:
  vtkPhastaSyncIOReader();
  ~vtkPhastaSyncIOReader();

  virtual int RequestData(vtkInformation* request,
                          vtkInformationVector** inputVector,
                          vtkInformationVector* outputVector);

  void ReadGeomFile(char *GeomFileName, 
                    int &firstVertexNo,
                    vtkPoints *points, 
                    int &noOfNodes,
                    int &noOfCells, int &ncverts, int **evm1, int **evm2 );
  void ReadFieldFile(char *fieldFileName , 
                     int firstVertexNo, 
                     vtkDataSetAttributes *field, 
                     int &noOfNodes);
  void ReadFieldFile(char *fieldFileName,
                     int firstVertexNo,
                     vtkUnstructuredGrid *output,
                     int &noOfDatas, int &ncverts, int **evm1, int **evm2 );

private:
  char *GeometryFileName;
  char *FieldFileName;

  ////////////////////
  vtkPVXMLParser* Parser;
  char* FileName;
  ///////////////////

  int NumberOfVariables; //number of variable in the field file

  static char* StringStripper( const char  istring[] );
  static int cscompare( const char teststring[], 
                        const char targetstring[] );
  static void isBinary( const char iotype[] );
  static size_t typeSize( const char typestring[] );
  //CHANGE////////////////////////////////////////////////////

  static void queryphmpiio_( const char filename[],
			     int *nfields, 
			     int *nppf );
  static void finalizephmpiio_( int *fileDescriptor );

  //CHANGE END///////////////////////////////////////////////
  static int readHeader( FILE*       fileObject,
                         const char  phrase[],
                         int*        params,
                         int         expect );
  static void SwapArrayByteOrder_( void* array, 
				   int   nbytes, 
				   int   nItems );
  static void openfile( const char filename[],
                        const char mode[],
                        int*  fileDescriptor );
  static void closefile( int* fileDescriptor, 
                         const char mode[] );
  static void readheader( int* fileDescriptor,
                          const char keyphrase[],
                          void* valueArray,
                          int*  nItems,
                          const char  datatype[],
                          const char  iotype[] );
  static void readdatablock( int*  fileDescriptor,
                             const char keyphrase[],
                             void* valueArray,
                             int*  nItems,
                             const char  datatype[],
                             const char  iotype[] );


  
  
private:
  vtkPhastaSyncIOReaderInternal *Internal;

  vtkPhastaSyncIOReader(const vtkPhastaSyncIOReader&); // Not implemented
  void operator=(const vtkPhastaSyncIOReader&); // Not implemented
};

#endif


