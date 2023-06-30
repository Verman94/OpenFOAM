
int N_chiHat_B, N_zHat_B ,N_zPrime2Hat_B, N_hNormHat_B;
double del_chiHat_B, del_zHat_B, del_zPrime2Hat_B, del_hNormHat_B,h_non_adia,h_adia,norm_h;

int expChiRang = 0;
for (int m=0; m<Nchi_Hat-1 ;m++ )
  {
    if ( (chi_Hat[m] <= chiHat[i]) && (chiHat[i] < chi_Hat[m+1]) )
      {
       N_chiHat_B = m;
       del_chiHat_B = (chiHat[i] - chi_Hat[m]) / (chi_Hat[m+1] - chi_Hat[m]);
       expChiRang = 1;
       break;
      }
    else if ( chiHat[i] < chi_Hat[0] )
      {
       N_chiHat_B = 0;
       del_chiHat_B = 0.;
       expChiRang = 1;
       break;
      }
    else if ( chi_Hat[Nchi_Hat-1] <= chiHat[i] )
      {
       N_chiHat_B = Nchi_Hat-2;
       del_chiHat_B = 1.;
       expChiRang = 1;
       break;
      }
  }
if ( expChiRang == 0 ) {std::cout << "chiHat["<<i<<"] not in range and value is: " << chiHat[i] << '\n';}


int expzPrime2Rang = 0;
double zPrime2HatScaled = 0.25 * zPrime2Hat[i] / (zHat[i]*(1.0 - zHat[i])+1e-10);
for (int m=0; m<Nz_Prime2Hat-1 ;m++ )
  {
    if ( (z_Prime2Hat[m] <= zPrime2HatScaled) && (zPrime2HatScaled < z_Prime2Hat[m+1]) )
      {
       N_zPrime2Hat_B = m;
       del_zPrime2Hat_B = (zPrime2HatScaled - z_Prime2Hat[m]) / (z_Prime2Hat[m+1] - z_Prime2Hat[m]);
       expzPrime2Rang = 1;
       break;
      }
    else if ( zPrime2HatScaled < z_Prime2Hat[0] )
      {
       N_zPrime2Hat_B = 0.;
       del_zPrime2Hat_B = 0.;
       expzPrime2Rang = 1;
       break;
      }
    else if ( z_Prime2Hat[Nz_Prime2Hat-1] <= zPrime2HatScaled )
      {
       N_zPrime2Hat_B = Nz_Prime2Hat-2;
       del_zPrime2Hat_B = 1.;
       expzPrime2Rang = 1;
       break;
      }
  }
if ( expzPrime2Rang == 0 ) {std::cout << "zPrime2Hat["<<i<<"] not in range and value is: " << zPrime2HatScaled << '\n';}


int expZRang = 0;
for (int m=0; m<Nz_Hat-1 ;m++ )
  {
    if ( (z_Hat[m] <= zHat[i]) && (zHat[i] < z_Hat[m+1]) )
      {
       N_zHat_B = m;
       del_zHat_B = (zHat[i] - z_Hat[m]) / (z_Hat[m+1] - z_Hat[m]);
       expZRang = 1;
       break;
      }
    else if ( zHat[i] < z_Hat[0] )
      {
       N_zHat_B = 0;
       del_zHat_B = 0.;
       expZRang = 1;
       break;
      }
    else if ( z_Hat[Nz_Hat-1] <= zHat[i] )
      {
       N_zHat_B = Nz_Hat-2;
       del_zHat_B = 1.;
       expZRang = 1;
       break;
      }
  }
if ( expZRang == 0 ) {std::cout << "zHat["<<i<<"] not in range and value is: " << zHat[i] << '\n';}

///  normalize total enthalpy

//   step 1:: adiabatic Enthalpy

double A = (1.-del_zHat_B) * phi_T[0][N_chiHat_B][N_zPrime2Hat_B][N_zHat_B][EnthT_N] + 
            (del_zHat_B) * phi_T[0][N_chiHat_B][N_zPrime2Hat_B][N_zHat_B+1][EnthT_N];
