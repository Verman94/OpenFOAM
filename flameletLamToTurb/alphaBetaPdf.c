//*****************************************************//
//						       //
//           this code is for evaluating pdf           //
//						       //
//*****************************************************//
using namespace   boost::math;

void alphaBetaPdf(int Nz, double *z, double mean, double var, double *PDF)
{
	double tmp,alpha,beta,z_,sumPdf,dz,dz1,dz2;
	double truncateVar= 1e-10,tmpU=1000,tmpB=0;

	mean = fmin(1.0, fmax(0.0, mean));
//	var  = fmin(fmax(0.0, var), mean*(1.0 - mean));
	var  = mean*(1.0 - mean)*var/0.25;


	if (var == 0.)
	 {
	  if ((mean == 0.) || (mean == 1.))
	    {tmp = tmpU;}
	  else
	   {tmp = tmpU;}
	 }
	else
	 {tmp = mean*(1.-mean)/var - 1.;}

	alpha = fmax(mean*tmp , truncateVar);
	beta  = fmax((1.-mean)*tmp , truncateVar);

	if (fabs(alpha - 1.) < 1.0e-6) alpha = 1.0;
  	if (fabs(beta - 1.)  < 1.0e-6) beta = 1.0;

	if (fabs(alpha)  < 1.0e-6) alpha = 1.0e-6;
	if (fabs(beta)  < 1.0e-6) beta = 1.0e-6;	

        beta_distribution<> d1(alpha, beta);

	sumPdf=0.;

      	for (int l=1; l<Nz-2; ++l) 
       	{
	 z_=(z[l]+z[l+1])/2.;
	 dz = z[l+1]-z[l];
	 PDF[l] = pdf(d1,z_);
	 sumPdf += (PDF[l]*dz);
        }

	if ((alpha > 1) && (beta > 1))
	{
	 dz1=z[1]-z[0];
	 dz2= z[Nz-1]-z[Nz-2];
	 PDF[0] = (1.-sumPdf)/(2.*dz1);
	 PDF[Nz-2] = (1.-sumPdf)/(2.*dz2);
	}
	else if ((alpha <= 1) && (beta > 1))
	// PDF Singularity at Z = 0
	{
	 z_=(z[Nz-2]+z[Nz-1])/2.;
	 dz = z[Nz-1]-z[Nz-2];
	 dz1=z[1]-z[0];	 
	 PDF[Nz-2] = pdf(d1,z_);
	 sumPdf += (PDF[Nz-2]*dz);
	 PDF[0] = (1.-sumPdf)/dz1;
	}	
	else if ((alpha > 1) && (beta <= 1))
	// PDF Singularity at Z = 1
	{
	 z_=(z[0]+z[1])/2.;
	 dz = z[1]-z[0];
	 dz2= z[Nz-1]-z[Nz-2];
	 PDF[0] = pdf(d1,z_);
	 sumPdf +=(PDF[0]*dz);
	 PDF[Nz-2] = (1.-sumPdf)/dz2;
	}

	else if ((alpha <= 1) && (beta <= 1))
	// PDF Singularity at Z = 1 and Z = 0
	{
	//First Edition
/*	 dz1=z[1]-z[0];
	 dz2= z[Nz-1]-z[Nz-2];
	 PDF[0] = (1.-sumPdf)/(2.*dz1);
	 PDF[Nz-2] = (1.-sumPdf)/(2.*dz2);  */

	//Second Edition
/*	 dz1=z[1]-z[0];
	 dz2= z[Nz-1]-z[Nz-2];
	PDF[0] =pdf(d1,dz1/2.0);
	PDF[Nz-2] = pdf(d1,1-dz2/2.0);	*/

	//Third Edition: Linearization
/*	PDF[0] = PDF[1]+(-dz1*(PDF[2]-PDF[1]))/(z[2]-z[1]);
	 sumPdf +=(PDF[0]*dz1);
	 PDF[Nz-2] = (1.-sumPdf)/(dz2);	*/

	//Forth Edition
/*	 dz1=z[1]-z[0];
	 dz2= z[Nz-1]-z[Nz-2];
	 PDF[0] = (1.-sumPdf)/(dz1)*(beta/(alpha+beta));
	 PDF[Nz-2] = (1.-sumPdf)/(dz2)*(alpha/(alpha+beta));	*/

	PDF[Nz-2] =   1.5*PDF[Nz-3] / beta;
     	PDF[0] =  1.5*PDF[1] / alpha;
	}
	else 
	{
	std::cout << "this pdf bound is not defined " <<  '\n'; 
	}

}
