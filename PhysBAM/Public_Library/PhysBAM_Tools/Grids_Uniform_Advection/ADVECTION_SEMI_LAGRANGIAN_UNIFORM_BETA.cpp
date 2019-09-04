//#####################################################################
// Copyright 2002-2010, Ronald Fedkiw, Geoffrey Irving, Michael Lentine, Frank Losasso, Andrew Selle.
// This file is part of PhysBAM whose distribution is governed by the license contained in the accompanying file PHYSBAM_COPYRIGHT.txt.
//#####################################################################
#include <PhysBAM_Tools/Grids_Uniform_Advection/ADVECTION_SEMI_LAGRANGIAN_UNIFORM_DEFINITION_BETA.h>
#include <PhysBAM_Tools/Grids_Uniform_Interpolation/CUBIC_MN_INTERPOLATION_UNIFORM.h>
#include <PhysBAM_Tools/Grids_Uniform_Interpolation/QUADRATIC_INTERPOLATION_UNIFORM.h>

#define INSTANTIATION_HELPER(T,T_GRID,d) \
    template class ADVECTION_SEMI_LAGRANGIAN_UNIFORM_BETA<T_GRID,SYMMETRIC_MATRIX<T,d>,AVERAGING_UNIFORM<T_GRID,FACE_LOOKUP_UNIFORM<T_GRID > >,LINEAR_INTERPOLATION_UNIFORM<T_GRID,SYMMETRIC_MATRIX<T,d>,FACE_LOOKUP_UNIFORM<T_GRID > > >; \
    template class ADVECTION_SEMI_LAGRANGIAN_UNIFORM_BETA<T_GRID,T,AVERAGING_UNIFORM<T_GRID,FACE_LOOKUP_UNIFORM<T_GRID > >,LINEAR_INTERPOLATION_UNIFORM<T_GRID,T,FACE_LOOKUP_UNIFORM<T_GRID > > >; \
    template class ADVECTION_SEMI_LAGRANGIAN_UNIFORM_BETA<T_GRID,T,AVERAGING_UNIFORM<T_GRID,FACE_LOOKUP_UNIFORM<T_GRID > >,QUADRATIC_INTERPOLATION_UNIFORM<T_GRID,T,FACE_LOOKUP_UNIFORM<T_GRID > > >; \
    template class ADVECTION_SEMI_LAGRANGIAN_UNIFORM_BETA<T_GRID,T,AVERAGING_UNIFORM<T_GRID,FACE_LOOKUP_UNIFORM<T_GRID > >,CUBIC_MN_INTERPOLATION_UNIFORM<T_GRID,T,FACE_LOOKUP_UNIFORM<T_GRID > > >;
    
#define P(...) __VA_ARGS__
namespace PhysBAM{
INSTANTIATION_HELPER(float,P(GRID<VECTOR<float,1> >),2)
INSTANTIATION_HELPER(float,P(GRID<VECTOR<float,2> >),2);
INSTANTIATION_HELPER(float,P(GRID<VECTOR<float,3> >),3);
#ifndef COMPILE_WITHOUT_DOUBLE_SUPPORT
INSTANTIATION_HELPER(double,P(GRID<VECTOR<double,1> >),2);
INSTANTIATION_HELPER(double,P(GRID<VECTOR<double,2> >),2);
INSTANTIATION_HELPER(double,P(GRID<VECTOR<double,3> >),3);
#endif
}