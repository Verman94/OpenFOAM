//*****************************************************//
//						       //
//this code is for making primery Grid for Zhat and  ..//
//						       //
//*****************************************************//

//uniform Meshing of zHat
//for (int i=0; i<Nz_Hat; ++i)    z_Hat[i] = z_HatB + i*(z_HatU-z_HatB)/(Nz_Hat-1);

//make the list of z_hat	non Uniform


   for (int i=0; i < floor(Nz_Hat/2) ;i++ )     z_Hat[i] = z_HatB+ i*(z_HatU/20.-z_HatB)/(floor(Nz_Hat/2));
   for (int i=floor(Nz_Hat/2); i < Nz_Hat ;i++ )     z_Hat[i] = z_HatU/20.+ (i-floor(Nz_Hat/2))*(z_HatU-z_HatU/20.)/(Nz_Hat-floor(Nz_Hat/2)-1.0);



//make the list of z_Prime2Hat	uniform

   for (int i=0; i<Nz_Prime2Hat; ++i)    z_Prime2Hat[i] = z_Prime2HatB + i*(z_Prime2HatU-z_Prime2HatB)/(Nz_Prime2Hat-1);

//uniform Meshing of chiHat

for (int i=0; i<Nchi_Hat; ++i)    chi_Hat[i] = chi_HatB + i*(chi_HatU-chi_HatB)/(Nchi_Hat-1);

//uniform Meshing of hNorm

for (int i=0; i<NhNorm_Hat; ++i)    hNorm_Hat[i] = hNorm_HatB + i*(hNorm_HatU-hNorm_HatB)/(NhNorm_Hat-1);