double B = (1.-del_zHat_B) * phi_T[0][N_chiHat_B][N_zPrime2Hat_B+1][N_zHat_B][EnthT_N] + 
           (del_zHat_B) * phi_T[0][N_chiHat_B][N_zPrime2Hat_B+1][N_zHat_B+1][EnthT_N];
double C = (1.-del_zHat_B) * phi_T[0][N_chiHat_B+1][N_zPrime2Hat_B][N_zHat_B][EnthT_N] + 
           (del_zHat_B) * phi_T[0][N_chiHat_B+1][N_zPrime2Hat_B][N_zHat_B+1][EnthT_N];
double D = (1.-del_zHat_B) * phi_T[0][N_chiHat_B+1][N_zPrime2Hat_B+1][N_zHat_B][EnthT_N] + 
           (del_zHat_B) * phi_T[0][N_chiHat_B+1][N_zPrime2Hat_B+1][N_zHat_B+1][EnthT_N];

double AA = (1.-del_zPrime2Hat_B) * A + (del_zPrime2Hat_B) * B;
double BB = (1.-del_zPrime2Hat_B) * C + (del_zPrime2Hat_B) * D;

h_adia = (1.-del_chiHat_B) * AA + del_chiHat_B * BB;


//   step 2:: max non_adiabatic Enthalpy
A = (1.-del_zHat_B) * phi_T[NhNorm_Hat-1][N_chiHat_B][N_zPrime2Hat_B][N_zHat_B][EnthT_N] + 
            (del_zHat_B) * phi_T[NhNorm_Hat-1][N_chiHat_B][N_zPrime2Hat_B][N_zHat_B+1][EnthT_N];
B = (1.-del_zHat_B) * phi_T[NhNorm_Hat-1][N_chiHat_B][N_zPrime2Hat_B+1][N_zHat_B][EnthT_N] + 
           (del_zHat_B) * phi_T[NhNorm_Hat-1][N_chiHat_B][N_zPrime2Hat_B+1][N_zHat_B+1][EnthT_N];
C = (1.-del_zHat_B) * phi_T[NhNorm_Hat-1][N_chiHat_B+1][N_zPrime2Hat_B][N_zHat_B][EnthT_N] + 
           (del_zHat_B) * phi_T[NhNorm_Hat-1][N_chiHat_B+1][N_zPrime2Hat_B][N_zHat_B+1][EnthT_N];
D = (1.-del_zHat_B) * phi_T[NhNorm_Hat-1][N_chiHat_B+1][N_zPrime2Hat_B+1][N_zHat_B][EnthT_N] + 
           (del_zHat_B) * phi_T[NhNorm_Hat-1][N_chiHat_B+1][N_zPrime2Hat_B+1][N_zHat_B+1][EnthT_N];

AA = (1.-del_zPrime2Hat_B) * A + (del_zPrime2Hat_B) * B;
BB = (1.-del_zPrime2Hat_B) * C + (del_zPrime2Hat_B) * D;

h_non_adia = (1.-del_chiHat_B) * AA + del_chiHat_B * BB;

//   step 3:: evaluate total enthalpy
norm_h = (h_adia-hHat[i])/(h_adia-h_non_adia+0.0001);
if (norm_h < 0) {norm_h=0;}
if (norm_h > 1) {norm_h=1;}


int expHRang = 0;
for (int m=0; m<NhNorm_Hat-1 ;m++ )
  {
    if ( (hNorm_Hat[m] <= norm_h) && (norm_h < hNorm_Hat[m+1]) )
      {
       N_hNormHat_B = m;
       del_hNormHat_B = (norm_h - hNorm_Hat[m]) / (hNorm_Hat[m+1] - hNorm_Hat[m]);
       expHRang = 1;
       break;
      }
    else if ( norm_h < hNorm_Hat[0] )
      {
       N_hNormHat_B = 0;
       del_hNormHat_B = 0.;
       expHRang = 1;
       break;
      }
    else if ( hNorm_Hat[NhNorm_Hat-1] <= norm_h )
      {
       N_hNormHat_B = NhNorm_Hat-2;
       del_hNormHat_B = 1.;
       expHRang = 1;
       break;
      }
  }
