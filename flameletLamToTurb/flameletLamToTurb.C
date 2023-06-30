//*****************************************************//
//						       //
//                IN THE NAME OF GOD                   //
//             utilities : flameletLamToTurb           //
//       converting laminar library to turbulence      //
//						       //
//*****************************************************//



#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/math/special_functions/erf.hpp>
#include <boost/math/distributions.hpp>
#include <sstream>
#include "List.H"
#include "fvCFD.H" 

#include "alphaBetaPdf.c" 
#include "fErrInv.c" 
#include "makeGrid.h"


/////   main code

int main(int argc, char *argv[])
{
  #include "setRootCase.H"
  #include "createTime.H"
  #include "createMesh.H"

// first step : read imput data
  #include "createFields.H"
for (int i=0; i < NhNorm_Param ;i++ )
{
// second step : read laminar flamelet data 
  #include "readLamFlamelet.h"
// third step : main code for making turbulence flamelet library
  #include "mainTurbLib.h"
// fourth step : export table for turbulence library
  #include "exportTurbFlamelet.h"
}
  return 0;
}

