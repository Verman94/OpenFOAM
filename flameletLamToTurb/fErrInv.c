//*****************************************************//
//						       //
//         this code is for evaluating errfinv         //
//						       //
//*****************************************************//
void fErrInv(double *z, int l, double *fZ_)
{
   double x ;
   x = (z[l]+z[l+1])/2.;
   double img = boost::math::erf_inv(2*x-1);

   *fZ_ = std::exp(-2* std::pow(img,2) );
}

