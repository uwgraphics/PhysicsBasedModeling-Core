//#####################################################################
// Copyright 3009, Avi Robinson-Mosher.
// This file is part of PhysBAM whose distribution is governed by the license contained in the accompanying file PHYSBAM_COPYRIGHT.txt.
//#####################################################################
// Class READ_WRITE_VECTOR_1D
//#####################################################################
#ifndef COMPILE_WITHOUT_READ_WRITE_SUPPORT
#ifndef __READ_WRITE_VECTOR_1D__
#define __READ_WRITE_VECTOR_1D__

#include <PhysBAM_Tools/Read_Write/Utilities/FILE_UTILITIES.h>
#include <PhysBAM_Tools/Read_Write/Utilities/READ_WRITE.h>
#include <PhysBAM_Tools/Read_Write/Vectors/READ_WRITE_VECTOR_BASE.h>
#include <PhysBAM_Tools/Vectors/VECTOR_1D.h>
namespace PhysBAM{

template<class RW,class T>
class Read_Write<VECTOR<T,1>,RW,typename DISABLE_IF<IS_BINARY_IO_SAFE<VECTOR<T,1>,RW>::value>::TYPE>
{
public:
    static void Read(std::istream& input,VECTOR<T,1>& object)
    {Read_Binary<RW>(input,object.x);}

    static void Write(std::ostream& output,const VECTOR<T,1>& object)
    {Write_Binary<RW>(output,object.x);}
};
//#####################################################################
// Stream input and output
//#####################################################################
template<class T>
inline std::istream& operator>>(std::istream& input,VECTOR<T,1>& v)
{FILE_UTILITIES::Ignore(input,'[');input>>v.x;FILE_UTILITIES::Ignore(input,']');return input;}
}
#endif
#endif
