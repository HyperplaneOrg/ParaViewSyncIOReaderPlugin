/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkPhastaReaderDev.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
// .NAME vtkPhastaReaderDev - Reader for RPI's PHASTA software
// .SECTION Description
// vtkPhastaReaderDev reads RPI's Scorec's PHASTA (Parallel Hierarchic
// Adaptive Stabilized Transient Analysis) dumps.  See
// http://www.scorec.rpi.edu/software_products.html or contact Scorec for
// information on PHASTA.

#ifndef __vtkPhastaReaderDev_h
#define __vtkPhastaReaderDev_h

#include "vtkPVVTKExtensionsDefaultModule.h" //needed for exports
#include "vtkUnstructuredGridAlgorithm.h"

class vtkUnstructuredGrid;
class vtkPoints;
class vtkDataSetAttributes;
class vtkInformationVector;

//BTX
struct vtkPhastaReaderDevInternal;
//ETX

class VTKPVVTKEXTENSIONSDEFAULT_EXPORT vtkPhastaReaderDev : public vtkUnstructuredGridAlgorithm
{
public:
  static vtkPhastaReaderDev *New();
  vtkTypeMacro(vtkPhastaReaderDev,vtkUnstructuredGridAlgorithm);
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
  // Clear/Set info. in FieldInfoMap for object of vtkPhastaReaderDevInternal
  void ClearFieldInfo();
  void SetFieldInfo(const char *paraviewFieldTag,
                    const char* phastaFieldTag,
                    int index,
                    int numOfComps,
                    int dataDependency,
                    const char* dataType);

  void SetCachedGrid(vtkUnstructuredGrid*);
  vtkGetObjectMacro(CachedGrid, vtkUnstructuredGrid);

protected:
  vtkPhastaReaderDev();
  ~vtkPhastaReaderDev();

  virtual int RequestData(vtkInformation* request,
                          vtkInformationVector** inputVector,
                          vtkInformationVector* outputVector);

  void ReadGeomFile(char *GeomFileName, 
                    int &firstVertexNo,
                    vtkPoints *points, 
                    int &noOfNodes,
                    int &noOfCells);
  void ReadFieldFile(char *fieldFileName , 
                     int firstVertexNo, 
                     vtkDataSetAttributes *field, 
                     int &noOfNodes);
  void ReadFieldFile(char *fieldFileName,
                     int firstVertexNo,
                     vtkUnstructuredGrid *output,
                     int &noOfDatas);

private:
  char *GeometryFileName;
  char *FieldFileName;
  vtkUnstructuredGrid* CachedGrid;

  int NumberOfVariables; //number of variable in the field file

  static char* StringStripper( const char  istring[] );
  static int cscompare( const char teststring[], 
                        const char targetstring[] );
  static void isBinary( const char iotype[] );
  static size_t typeSize( const char typestring[] );
  static int readHeader( FILE*       fileObject,
                         const char  phrase[],
                         int*        params,
                         int         expect );
  static void SwapArrayByteOrder( void* array, 
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
  vtkPhastaReaderDevInternal *Internal;

  vtkPhastaReaderDev(const vtkPhastaReaderDev&); // Not implemented
  void operator=(const vtkPhastaReaderDev&); // Not implemented
};

#endif


