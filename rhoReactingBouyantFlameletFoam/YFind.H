//*****************************************************//
//						       //
//this code is for finding data from Turbulent Library //
//						       //
//*****************************************************//

{

 for (int i=0; i<zHat.size() ;i++ )
   {
    std::vector<double> vecYF;

   if (flameletModel == 1)
      {
        #include "flameletModels/SLFM_TurbPhi.H"
      }
//Info<< "its here"<< endl;
/*
    for (int j=0; j<Y.size() ;j++ )
     {
	for (int k=0; k<vecYF.size() ;k++ ) 
	   { 
	     if (flameletTableFormat[k] == composition.species()[j])  { Y[j][i] = vecYF[k]; break;}    
     	   }
     }
*/
// evaluate the Y Component
    for (int j=0; j<specieExport_param.size() ;j++ )
     { 
	for(int ii=0; ii<thermo.composition().species().size() ;ii++) 
		{
		   if (specieExport_param[j]==composition.species()[ii])
			{
                           for (int k=0; k<vecYF.size() ;k++ ) 
				{ if (flameletTableFormat[k]==composition.species()[ii])  {Y[ii][i]=vecYF[k];break;} }
			}
		}	    
     }  
/*
      for (int j=0; j<thermo.composition().species().size();j++)
      {
         he[i] += Y[j][i] * abs(composition.Hs(j, pstd, T[i]));
      }
*/
     Qdot[i] = max(vecYF[Q_dot_N],0.);//Qdot[i] = vecYF[Q_dot_N];
     TT[i] = vecYF[TempT_N];
     RhoT[i] = vecYF[Rho_T_N];
     CpT[i] = vecYF[Cp_T_N];
     ViscT[i] = vecYF[Visc_T_N];
     AlphaT[i] = vecYF[Alpha_T_N];
     MolweightT[i] = vecYF[Mol_weight_N];
     QdotTEqn[i] = Qdot[i]/CpT[i];
     CPTInv[i]=1./CpT[i];
   } 
QdotTEqn.correctBoundaryConditions();
CPTInv.correctBoundaryConditions();
CpT.correctBoundaryConditions();
RhoT.correctBoundaryConditions();
ViscT.correctBoundaryConditions();
MolweightT.correctBoundaryConditions();
}
