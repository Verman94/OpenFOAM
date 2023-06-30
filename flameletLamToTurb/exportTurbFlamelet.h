//*****************************************************//
//						       //
//    this code is for exporting Tutbulence Library    //
//						       //
//*****************************************************//
std::string tableExport;
std::ofstream outfile;

string preExporter = tableExportName + "/hNorm" + ihNorm.str();
frt = mkr + preExporter;
std::cout << '\n'<< '\n' << "Calculating new Enthalpy defect: " << '\n' << '\n' << '\n';
system(frt.c_str());

for (int i=0; i<Nchi_Hat ;i++ )
  {
     std::stringstream ii;
     ii << chi_Hat[i];

   for (int j=0; j<Nz_Prime2Hat ;j++ )
    {
     std::stringstream jj;
     jj << z_Prime2Hat[j];
     tableExport = preExporter +"/chiHat" + ii.str() + "_zPrime2Hat" + jj.str() + ".csv"; 
     outfile.open(tableExport.c_str());

//write the specices 
     for (int k = 0; k < flameletTableFormat.size(); k++)
     {
      outfile<<flameletTableFormat[k]<<",";
     }
     outfile<<'\n';

//write the values of specices 
     for (int m=0; m<Nz_Hat ;m++ )
     {
    	    for (int n = 0; n < phi_T[i][m][j].size(); n++)
	    {
	      if (n==Z_N)
		{outfile<<z_Hat[m]<<",";}
	      else
		{outfile<<phi_T[i][m][j][n]<<",";}
	    }
          outfile<<'\n';
     }

     outfile.close();
     std::cout << "export: " << tableExport.c_str() << '\n';
    }
  }
