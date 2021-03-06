//#####################################################################
// Copyright 2009, Jon Gretarsson.
// This file is part of PhysBAM whose distribution is governed by the license contained in the accompanying file PHYSBAM_COPYRIGHT.txt.
//#####################################################################
#include <PhysBAM_Tools/Grids_Uniform/GRID.h>
#include <PhysBAM_Tools/Grids_Uniform/UNIFORM_GRID_ITERATOR_NODE.h>
#include <PhysBAM_Tools/Grids_Uniform_Arrays/ARRAYS_ND.h>
#include <PhysBAM_Tools/Grids_Uniform_Arrays/GRID_ARRAYS_POLICY_UNIFORM.h>
#include <PhysBAM_Geometry/Basic_Geometry/BOX.h>
#include <PhysBAM_Geometry/Grids_Uniform_Computations/BOX_SIGNED_DISTANCE.h>
#include <PhysBAM_Geometry/Grids_Uniform_Computations/SIGNED_DISTANCE.h>

namespace PhysBAM{
namespace SIGNED_DISTANCE{
#define BOX_SIGNED_DISTANCE_HELPER_d(T,d) \
    template void Calculate(BOX<VECTOR<T,d> >&,const GRID<VECTOR<T,d> >&,GRID_ARRAYS_POLICY<GRID<VECTOR<T,d> > >::ARRAYS_SCALAR&,bool);

BOX_SIGNED_DISTANCE_HELPER_d(float,1);
BOX_SIGNED_DISTANCE_HELPER_d(float,2);
BOX_SIGNED_DISTANCE_HELPER_d(float,3);
#ifndef COMPILE_WITHOUT_DOUBLE_SUPPORT
BOX_SIGNED_DISTANCE_HELPER_d(double,1);
BOX_SIGNED_DISTANCE_HELPER_d(double,2);
BOX_SIGNED_DISTANCE_HELPER_d(double,3);
#endif
}
}
