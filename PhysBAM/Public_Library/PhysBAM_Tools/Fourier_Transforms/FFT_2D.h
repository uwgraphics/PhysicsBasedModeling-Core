//#####################################################################
// Copyright 2002-2006, Ronald Fedkiw, Eran Guendelman, Geoffrey Irving.
// This file is part of PhysBAM whose distribution is governed by the license contained in the accompanying file PHYSBAM_COPYRIGHT.txt.
//#####################################################################
// Class FFT_2D
//#####################################################################
//
// Uses fftw if USE_FFTW is defined, otherwise uses code from Numerical Recipes.
// u is (1,m) by (1,n).
// u_hat is (0,m-1) by (0,n/2).
// Forward transform (u -> u_hat) uses -1 sign in exponential
// Inverse transform (u_hat -> u) uses +1 sign in exponential
//
// Note: fftw's inverse transform destroys input array, so we make a copy by default.
// But if you don't need your u_hat's preserved you can call Inverse_Transform with preserve_u_hat=false which will save having to do the copy.
//
//#####################################################################
#ifndef __FFT_2D__
#define __FFT_2D__

#include <PhysBAM_Tools/Arrays/ARRAY.h>
#include <PhysBAM_Tools/Grids_Uniform/GRID.h>
struct fftw_plan_s;struct fftwf_plan_s;
namespace PhysBAM{

template<class T> class COMPLEX;

template<class T>
class FFT_2D
{
    typedef VECTOR<T,2> TV;
public:
    GRID<TV> grid;
private:
    // for fftw
    typedef typename IF<IS_SAME<T,float>::value,fftwf_plan_s*,fftw_plan_s*>::TYPE T_FFTW_PLAN;
    mutable ARRAY<COMPLEX<T> ,VECTOR<int,2> > u_hat_copy;
    mutable T_FFTW_PLAN plan_u_to_u_hat,plan_u_hat_to_u;
    mutable VECTOR<int,2> plan_u_to_u_hat_counts,plan_u_hat_to_u_counts;
    // for NR
    mutable ARRAY<float> data; // array of complex numbers
public:

    FFT_2D(const GRID<TV>& grid_input);
    ~FFT_2D();

    void Inverse_Transform(const ARRAY<COMPLEX<T> ,VECTOR<int,2> >& u_hat,ARRAY<T,VECTOR<int,2> >& u,bool normalize=true) const
    {Inverse_Transform(const_cast<ARRAY<COMPLEX<T> ,VECTOR<int,2> >&>(u_hat),u,normalize,true);}

//#####################################################################
    void Transform(const ARRAY<T,VECTOR<int,2> >& u,ARRAY<COMPLEX<T> ,VECTOR<int,2> >& u_hat) const;
    void Inverse_Transform(ARRAY<COMPLEX<T> ,VECTOR<int,2> >& u_hat,ARRAY<T,VECTOR<int,2> >& u,bool normalize=true,bool preserve_u_hat=true) const;
    void Enforce_Real_Valued_Symmetry(ARRAY<COMPLEX<T> ,VECTOR<int,2> >& u_hat) const;
    void First_Derivatives(const ARRAY<COMPLEX<T> ,VECTOR<int,2> >& u_hat,ARRAY<COMPLEX<T> ,VECTOR<int,2> >& ux_hat,ARRAY<COMPLEX<T> ,VECTOR<int,2> >& uy_hat) const;
    void Make_Divergence_Free(ARRAY<COMPLEX<T> ,VECTOR<int,2> >& u_hat,ARRAY<COMPLEX<T> ,VECTOR<int,2> >& v_hat) const;
    void Filter_High_Frequencies(ARRAY<COMPLEX<T> ,VECTOR<int,2> >& u_hat,T scale=(T)1) const;
//#####################################################################
};
}
#endif
