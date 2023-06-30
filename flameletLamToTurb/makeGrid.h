//*****************************************************//
//						       //
//             this code is for making Grid            //
//						       //
//*****************************************************//







void makeGridZ(int Nz, int Nz_Hat, int Nz_Prime2Hat, double zU, double zB, double z_HatU, double z_HatB,
	       double z_Prime2HatU, double z_Prime2HatB, double *z, double *z_Hat, double *z_Prime2Hat)
{
//for (int i=0; i<Nz; ++i)    z[i] = zB + i*(zU-zB)/(Nz-1);

   for (int i=0; i < floor(Nz/2) ;i++ )     z[i] = zB+ i*(zU/20.-zB)/(floor(Nz/2));
   for (int i=floor(Nz/2); i < Nz ;i++ )     z[i] = zU/20.+ (i-floor(Nz/2))*(zU-zU/20.)/(Nz-floor(Nz/2)-1.0);

//for (int i=0; i<Nz_Hat; ++i)    z_Hat[i] = z_HatB + i*(z_HatU-z_HatB)/(Nz_Hat-1);

//non uniform zHat
   for (int i=0; i < floor(Nz_Hat/2) ;i++ )     z_Hat[i] = z_HatB+ i*(z_HatU/20.-z_HatB)/(floor(Nz_Hat/2));
   for (int i=floor(Nz_Hat/2); i < Nz_Hat ;i++ )     z_Hat[i] = z_HatU/20.+ (i-floor(Nz_Hat/2))*(z_HatU-z_HatU/20.)/(Nz_Hat-floor(Nz_Hat/2)-1.0);


for (int i=0; i<Nz_Prime2Hat; ++i)    z_Prime2Hat[i] = z_Prime2HatB + i*(z_Prime2HatU-z_Prime2HatB)/(Nz_Prime2Hat-1);
}


void makeGridChi( int Nchi_Hat, double chi_HatU, double chi_HatB, double *chi_Hat)
{
for (int i=0; i<Nchi_Hat; ++i)    chi_Hat[i] = chi_HatB + i*(chi_HatU-chi_HatB)/(Nchi_Hat-1);
}

void makeGridhNorm( int NhNorm_Param, double hNorm_HatU, double hNorm_HatB, double *hNorm_Hat)
{
for (int i=0; i<NhNorm_Param; ++i)    hNorm_Hat[i] = hNorm_HatB + i*(hNorm_HatU-hNorm_HatB)/(NhNorm_Param-1);
}

