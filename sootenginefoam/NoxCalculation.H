basicMultiComponentMixture& composition = thermo.composition();

volScalarField Otest(0.0*Y[0]);
volScalarField OHtest(0.0*Y[0]);
/// fluent when concentrtion is mol/m^3 and coefficients are m3/mol.s

volScalarField  cNOx =  YNOx*rho/(NOe.W()/1000);
volScalarField  cOH  =  composition.Y("OH")*rho/(OHe.W()/1000);
volScalarField  cN2  =  composition.Y("N2")*rho/(N2e.W()/1000);
volScalarField  cO2  =  composition.Y("O2")*rho/(O2e.W()/1000);
volScalarField  cO   =  composition.Y("O")*rho/(Oe.W()/1000);
volScalarField  cH   =  composition.Y("H")*rho/(He.W()/1000);
volScalarField  cH2O   =  composition.Y("H2O")*rho/(18.01528/1000);


forAll(YNOx,celli)
{
	Otest[celli] = 3.97e5 * ::pow(T[celli],(-0.5)) * ::pow(cO2[celli],(0.5)) * ::exp(-31090/T[celli]);
//	Otest[celli] = 36.64 * ::pow(T[celli],(0.5)) * ::pow(cO2[celli],(0.5)) * ::exp(-27123/T[celli]);	//partial equlibrium
	OHtest[celli] = 2.129e2 * ::pow(T[celli],(-0.57)) * ::exp(-4595/T[celli]) * ::pow(Otest[celli] * cH2O[celli],(0.5));
	YOtest[celli] = Otest[celli]*(15.999/1000)/rho[celli];
	YOHtest[celli] = OHtest[celli]*(OHe.W()/1000)/rho[celli];
/*	
// m3/mol.s
	scalar k1pos = 1.8e8 * ::exp(-38370/T[celli]);
	scalar k2pos = 1.8e4 * T[celli] * ::exp(-4680/T[celli]);
	scalar k3pos = 7.1e7 * ::exp(-450/T[celli]);
	scalar k1neg = 3.8e7 * ::exp(-425/T[celli]);;
	scalar k2neg = 3.81e3 * T[celli] * ::exp(-20820/T[celli]);
	scalar k3neg = 1.7e8 * ::exp(-24560/T[celli]);
*/	

// doubiani coeffs	
	scalar k1pos = 7.6e7 * ::exp(-38000/T[celli]);
	scalar k2pos = 6.4e3 * T[celli] * ::exp(-3150/T[celli]);
	scalar k3pos = 4.1e7;
	scalar k1neg = 1.6e7;
	scalar k2neg = 1.5e3 * T[celli] * ::exp(-19500/T[celli]);
	scalar k3neg = 2e8 * ::exp(-23650/T[celli]);
	
	scalar K = (k1pos/k1neg)*(k2pos/k2neg);	
	scalar A = 2.0 * k1pos*Otest[celli]*cN2[celli];
	scalar B = 1.0 - ::pow(cNOx[celli],2.0)/(K*cO2[celli]*cN2[celli]);
	scalar C = 1.0 + k1neg*cNOx[celli]/(k2pos*cO2[celli]+k3pos*OHtest[celli]);
	RRNOx[celli] = A*B/C;
	RRNOx[celli] = 0.2 * RRNOx[celli] * (NOe.W() / 1000);// kg/m3.s
}


tmp<fv::convectionScheme<scalar> > mvConvection
(
	fv::convectionScheme<scalar>::New
	(
		mesh,
		fields,
		phi,
		mesh.divScheme("div(phi,Yi_h)")
	)
);
	
solve
(
	fvm::ddt(rho, YNOx)
	+ mvConvection->fvmDiv(phi, YNOx)
	- fvm::laplacian(turbulence->muEff(), YNOx)
	==
	RRNOx,
	mesh.solver("YNOx")
);
