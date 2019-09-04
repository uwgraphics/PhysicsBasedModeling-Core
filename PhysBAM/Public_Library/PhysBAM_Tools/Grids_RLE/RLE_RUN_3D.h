//#####################################################################
// Copyright 2005, Geoffrey Irving.
// This file is part of PhysBAM whose distribution is governed by the license contained in the accompanying file PHYSBAM_COPYRIGHT.txt.
//#####################################################################
// Class RLE_RUN_3D
//#####################################################################
#ifndef COMPILE_WITHOUT_RLE_SUPPORT
#ifndef __RLE_RUN_3D__
#define __RLE_RUN_3D__

#include <PhysBAM_Tools/Grids_RLE/RLE_RUN.h>
namespace PhysBAM{

class RLE_RUN_3D:public RLE_RUN
{
public:
    int cell;
    //int faces_x[2];
    //int faces_z[2];
    int faces[6];

    RLE_RUN_3D()
    {
        Clear();
    }

    RLE_RUN_3D(const bool is_long_input,const short jmin_input)
        :RLE_RUN(is_long_input,jmin_input)
    {
        Clear();
    }

    explicit RLE_RUN_3D(const RLE_RUN& run_input)
        :RLE_RUN(run_input)
    {
        Clear();
    }

private:
    void Clear()
    {cell=0;for(int f=0;f<6;f++)faces[f]=0;}

//#####################################################################
};
}
#endif
#endif
