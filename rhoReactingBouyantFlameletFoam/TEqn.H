{
// Solve the total enthalpy equation
 radiation->correct();
 if (T_Models == 3)  
 { 

//    dimensionedScalar Hc ("Hc",dimensionSet(1,-1,-3,0,0,0,0),scalar(0.0001));


    fvScalarMatrix hHatEqn
    (
        fvm::ddt(rho,hHat)
      + fvm::div(phi, hHat)
      + fvc::ddt(rho, K) + fvc::div(phi, K)
      - dpdt
      - fvm::laplacian( (ViscT/Prat+turbulence->mut()/PratT) , hHat)

     ==

	 radiation->ShHat(T,hHat)
       +  fvOptions(rho,hHat)
    );

    hHatEqn.relax();

    fvOptions.constrain(hHatEqn);

    hHatEqn.solve();
    fvOptions.correct(hHat);
 }
 #include "YFind.H"    

 if ((T_Models == 1) || (T_Models == 3) )  
 { 
    for (int l=0; l<T.size() ;l++ ) {T[l] = TT[l];}
    T.correctBoundaryConditions();
//    if (T_Models == 3 & T[i]<300.0 ) T[i] == 300
 }
 else if (T_Models == 2)
 {
    volScalarField& he = thermo.he();

    fvScalarMatrix TEqn
    (
        fvm::ddt(rho,T)
      + fvm::div(phi, T)
      + CPTInv*fvc::ddt(rho, K) + CPTInv*fvc::div(phi, K)
      + CPTInv*(
            he.name() == "e"
          ? fvc::div
            (
                fvc::absolute(phi/fvc::interpolate(rho), U),
                p,
                "div(phiv,p)"
            )
          : -dpdt
        )

      - fvm::laplacian( (ViscT/Prat+turbulence->mut()/PratT) , T)
     ==
        QdotTEqn
      + CPTInv*radiation->ST(T)
      + fvOptions(rho,T)
    );

    TEqn.relax();

    fvOptions.constrain(TEqn);

    TEqn.solve();
    fvOptions.correct(T);
 }
 

 if (coupledRho)  
    { for (int ll=0; ll<rho.size() ;ll++ )  { rho[ll] = min(p[ll],pRef) * MolweightT[ll] / (8.314 * T[ll]);   }  }
 else
    { for (int l=0; l<rho.size() ;l++ )  {rho[l] = RhoT[l];} }
 thermo.rho()=rho;
 rho.correctBoundaryConditions();
 RhoT = rho;
 RhoT.correctBoundaryConditions();

 thermo.mu() = ViscT*p/p;

    Info<< "min/max(T) = "
        << min(T).value() << ", " << max(T).value() << endl;
}
