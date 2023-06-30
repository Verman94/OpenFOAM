//*****************************************************//
//						       //
//     this code is for making Tutbulence Library      //
//						       //
//*****************************************************//
double intPhi;

for (int m=0; m<flameletTableFormat.size(); ++m)
{
 intPhi=0.;
 for (int l=0; l<Nz-1; ++l)  
  {
     dx = z[l+1]-z[l];
     int z_range1=0;
     int z_range2=0;

     for (int n=0; n<phi_L[chi0State].size()-1; ++n)  
      {
 	if ( ((phi_L[chi0State][n][Z_N]>=z[l]) && (phi_L[chi0State][n+1][Z_N]<=z[l])) || 							  ((phi_L[chi0State][n][Z_N]<=z[l]) && (phi_L[chi0State][n+1][Z_N]>=z[l])) ) 
    	{
    	 phiLB=deltaChiU/(deltaChiB+deltaChiU)*phi_L[chi0State][n][m];
	 z_range1=1;
	 break;
   	}
      }


     for (int n=0; n<phi_L[chi0State+1].size()-1; ++n)  
      {
	if ( ((phi_L[chi0State+1][n][Z_N]>=z[l]) && (phi_L[chi0State+1][n+1][Z_N]<=z[l])) || 								((phi_L[chi0State+1][n][Z_N]<=z[l]) && (phi_L[chi0State+1][n+1][Z_N]>=z[l])) )
    	{
    	 phiLU=deltaChiB/(deltaChiB+deltaChiU)*phi_L[chi0State+1][n][m];
	 z_range2=1;
	 break;
   	}
      }

      if ((z_range1 == 0) || (z_range2 == 0)) 
    	{
    	 std::cout << "z is not in range and  " <<"  z_range1 ==  "<< z_range1<<"  z_range2 ==  "<< z_range2  << '\n';
   	}
	//PDF_=PDF[l];
    intPhi += (PDF[l] * (phiLB+phiLU) * dx);
  }
   phi_T[i][j][k][m]=intPhi;
}