if ( expHRang == 0 ) {std::cout << "hHat["<<i<<"] not in range and value is: " << norm_h << '\n';}

//interpolation
vecYF.resize(flameletTableFormat.size());
for (int m=0; m<vecYF.size() ;m++ )
  {
   double A0 = (1.-del_zHat_B) * phi_T[N_hNormHat_B][N_chiHat_B][N_zPrime2Hat_B][N_zHat_B][m] + 
            (del_zHat_B) * phi_T[N_hNormHat_B][N_chiHat_B][N_zPrime2Hat_B][N_zHat_B+1][m];
   double B0 = (1.-del_zHat_B) * phi_T[N_hNormHat_B][N_chiHat_B][N_zPrime2Hat_B+1][N_zHat_B][m] + 
           (del_zHat_B) * phi_T[N_hNormHat_B][N_chiHat_B][N_zPrime2Hat_B+1][N_zHat_B+1][m];
   double C0 = (1.-del_zHat_B) * phi_T[N_hNormHat_B][N_chiHat_B+1][N_zPrime2Hat_B][N_zHat_B][m] + 
           (del_zHat_B) * phi_T[N_hNormHat_B][N_chiHat_B+1][N_zPrime2Hat_B][N_zHat_B+1][m];
   double D0 = (1.-del_zHat_B) * phi_T[N_hNormHat_B][N_chiHat_B+1][N_zPrime2Hat_B+1][N_zHat_B][m] + 
           (del_zHat_B) * phi_T[N_hNormHat_B][N_chiHat_B+1][N_zPrime2Hat_B+1][N_zHat_B+1][m];


   double A1 = (1.-del_zHat_B) * phi_T[N_hNormHat_B+1][N_chiHat_B][N_zPrime2Hat_B][N_zHat_B][m] + 
            (del_zHat_B) * phi_T[N_hNormHat_B+1][N_chiHat_B][N_zPrime2Hat_B][N_zHat_B+1][m];
   double B1 = (1.-del_zHat_B) * phi_T[N_hNormHat_B+1][N_chiHat_B][N_zPrime2Hat_B+1][N_zHat_B][m] + 
           (del_zHat_B) * phi_T[N_hNormHat_B+1][N_chiHat_B][N_zPrime2Hat_B+1][N_zHat_B+1][m];
   double C1 = (1.-del_zHat_B) * phi_T[N_hNormHat_B+1][N_chiHat_B+1][N_zPrime2Hat_B][N_zHat_B][m] + 
           (del_zHat_B) * phi_T[N_hNormHat_B+1][N_chiHat_B+1][N_zPrime2Hat_B][N_zHat_B+1][m];
   double D1 = (1.-del_zHat_B) * phi_T[N_hNormHat_B+1][N_chiHat_B+1][N_zPrime2Hat_B+1][N_zHat_B][m] + 
           (del_zHat_B) * phi_T[N_hNormHat_B+1][N_chiHat_B+1][N_zPrime2Hat_B+1][N_zHat_B+1][m];

   double AA0 = (1.-del_zPrime2Hat_B) * A0 + (del_zPrime2Hat_B) * B0;
   double BB0 = (1.-del_zPrime2Hat_B) * C0 + (del_zPrime2Hat_B) * D0;
   double AA1 = (1.-del_zPrime2Hat_B) * A1 + (del_zPrime2Hat_B) * B1;
   double BB1 = (1.-del_zPrime2Hat_B) * C1 + (del_zPrime2Hat_B) * D1;

   double AAA0 = (1.-del_chiHat_B) * AA0 + del_chiHat_B * BB0;
   double BBB0 = (1.-del_chiHat_B) * AA1 + del_chiHat_B * BB1;

   vecYF[m] = (1.-del_hNormHat_B) * AAA0 + del_hNormHat_B * BBB0;
  }

