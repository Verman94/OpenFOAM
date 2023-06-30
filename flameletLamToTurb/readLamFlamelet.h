//*****************************************************//
//						       //
//   this code is for reading laminar flamelet data    //
//						       //
//*****************************************************//
std::string tableName;
std::string delimeter = ",";
std::string line = "";
std::vector<std::string> flameletTableFormat;
std::vector<std::vector<std::vector<double> > > phi_L;
int iii=0;


std::fstream file; 

std::stringstream ihNorm;
ihNorm << hNorm_Param[i];

   phi_L.resize(Nchi0);

   for (int i=0; i<Nchi0 ;i++ )
   {
      	std::stringstream ii;
      	
     	ii << chi0[i];
	tableName = tableFileName + "/hNorm" + ihNorm.str() + "/Table_" + ii.str() + ".csv"; 

   	file.open(tableName.c_str());
      	std::cout << "opening: " << tableName.c_str() << '\n';

	iii = 0;
	while (getline(file, line))     
	{
	  std::vector<std::string> vec;
	  std::vector<double> doubleVec;
	  boost::algorithm::split(vec, line, boost::is_any_of(delimeter)); 
	  doubleVec.resize(vec.size());

	  if ( (iii==0) && (i==0) )
	   {
 	    flameletTableFormat = vec;
	   }
	  else if ( (iii==0) && (i>0) )
	   {
	    	for (unsigned int j=0; j<flameletTableFormat.size(); j++ )
		 {
		  if (vec[j].compare(flameletTableFormat[j]) != 0)
		     {
		      std::cout << "flameletTableFormat of " << tableName.c_str() << " is not match " << '\n';
		     }
		/*  else
		     {	
		      std::cout << "flameletTableFormat is match " << '\n';		     
		     } */
  		 }
	   }
          else 
	   {
	    phi_L[i].resize(iii);
	    std::transform(vec.begin(), vec.end(), doubleVec.begin(), [](const std::string & astr){ return stod( astr) ; } ) ;
	    phi_L[i][iii-1] = doubleVec;
           }
	   iii++;
	}
	file.close();
    }

//find the Z_N

   for (unsigned int i=0; i<flameletTableFormat.size() ;i++ )
    {
 	if (Zmf.compare(flameletTableFormat[i]) == 0) 	{Z_N=i;}
    }

