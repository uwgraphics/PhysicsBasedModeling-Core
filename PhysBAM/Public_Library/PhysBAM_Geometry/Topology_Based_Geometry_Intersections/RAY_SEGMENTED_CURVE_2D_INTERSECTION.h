//#####################################################################
// Copyright 2009, Jon Gretarsson.
// This file is part of PhysBAM whose distribution is governed by the license contained in the accompanying file PHYSBAM_COPYRIGHT.txt.
//#####################################################################
// Namespace INTERSECTION
//##################################################################### 
#ifndef __RAY_SEGMENTED_CURVE_2D_INTERSECTION__
#define __RAY_SEGMENTED_CURVE_2D_INTERSECTION__
#include <PhysBAM_Geometry/Topology_Based_Geometry/TOPOLOGY_BASED_GEOMETRY_FORWARD.h>
namespace PhysBAM{
template<class T,int d> class VECTOR;
template<class TV> class RAY;

namespace INTERSECTION{
//#####################################################################
template<class T> bool Intersects(RAY<VECTOR<T,2> >& ray,const SEGMENTED_CURVE_2D<T>& curve, const T thickness_over_two=0);
template<class T> bool Closest_Non_Intersecting_Point(RAY<VECTOR<T,2> >& ray,const SEGMENTED_CURVE_2D<T>& curve, const T thickness_over_two=0);
//#####################################################################
};
};
#endif
