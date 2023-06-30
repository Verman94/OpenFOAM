//*****************************************************//
//						       //
//   this code is for reading Turbulent Library data   //
//						       //
//*****************************************************//

std::string tableFileName = "turbTables/hNorm";
std::string tableName;
std::string delimeter = ",";
std::string line = "";
std::vector<std::string> flameletTableFormat;
std::vector<std::vector<std::vector<std::vector<std::vector<double> > > > >phi_T;
int iii=0, Q_dot_N, Rho_T_N, Cp_T_N, Visc_T_N, Alpha_T_N, Mol_weight_N, TempT_N, EnthT_N;

std::fstream file; 
phi_T.resize(NhNorm_Hat);
for (int ih=0; ih<NhNorm_Hat ;ih++ )
{
std::stringstream ihh;
ihh<<hNorm_Hat[ih];
phi_T[ih].resize(Nchi_Hat);
for (int i=0; i<Nchi_Hat ;i++ )
  {
     std::stringstream ii;
     ii << chi_Hat[i];
     phi_T[ih][i].resize(Nz_Prime2Hat);
   for (int j=0; j<Nz_Prime2Hat ;j++ )
    {
     std::stringstream jj;
     jj << z_Prime2Hat[j];

     tableName = tableFileName.c_str() + ihh.str() + "/chiHat" + ii.str() + "_zPrime2Hat" + jj.str() + ".csv"; 

  	file.open(tableName.c_str());
      	std::cout << "opening: " << tableName.c_str() << '\n';

	iii = 0;
	while (getline(file, line))     
	{
	  std::vector<std::string> vec;
	  std::vector<double> doubleVec;
	  boost::algorithm::split(vec, line, boost::is_any_of(delimeter)); 
	  doubleVec.resize(vec.size());

	  if ( (iii==0) && (i==0) && (j==0) )
	   {
 	    flameletTableFormat = vec;
	   }
	  else if ( (iii==0) && ((i>0) || ((j>0))) )
	   {
	    	for (unsigned int k=0; k<flameletTableFormat.size(); k++ )
		 {
		  if (vec[k].compare(flameletTableFormat[k]) != 0)
		     {
		      std::cout << "flameletTableFormat of " << tableName.c_str() << " is not match " << '\n';
		     }
		  else
		     {	
		    //  std::cout << "flameletTableFormat is match " << '\n';		     
		     } 
  		 }
	   }
          else 
	   {
	    phi_T[ih][i][j].resize(iii);

	    for (unsigned int k=0; k<vec.size(); k++ )  {doubleVec[k]=atof(vec[k].c_str());}
	    phi_T[ih][i][j][iii-1] = doubleVec;
           }
	   iii++;
	}
	file.close();

     std::cout << "import: " << tableName.c_str() << '\n';
    }
  }
}

   for (int i=0; i<flameletTableFormat.size() ;i++ )
    {
 	if (Q_dot.compare(flameletTableFormat[i]) == 0)	 	{Q_dot_N=i;}
	if (enthalpy.compare(flameletTableFormat[i]) == 0)	{EnthT_N=i;}
 	if (Rho_T.compare(flameletTableFormat[i]) == 0)	 	{Rho_T_N=i;}
 	if (Cp_T.compare(flameletTableFormat[i]) == 0)	 	{Cp_T_N=i;}
 	if (Visc_T.compare(flameletTableFormat[i]) == 0)	{Visc_T_N=i;}
 	if (Alpha_T.compare(flameletTableFormat[i]) == 0)	{Alpha_T_N=i;}
 	if (Mol_weight.compare(flameletTableFormat[i]) == 0)	{Mol_weight_N=i;}
 	if (T_T.compare(flameletTableFormat[i]) == 0)	 	{TempT_N=i;}
    }

     std::cout << "Q_dot_N= " << Q_dot_N << "/Rho_T_N= " << Rho_T_N << '\n';

