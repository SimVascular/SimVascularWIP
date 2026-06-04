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

#ifndef __CV_SYS_GEOM_H
#define __CV_SYS_GEOM_H

#include "SimVascular.h"
#include "vtkSV1GeometryModule.h" // For exports

#include "sv_PolyData.h"
#include "vtkSVNURBSSurface.h"

VTKSV1GEOMETRY_EXPORT void sys_geom_write_vtp(std::string &file_name,
                                          cvPolyData *src);
VTKSV1GEOMETRY_EXPORT void sys_geom_write_vtp(std::string &file_name,
                                          vtkPolyData *src);

VTKSV1GEOMETRY_EXPORT cvPolyData *sys_geom_DeepCopy(cvPolyData *src);

VTKSV1GEOMETRY_EXPORT cvPolyData *sys_geom_MergePts(cvPolyData *src);

VTKSV1GEOMETRY_EXPORT cvPolyData *sys_geom_MergePts_tol(cvPolyData *src,
                                                    double tol);

VTKSV1GEOMETRY_EXPORT int sys_geom_union(cvPolyData *srcA, cvPolyData *srcB,
                                     double tolerance, cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_all_union(cvPolyData **src, int numSrcs,
                                         int nointerbool, double tolerance,
                                         cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_assign_ids_based_on_faces(cvPolyData *model,
                                                         cvPolyData **faces,
                                                         int numFaces, int *ids,
                                                         cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_intersect(cvPolyData *srcA, cvPolyData *srcB,
                                         double tolerance, cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_subtract(cvPolyData *srcA, cvPolyData *srcB,
                                        double tolerance, cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int
sys_geom_checksurface(cvPolyData *src, int stats[], double tolerance,
                      PolyDataCheckResults &check_results);

VTKSV1GEOMETRY_EXPORT cvPolyData *sys_geom_Clean(cvPolyData *src);

VTKSV1GEOMETRY_EXPORT int sys_geom_NumClosedLineRegions(cvPolyData *src, int *num);

VTKSV1GEOMETRY_EXPORT int sys_geom_GetClosedLineRegion(cvPolyData *src, int id,
                                                   cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_Reduce(cvPolyData *src, double tol,
                                      cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_ReverseAllCells(cvPolyData *src,
                                               cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_GetOrderedPts(cvPolyData *src, double **ord_pts,
                                             int *num);

VTKSV1GEOMETRY_EXPORT int sys_geom_Get2DPgon(cvPolyData *src, double **pgon,
                                         int *num);

VTKSV1GEOMETRY_EXPORT int sys_geom_ReversePtList(int num, double ptsIn[],
                                             double *ptsOut[]);

VTKSV1GEOMETRY_EXPORT int sys_geom_WriteOrderedPts(cvPolyData *src, char *fn);

VTKSV1GEOMETRY_EXPORT int sys_geom_WriteLines(cvPolyData *src, char *fn);

VTKSV1GEOMETRY_EXPORT int sys_geom_MakePolysConsistent(cvPolyData *src,
                                                   cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_PolysClosed(cvPolyData *src, int *closed);

VTKSV1GEOMETRY_EXPORT int sys_geom_SurfArea(cvPolyData *src, double *area);

VTKSV1GEOMETRY_EXPORT int sys_geom_getPolyCentroid(cvPolyData *src,
                                               double centroid[]);

VTKSV1GEOMETRY_EXPORT int sys_geom_PrintTriStats(cvPolyData *surf);

VTKSV1GEOMETRY_EXPORT int sys_geom_PrintSmallPolys(cvPolyData *src, double sideTol);

VTKSV1GEOMETRY_EXPORT int sys_geom_RmSmallPolys(cvPolyData *src, double sideTol,
                                            cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_BBox(cvPolyData *obj, double bbox[]);

VTKSV1GEOMETRY_EXPORT int sys_geom_OrientProfile(cvPolyData *src, double ppt[],
                                             double ptan[], double xhat[],
                                             cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_DisorientProfile(cvPolyData *src, double ppt[],
                                                double ptan[], double xhat[],
                                                cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_Translate(cvPolyData *src, double translate[],
                                         cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_ScaleAvg(cvPolyData *src, double factor,
                                        cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT cvPolyData *sys_geom_Align(cvPolyData *ref, cvPolyData *src);

VTKSV1GEOMETRY_EXPORT cvPolyData *sys_geom_AlignByDist(cvPolyData *ref,
                                                   cvPolyData *src);

VTKSV1GEOMETRY_EXPORT cvPolyData *sys_geom_ReorderPolygon(cvPolyData *src,
                                                      int startIx);

VTKSV1GEOMETRY_EXPORT int sys_geom_Classify(cvPolyData *obj, double pt[],
                                        int *result);

VTKSV1GEOMETRY_EXPORT int sys_geom_PtInPoly(cvPolyData *obj, double pt[],
                                        int usePrevPoly, int *result);

VTKSV1GEOMETRY_EXPORT cvPolyData *sys_geom_sampleLoop(cvPolyData *src,
                                                  int targetNumPts);

VTKSV1GEOMETRY_EXPORT int sys_geom_loft_solid(
    cvPolyData **srcs, int numSrcs, int useLinearSampleAlongLength, int useFFT,
    int numOutPtsAlongLength, int numOutPtsInSegs, int numLinearPtsAlongLength,
    int numModes, int splineType, double bias, double tension,
    double continuity, cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_loft_solid_with_nurbs(
    cvPolyData **srcs, int numSrcs, int uDegree, int vDegree, double uSpacing,
    double vSpacing, const char *uKnotSpanType, const char *vKnotSpanType,
    const char *uParametricSpanType, const char *vParametricSpanType,
    vtkSVNURBSSurface *surface, cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_2DWindingNum(cvPolyData *pgn);

VTKSV1GEOMETRY_EXPORT int sys_geom_PolygonNormal(cvPolyData *pgn, double n[]);

VTKSV1GEOMETRY_EXPORT int sys_geom_AvgPt(cvPolyData *src, double pt[]);

VTKSV1GEOMETRY_EXPORT int sys_geom_splinePtsToPathPlan(vtkPolyData *pd,
                                                   int numOutputPts,
                                                   char *filename, int flag);

#ifdef SV_USE_PYTHON
VTKSV1GEOMETRY_EXPORT int pysys_geom_splinePtsToPathPlan(vtkPolyData *pd,
                                                     int numOutputPts,
                                                     char *filename, int flag,
                                                     char **output);
#endif

VTKSV1GEOMETRY_EXPORT int sys_geom_InterpolateScalar(cvPolyData *src, double pt[],
                                                 double *scalar);

VTKSV1GEOMETRY_EXPORT int sys_geom_InterpolateVector(cvPolyData *src, double pt[],
                                                 double vect[]);

VTKSV1GEOMETRY_EXPORT int sys_geom_IntersectWithLine(cvPolyData *src, double p0[],
                                                 double p1[],
                                                 double intersect[]);

VTKSV1GEOMETRY_EXPORT cvPolyData *sys_geom_warp3dPts(cvPolyData *src, double scale);

enum sys_geom_math_scalar {
  SYS_GEOM_NO_SCALAR,
  SYS_GEOM_ADD_SCALAR,
  SYS_GEOM_SUBTRACT_SCALAR,
  SYS_GEOM_MULTIPLY_SCALAR,
  SYS_GEOM_DIVIDE_SCALAR
};
enum sys_geom_math_vector {
  SYS_GEOM_NO_VECTOR,
  SYS_GEOM_ADD_VECTOR,
  SYS_GEOM_SUBTRACT_VECTOR,
  SYS_GEOM_MULTIPLY_VECTOR,
  SYS_GEOM_DIVIDE_VECTOR
};

VTKSV1GEOMETRY_EXPORT int sys_geom_mathPointData(cvPolyData *srcA, cvPolyData *srcB,
                                             sys_geom_math_scalar scflag,
                                             sys_geom_math_vector vflag,
                                             cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_Project(cvPolyData *srcA, cvPolyData *srcB,
                                       sys_geom_math_scalar scflag,
                                       sys_geom_math_vector vflag,
                                       cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int sys_geom_ReplacePointData(cvPolyData *srcA,
                                                cvPolyData *srcB,
                                                sys_geom_math_scalar scflag,
                                                sys_geom_math_vector vflag,
                                                cvPolyData **dst);

VTKSV1GEOMETRY_EXPORT int
sys_geom_set_array_for_local_op_sphere(cvPolyData *pd, cvPolyData **outpd,
                                       double radius, double *center,
                                       char *outarrayname, int datatype);

VTKSV1GEOMETRY_EXPORT int
sys_geom_set_array_for_local_op_face(cvPolyData *pd, cvPolyData **outpd,
                                     char *inarrayname, int *vals, int nvals,
                                     char *outarrayname, int datatype);

VTKSV1GEOMETRY_EXPORT int
sys_geom_set_array_for_local_op_cells(cvPolyData *pd, cvPolyData **outpd,
                                      int *vals, int nvals, char *outarrayname,
                                      int datatype);

VTKSV1GEOMETRY_EXPORT int sys_geom_set_array_for_local_op_face_blend(
    cvPolyData *pd, cvPolyData **outpd, char *inarrayname, int *vals, int nvals,
    double radius, char *outarrayname, int datatype);

VTKSV1GEOMETRY_EXPORT int sys_geom_local_quadric_decimation(cvPolyData *pd,
                                                        cvPolyData **outpd,
                                                        double target,
                                                        char *pointarrayname,
                                                        char *cellarrayname);

VTKSV1GEOMETRY_EXPORT int
sys_geom_local_laplacian_smooth(cvPolyData *pd, cvPolyData **outpd,
                                int numiters, double relax,
                                char *pointarrayname, char *cellarrayname);

VTKSV1GEOMETRY_EXPORT int sys_geom_local_constrain_smooth(
    cvPolyData *pd, cvPolyData **outpd, int numiters, double constrainfactor,
    int numcgsolves, char *pointarrayname, char *cellarrayname);

VTKSV1GEOMETRY_EXPORT int sys_geom_local_linear_subdivision(cvPolyData *pd,
                                                        cvPolyData **outpd,
                                                        int numiters,
                                                        char *pointarrayname,
                                                        char *cellarrayname);

VTKSV1GEOMETRY_EXPORT int sys_geom_local_butterfly_subdivision(cvPolyData *pd,
                                                           cvPolyData **outpd,
                                                           int numiters,
                                                           char *pointarrayname,
                                                           char *cellarrayname);

VTKSV1GEOMETRY_EXPORT int sys_geom_local_loop_subdivision(cvPolyData *pd,
                                                      cvPolyData **outpd,
                                                      int numiters,
                                                      char *pointarrayname,
                                                      char *cellarrayname);

VTKSV1GEOMETRY_EXPORT int sys_geom_local_blend(
    cvPolyData *pd, cvPolyData **outpd, int numblenditers, int numsubblenditers,
    int numsubdivisioniters, int numcgsmoothiters, int numlapsmoothiters,
    double targetdecimation, char *pointarrayname, char *cellarrayname);

VTKSV1GEOMETRY_EXPORT int sys_geom_set_ids_for_caps(cvPolyData *pd,
                                                cvPolyData **outpd,
                                                int **doublecaps,
                                                int *numfaces);

VTKSV1GEOMETRY_EXPORT void sys_geom_check_lines_connectivity(int numLines,
                                                         vtkIdType *lineConn,
                                                         bool &nonManifold,
                                                         bool &multipleRegions,
                                                         bool &notClosed);

#endif /* __SYS_GEOM_H */
