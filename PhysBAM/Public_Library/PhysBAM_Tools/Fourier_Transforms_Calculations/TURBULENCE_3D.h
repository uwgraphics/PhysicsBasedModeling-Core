//#####################################################################
// Copyright 2002, 2003, 2004, Ronald Fedkiw, Duc Nguyen.
// This file is part of PhysBAM whose distribution is governed by the license contained in the accompanying file PHYSBAM_COPYRIGHT.txt.
//#####################################################################
// Class TURBULENCE_2D  
//##################################################################### 
//
// Generates a periodic turbulent field from a random complex sequence.
// The length of the domain is equal the number of grid points (i.e 64) you want to use multiply with the dx of the physical domain. 
//
//#####################################################################
#ifndef __TURBULENCE_3D__
#define __TURBULENCE_3D__

#include <PhysBAM_Tools/Fourier_Transforms_Calculations/TURBULENCE.h>
#include <PhysBAM_Tools/Grids_Uniform_Arrays/ARRAYS_ND.h>
#include <PhysBAM_Tools/Grids_Uniform_Interpolation/LINEAR_INTERPOLATION_UNIFORM.h>
#include <PhysBAM_Tools/Vectors/VECTOR_3D.h>
namespace PhysBAM{

template<class T>
class TURBULENCE_3D:public TURBULENCE<T>
{
    typedef VECTOR<T,3> TV;
public:
    using TURBULENCE<T>::time_start;using TURBULENCE<T>::time_end;
        
private:
    GRID<TV> grid;
    ARRAY<T,VECTOR<int,3> > u_old,v_old,w_old,u_new,v_new,w_new;
    LINEAR_INTERPOLATION_UNIFORM<GRID<TV>,T> interpolation;

public:
    TURBULENCE_3D()
    {}
    
    TURBULENCE_3D(const GRID<TV>& grid_input)
    {
        Initialize_Grid(grid_input);
    }
    
    void Initialize_Grid(const GRID<TV>& grid_input)
    {grid=grid_input;
    u_old.Resize(1,grid.counts.x,1,grid.counts.y,1,grid.counts.z);v_old.Resize(1,grid.counts.x,1,grid.counts.y,1,grid.counts.z);w_old.Resize(1,grid.counts.x,1,grid.counts.y,1,grid.counts.z);
    u_new.Resize(1,grid.counts.x,1,grid.counts.y,1,grid.counts.z);v_new.Resize(1,grid.counts.x,1,grid.counts.y,1,grid.counts.z);w_new.Resize(1,grid.counts.x,1,grid.counts.y,1,grid.counts.z);}

    void Generate_Initial_Turbulence(const T time_start_input=0,const T time_end_input=1)
    {time_start=time_start_input;time_end=time_end_input;
    Generate_Random_Turbulence(grid,u_old,v_old,w_old);Generate_Random_Turbulence(grid,u_new,v_new,w_new);}

    void Advance_Turbulence()
    {T increment=time_end-time_start;time_start=time_end;time_end+=increment;
    ARRAY<T,VECTOR<int,3> >::Copy(u_new,u_old);ARRAY<T,VECTOR<int,3> >::Copy(v_new,v_old);ARRAY<T,VECTOR<int,3> >::Copy(w_new,w_old);
    Generate_Random_Turbulence(grid,u_new,v_new,w_new);}
   
    VECTOR<T,3> Turbulent_Velocity(const VECTOR<T,3>& X,const T fraction) const
    {VECTOR<T,3> X_new=wrap(X,grid.Xmin(),grid.Xmax());
    T u1=interpolation.Clamped_To_Array(grid,u_old,X_new),u2=interpolation.Clamped_To_Array(grid,u_new,X_new),
       v1=interpolation.Clamped_To_Array(grid,v_old,X_new),v2=interpolation.Clamped_To_Array(grid,v_new,X_new),
       w1=interpolation.Clamped_To_Array(grid,w_old,X_new),w2=interpolation.Clamped_To_Array(grid,w_new,X_new);
    T one_minus_fraction=1-fraction;
    return VECTOR<T,3>(one_minus_fraction*u1+fraction*u2,one_minus_fraction*v1+fraction*v2,one_minus_fraction*w1+fraction*w2);}
    
    T Turbulent_Face_Velocity(const int axis,const VECTOR<T,3>& X,const T fraction) const
    {assert(1<=axis&&axis<=3);switch(axis){case 1:return Turbulent_U_Velocity(X,fraction);case 2:return Turbulent_V_Velocity(X,fraction);default:return Turbulent_W_Velocity(X,fraction);}}
    
    T Turbulent_U_Velocity(const VECTOR<T,3>& X,const T fraction) const
    {VECTOR<T,3> X_new=wrap(X,grid.Xmin(),grid.Xmax());
    T u1=interpolation.Clamped_To_Array(grid,u_old,X_new),u2=interpolation.Clamped_To_Array(grid,u_new,X_new);
    T one_minus_fraction=1-fraction;
    return one_minus_fraction*u1+fraction*u2;}

    T Turbulent_V_Velocity(const VECTOR<T,3>& X,const T fraction) const
    {VECTOR<T,3> X_new=wrap(X,grid.Xmin(),grid.Xmax());
    T v1=interpolation.Clamped_To_Array(grid,v_old,X_new),v2=interpolation.Clamped_To_Array(grid,v_new,X_new);
    T one_minus_fraction=1-fraction;
    return one_minus_fraction*v1+fraction*v2;}

    T Turbulent_W_Velocity(const VECTOR<T,3>& X,const T fraction) const
    {VECTOR<T,3> X_new=wrap(X,grid.Xmin(),grid.Xmax());
    T w1=interpolation.Clamped_To_Array(grid,w_old,X_new),w2=interpolation.Clamped_To_Array(grid,w_new,X_new);
    T one_minus_fraction=1-fraction;
    return one_minus_fraction*w1+fraction*w2;}

//#####################################################################
};
}    
#endif

