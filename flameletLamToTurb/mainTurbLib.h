//*****************************************************//
//						       //
//            main part : include lam to turb          //
//						       //
//*****************************************************//
std::vector<std::vector<std::vector<std::vector<double> > > > phi_T;
phi_T.resize(Nchi_Hat);

for (int i=0; i<Nchi_Hat; ++i)  
{
  phi_T[i].resize(Nz_Hat);

  for (int j=0; j<Nz_Hat; ++j)  
  {
    phi_T[i][j].resize(Nz_Prime2Hat);

    for (int k=0; k<Nz_Prime2Hat; ++k)  
    {
      phi_T[i][j][k].resize(flameletTableFormat.size());
	alphaBetaPdf(Nz, z, z_Hat[j], z_Prime2Hat[k], PDF);

      #include "convChiToChi0.h"
      #include "makeTurbLib.h"
    }
  }

}
