//#####################################################################
// Copyright 2004-2005, Ron Fedkiw, Geoffrey Irving, Frank Losasso, Andrew Selle, Tamar Shinar.
// This file is part of PhysBAM whose distribution is governed by the license contained in the accompanying file PHYSBAM_COPYRIGHT.txt.
//#####################################################################
// Class LINEAR_INTERPOLATION_COLLIDABLE_DYADIC
//#####################################################################
#ifndef COMPILE_WITHOUT_DYADIC_SUPPORT
#ifndef __LINEAR_INTERPOLATION_COLLIDABLE_CELL_DYADIC__
#define __LINEAR_INTERPOLATION_COLLIDABLE_CELL_DYADIC__

#include <PhysBAM_Tools/Interpolation/LINEAR_INTERPOLATION.h>
#include <PhysBAM_Geometry/Grids_Dyadic_Collisions/GRID_BASED_COLLISION_GEOMETRY_DYADIC.h>
namespace PhysBAM{

template<class T_GRID,class T2>
class LINEAR_INTERPOLATION_COLLIDABLE_CELL_DYADIC:public INTERPOLATION_DYADIC<T_GRID,T2>
{
    typedef typename T_GRID::VECTOR_T TV;typedef typename TV::SCALAR T;typedef typename T_GRID::CELL T_CELL;typedef typename COLLISION_GEOMETRY_COLLECTION_POLICY<T_GRID>::GRID_BASED_COLLISION_GEOMETRY T_GRID_BASED_COLLISION_GEOMETRY;
    typedef typename INTERPOLATION_POLICY<T_GRID>::LINEAR_INTERPOLATION_HELPER T_LINEAR_INTERPOLATION_HELPER;typedef typename INTERPOLATION_POLICY<T_GRID>::LINEAR_INTERPOLATION_MAC_HELPER T_LINEAR_INTERPOLATION_MAC_HELPER;
public:
    const T_GRID_BASED_COLLISION_GEOMETRY& body_list;
    const ARRAY<bool>* cell_valid_value_mask;
    T2 default_cell_replacement_value;
    bool extrapolate_to_invalid_cell_values;
    LINEAR_INTERPOLATION_DYADIC<T_GRID,T2> interpolation;
    
    LINEAR_INTERPOLATION_COLLIDABLE_CELL_DYADIC(const T_GRID_BASED_COLLISION_GEOMETRY& body_list_input,const ARRAY<bool>* cell_valid_value_mask_input,const T2& default_cell_replacement_value_input,
        const bool extrapolate_to_invalid_cell_values_input=true)
        :body_list(body_list_input),cell_valid_value_mask(cell_valid_value_mask_input),default_cell_replacement_value(default_cell_replacement_value_input),
        extrapolate_to_invalid_cell_values(extrapolate_to_invalid_cell_values_input)
    {}

    void Set_Default_Replacement_Value(const T2& default_cell_replacement_value_input)
    {default_cell_replacement_value=default_cell_replacement_value_input;}

    T2 From_Block_Cell(const T_GRID& grid,const BLOCK_DYADIC<T_GRID>& block,const ARRAY<T2>& u,const TV& X) const PHYSBAM_OVERRIDE
    {bool interpolation_valid;return From_Block_Cell(grid,block,u,X,interpolation_valid);}

    T2 From_Block_Cell(const T_GRID& grid,const BLOCK_DYADIC<T_GRID>& block,const ARRAY<T2>& u,const TV& X,bool& interpolation_valid) const
    {assert(block.Inside(X));
    if(!body_list.Occupied_Block(block)){interpolation_valid=true;return T_LINEAR_INTERPOLATION_MAC_HELPER::Interpolate_Cell(block,u,X);}
    COLLISION_GEOMETRY_ID body_id;int aggregate_id;
    if(body_list.Inside_Any_Simplex_Of_Any_Body(block,X,body_id,aggregate_id))
        return Invalid_Value_Replacement(grid,u,X,block,X,body_id,aggregate_id,interpolation_valid);
    int valid_mask=0;T2 values[T_GRID::number_of_cells_per_block];
    int cell_indices[T_GRID::number_of_cells_per_block];block.All_Cell_Indices(cell_indices);
    for(int k=0;k<T_GRID::number_of_cells_per_block;k++)
        values[k]=Trace_And_Get_Value(grid,u,X,cell_indices[k],cell_indices,valid_mask,1<<k);
    if(extrapolate_to_invalid_cell_values) Extrapolate_To_Invalid_Values(grid,u,X,block,values,valid_mask);
    interpolation_valid=(valid_mask!=0);
    return LINEAR_INTERPOLATION<T,T2>::Linear(values,(X-block.Minimum_Corner())*grid.One_Over_Minimum_Cell_DX());}

protected:
    T2 Trace_And_Get_Value(const T_GRID& grid,const ARRAY<T2>& u,const TV& X,const int i,int* cell_indices,int& valid_mask,const int mask_value=0) const
    {TV intersection_point;COLLISION_GEOMETRY_ID body_id;int aggregate_id;
    assert(cell_valid_value_mask);
    if(body_list.Cell_Center_Intersection(i,cell_indices,T_GRID::number_of_cells_per_block,X,body_id,aggregate_id,intersection_point) || !(*cell_valid_value_mask)(i))
        return default_cell_replacement_value;
    else{valid_mask|=mask_value;return u(i);}}

    virtual T2 Invalid_Value_Replacement(const T_GRID& grid,const ARRAY<T2>& u,const TV& X,const BLOCK_DYADIC<T_GRID>& block,const TV& intersection_point,
        const COLLISION_GEOMETRY_ID body_id,const int aggregate_id,bool& valid,const T ray_t_max=0) const
    {valid=false;return default_cell_replacement_value;}

    void Extrapolate_To_Invalid_Values(const T_GRID& grid,const ARRAY<T2>& u,const TV& X,const BLOCK_DYADIC<T_GRID>& block,T2 values[T_GRID::number_of_cells_per_block],int& valid_mask) const
    {static const int all_valid_mask=(1<<T_GRID::number_of_cells_per_block)-1,neighbor_mask=T_GRID::number_of_cells_per_block-1;
    if(valid_mask==0) for(int t=0;t<T_GRID::number_of_cells_per_block;t++)values[t]=default_cell_replacement_value;
    else if(valid_mask!=all_valid_mask){ // not everything is valid
        for(int t=0;t<T_GRID::number_of_cells_per_block;t++)if(!(valid_mask&(1<<t))){
            int ring;
            for(ring=1;ring<T_GRID::dimension;ring++){ // one ring in 2d, one and then two ring in 3d
                int ring_mask=ring==2?neighbor_mask:0;
                T2 sum=T2();int count=0;
                for(int n=0;n<T_GRID::dimension;n++){
                    int neighbor=t^(1<<n)^ring_mask;
                    if(valid_mask&(1<<neighbor)){count++;sum+=values[neighbor];}}
                if(count>0){values[t]=sum/(T)count;break;}} // average valid ring neighbors
            if(ring==T_GRID::dimension) values[t]=values[t^neighbor_mask];} // final ring (must be valid because valid_mask!=0)
        valid_mask=all_valid_mask;}}

//#####################################################################
};
}
#endif
#endif
