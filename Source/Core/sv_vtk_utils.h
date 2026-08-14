/* Copyright (c) Stanford University, The Regents of the University of
 *               California, and others.
 *
 * All Rights Reserved.
 *
 * See Copyright-SimVascular.txt for additional details.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SV_VTK_UTILS_H
#define SV_VTK_UTILS_H

#include <vtkPolyData.h>
#include <vtkUnstructuredGrid.h>

#include "vtkSVCoreModule.h"

int VTKSVCORE_EXPORT VtkUtils_NewVtkPolyData(vtkPolyData **pd, int numPts,
                                             double pts[], int numCells,
                                             vtkIdType polys[]);

int VTKSVCORE_EXPORT VtkUtils_NewVtkPolyDataLines(vtkPolyData **pd, int numPts,
                                                  double pts[], int numLines,
                                                  vtkIdType lines[]);

// What I'd like to do in FixTopology is clean up the vtkPolyData *pd
// in-place, returning the modified structure to the caller in pd.
// But it's UTTERLY unclear to me how to make changes to the point
// list in vtkPolyData.  MAYBE what I should do is make a new
// vtkCellArray to use as vtkPolyData::Verts, and then make new Lines
// and Polys which use indices into that new Verts array.  This does
// NOT seem like it would actually DELETE any of the redundant points
// that we're trying to get rid of in the vtkPoints member inherited
// from the vtkPointSet parent class.  But it WOULD eliminate
// references to those redundant points by the topology.  And
// actually, Verts does not seem to be important.  So just keep the
// same (potentially redundant) point set, and just change the id's
// that get used by Lines and Polys.

vtkSmartPointer<vtkUnstructuredGrid> VTKSVCORE_EXPORT
VtkUtils_ThresholdUgrid(const double lower, const double upper,
                        const std::string &data_name, vtkDataObject *vtk_data);

vtkSmartPointer<vtkPolyData> VTKSVCORE_EXPORT
VtkUtils_ThresholdSurface(const double lower, const double upper,
                          const std::string &data_name,
                          vtkDataObject *vtk_data);

int VTKSVCORE_EXPORT VtkUtils_FixTopology(vtkPolyData *pd, double tol);

int VTKSVCORE_EXPORT VtkUtils_GetPoints(vtkPolyData *pd, double **pts,
                                        int *numPts);

int VTKSVCORE_EXPORT VtkUtils_GetPointsFloat(vtkPolyData *pd, double **pts,
                                             int *numPts);

int VTKSVCORE_EXPORT VtkUtils_GetAllLines(vtkPolyData *pd, int *numLines,
                                          vtkIdType **lines);

int VTKSVCORE_EXPORT VtkUtils_GetAllPolys(vtkPolyData *pd, int *numPgns,
                                          vtkIdType **pgns);

int VTKSVCORE_EXPORT VtkUtils_GetLines(vtkPolyData *pd, vtkIdType **lines,
                                       int *numLines);

int VTKSVCORE_EXPORT VtkUtils_GetLinkedLines(vtkIdType *lines, int numLines,
                                             int ptIx, int **lineIxs,
                                             int *numLineIxs);

int VTKSVCORE_EXPORT VtkUtils_FindClosedLineRegions(vtkIdType *lines,
                                                    int numLines, int numPts,
                                                    int **startIxs,
                                                    int *numRegions);

int VTKSVCORE_EXPORT VtkUtils_GetClosedLineRegion(vtkIdType *lines,
                                                  int numLines, int startIx,
                                                  int **lineIds,
                                                  int *numLineIds);

int VTKSVCORE_EXPORT VtkUtils_MakePolyDataFromLineIds(double *pts, int numPts,
                                                      vtkIdType *lines,
                                                      int *lineIds,
                                                      int numLineIds,
                                                      vtkPolyData **pd);

int VTKSVCORE_EXPORT VtkUtils_MakeShortArray(vtkDataArray *s, int *num,
                                             short **dataOut);

int VTKSVCORE_EXPORT VtkUtils_MakeFloatArray(vtkDataArray *s, int *num,
                                             float **dataOut);

VTKSVCORE_EXPORT vtkPoints *VtkUtils_DeepCopyPoints(vtkPoints *ptsIn);

VTKSVCORE_EXPORT vtkCellArray *VtkUtils_DeepCopyCells(vtkCellArray *cellsIn);

int VTKSVCORE_EXPORT VtkUtils_MakePolysConsistent(vtkPolyData *pd);

int VTKSVCORE_EXPORT VtkUtils_ReverseAllCells(vtkPolyData *pd);

int VTKSVCORE_EXPORT VtkUtils_ReversePtList(int num, double ptsIn[],
                                            double *ptsOut[]);

int VTKSVCORE_EXPORT VtkUtils_PDCheckArrayName(vtkPolyData *object,
                                               int datatype,
                                               std::string arrayname);

int VTKSVCORE_EXPORT VtkUtils_UGCheckArrayName(vtkUnstructuredGrid *object,
                                               int datatype,
                                               std::string arrayname);

void VTKSVCORE_EXPORT VtkUtils_write_vtu(vtkUnstructuredGrid *ugrid,
                        const std::string file_name);

void VTKSVCORE_EXPORT VtkUtils_write_vtp(vtkPolyData *polydata, const std::string file_name);

#endif
