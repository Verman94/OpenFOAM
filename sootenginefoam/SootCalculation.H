Teps = turbulence->epsilon();
Tk   = turbulence->k();

forAll(T,celli)
{
	
	////////////////////////////////////////////


	Yfuel[celli] = composition.Y("C7H16") [celli];
	Yoxid[celli] = composition.Y("O2") [celli];
	YCO2[celli] = composition.Y("CO2") [celli];
	YH2O[celli] = composition.Y("H2O") [celli];
	YN2[celli] = composition.Y("N2") [celli];
	fuelToOxidAc[celli] = Yfuel[celli]/Yoxid[celli];
	equR[celli] = fuelToOxidAc[celli] / fuelToOxidSt;
	nfuel[celli]=Yfuel[celli] / MwFuel ;	// mol C7H16
	noxid[celli]=Yoxid[celli] / O2e.W();
	nH2O[celli]=YH2O[celli] / MWH2O;
	nCO2[celli]=YCO2[celli] / MWCO2;
	nN2[celli]=YN2[celli] / N2e.W();
	molFracfuel[celli] = nfuel[celli]/(nfuel[celli]+noxid[celli]+nCO2[celli]+nH2O[celli]+nN2[celli]);
	molFracOxid[celli] = noxid[celli]/(nfuel[celli]+noxid[celli]+nCO2[celli]+nH2O[celli]+nN2[celli]);
	Poxid[celli] = molFracOxid[celli] * p[celli] * 1e-5;
/*	
	if (equR[celli]>MinEqr && equR[celli]<MaxEqr)
	   {
	   	//Khan and Greeves soot formation model
		Rsootform[celli] = Cs * molFracfuel[celli] *p[celli] * ::pow(equR[celli],rex) * ::exp(-Tac/T[celli]);
	   }
		else
	   {
		Rsootform[celli] = 0.0;
	   }
	//Magnussen and Hjertager oxidization model
	coefs[celli] = Teps[celli] / Tk[celli];		
	R1[celli]=Amagnus * rho[celli] * Ysoot[celli] * coefs[celli] ;
	coefs2[celli] = (Yoxid[celli]/muSoot)*((Ysoot[celli]*muSoot)/(Yfuel[celli]*muFuel+Ysoot[celli]*muSoot+1e-10));
	R2[celli]=Amagnus*rho[celli]*coefs2[celli]*coefs[celli];
	RsootComb[celli] = min(R1[celli],R2[celli]);
*/	
	//Hiroyasu soot formation model		
	Rsootform[celli] = Af * ::pow(p[celli] * 1e-5,0.5) * ::exp(-6313 / T[celli]) * Yfuel[celli];
	
//	RsootComb[celli] = Ao * ::pow(Poxid[celli]/21000 ,0.5) * ::exp(-7070 / T[celli]) * Ysoot[celli];

	//Nagle and Strickland-Constable oxidization model
	ka = 20.0 * ::exp(-15100/T[celli]);	// g/cm2,s,atm
	kz = 21.3 * ::exp(2060/T[celli]);	// atm ^ -1
	kb = 4.46E-03 * ::exp(-7640/T[celli]); // g/cm2,s,atm
	kt = 1.51E+05 * ::exp(-48800/T[celli]); // g/cm2,s
	
	xa = Poxid[celli] /  (Poxid[celli] + (kt / kb));
	Rtot = (ka * Poxid[celli]) / (1 + kz * Poxid[celli]) * xa + kb * Poxid[celli] * (1 - xa);
	RsootComb[celli] = 6.0 * Ao * Mwc / rhos / dsoot * Rtot * Ysoot[celli];
	
	Rsoot[celli] = Rsootform[celli] - RsootComb[celli];	

}


// Transport equation for soot mass fraction
fvScalarMatrix YsootEqn 
  (
        fvm::ddt(rho, Ysoot)
      + mvConvection->fvmDiv(phi, Ysoot)
      - fvm::laplacian(turbulence->muEff(), Ysoot)
      ==
         Rsoot
   );
YsootEqn.relax();
fvOptions.constrain(YsootEqn);
YsootEqn.solve(mesh.solver("Ysoot"));
fvOptions.correct(Ysoot);
Ysoot.correctBoundaryConditions();

