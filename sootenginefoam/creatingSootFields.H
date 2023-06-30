Info<< "Reading sootProperties\n" << endl;

IOdictionary sootProperties
(
    IOobject
    (
        "sootProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

//////////////////////////////////////////////////////////////
scalar MwFuel(readScalar(sootProperties.lookup("MwFuel"))); //  (100.204)
scalar rex(readScalar(sootProperties.lookup("rex"))); // equivalence ratio exponent (3.0)
scalar Cs(readScalar(sootProperties.lookup("Cs"))); // soot formation constant (kg/N-m-s) (1.5)
scalar Tac(readScalar(sootProperties.lookup("Tac"))); // activation temperature of soot formation rate (K) (20000)
scalar fuelToOxidSt(readScalar(sootProperties.lookup("fuelToOxidSt"))); // stoichi fuel-to-oxidizer based on mass (0.066221657 for c7h16)
scalar Amagnus(readScalar(sootProperties.lookup("Amagnus"))); // magnussen constant for soot combustion (4.0)
scalar muSoot(readScalar(sootProperties.lookup("muSoot"))); //  (2.6667)
scalar muFuel(readScalar(sootProperties.lookup("muFuel"))); //  (3.6363)
scalar MaxEqr(readScalar(sootProperties.lookup("MaxEqr"))); //  (3.0)
scalar MinEqr(readScalar(sootProperties.lookup("MinEqr"))); //  (1.67)

scalar Af(readScalar(sootProperties.lookup("Af"))); //  (1.67)
scalar Ao(readScalar(sootProperties.lookup("Ao"))); //  (1.67)

scalar Mwc   = 12.011;	//relative molecular mass of C (g/mol)
scalar rhos  = 2.0;	// the soot particle density (g/cm3)
scalar dsoot = 2.5E-06;	// diameter of soot particle (cm)
scalar Pref = 26173;  // (pa)
scalar MWH2O = 18.015;
scalar MWCO2 = 44.01 ;

scalar Rtot = 0;
scalar ka = 0;
scalar kz = 0;
scalar kb = 0;
scalar kt = 0;
scalar xa = 0;

volScalarField fuelToOxidAc(0.0*Y[0]);
volScalarField Yfuel(0.0*Y[0]);
volScalarField Yoxid(0.0*Y[0]);
volScalarField YH2O(0.0*Y[0]);
volScalarField YCO2(0.0*Y[0]);
volScalarField YN2(0.0*Y[0]);
volScalarField nCO2(0.0*Y[0]);
volScalarField nH2O(0.0*Y[0]);
volScalarField nN2(0.0*Y[0]);
volScalarField Poxid(0.0*Y[0]);

volScalarField R1(0.0*Y[0]);
volScalarField R2(0.0*Y[0]);
volScalarField noxid(0.0*Y[0]);
volScalarField nfuel(0.0*Y[0]);
volScalarField coefs(0.0*Y[0]);
volScalarField coefs2(0.0*Y[0]);


// equivalance ratio
volScalarField equR
(
    IOobject
    (
        "equR",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("zero", dimless, 0.0)
);
// moleFraction
volScalarField molFracOxid
(
    IOobject
    (
        "molFracOxid",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("molFracOxid", dimless, 0.0)
);

volScalarField molFracfuel
(
    IOobject
    (
        "molFracfuel",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("molFracfuel", dimless, 0.0)
);
// soot  mass  fraction
volScalarField Ysoot
(
    IOobject
    (
        "Ysoot",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("zero", dimless, 0.0),
    zeroGradientFvPatchScalarField::typeName
);

// net rate of soot generation (kg/ m^3 -s)
volScalarField Rsoot
(
    IOobject
    (
        "Rsoot",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("Rsoot", dimensionSet(1,-3,-1,0,0,0,0), 0.0)
);

//soot formation
volScalarField Rsootform
(
    IOobject
    (
        "Rsootform",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("Rsootform", dimensionSet(1,-3,-1,0,0,0,0), 0.0)
);

//soot combustion
volScalarField RsootComb
(
    IOobject
    (
        "RsootComb",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("RsootComb", dimensionSet(1,-3,-1,0,0,0,0), 0.0)
);

volScalarField Tk
(
    IOobject
    (
        "Tk",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("Tk", dimensionSet(0,2,-2,0,0,0,0), 0.0)
);


volScalarField Teps
(
    IOobject
    (
        "Teps",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar("Teps", dimensionSet(0,2,-3,0,0,0,0), 0.0)
);


