//*****************************************************//
//						       //
//       this code is for converting chi to chi0       //
//						       //
//*****************************************************//
intF=0.;

 for (int l=0; l<Nz-1; ++l)  
  {
   dx = z[l+1]-z[l];
   fErrInv(z, l, &fZ_);
   intF += (PDF[l] * fZ_ * dx);       
  }

chiS = chi_Hat[i] / intF;
//chiS = chi_Hat[i];


 chiRange=0;
 chi0State=Nchi0-2;
 deltaChiU = 0.;
 deltaChiB = chi0[Nchi0-1]-chi0[Nchi0-2];
 for (int l=0; l<Nchi0-1; ++l)  
  {
   
   if ((chiS >= chi0[l]) && (chiS <= chi0[l+1])) 
    {
     chi0State=l;
     deltaChiU = chi0[l+1]-chiS;
     deltaChiB = chiS-chi0[l];
     chiRange=1;
     break;
    }

  }

if ( chiRange == 0 ) 
{
     std::cout << "chiS is not in range" << "   chi_Hat[i]=  "<<chi_Hat[i]<< "   z_Hat[j]=  " <<z_Hat[j]<< "  z_Prime2Hat[k]=  " <<z_Prime2Hat[k]<<"  chiS=   "<< chiS<< "  intF=   "<< intF<<  '\n';     
}
