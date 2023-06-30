volScalarField YNOx
(
    IOobject
    (
        "YNOx",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimless, Zero),
    zeroGradientFvPatchScalarField::typeName
);


volScalarField RRNOx
(
    IOobject
    (
        "RRNOx",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimensionSet (1,-3,-1,0,0), Zero),
    zeroGradientFvPatchScalarField::typeName
);


volScalarField YOtest
(
    IOobject
    (
        "YOtest",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimless, Zero)
);

volScalarField YOHtest
(
    IOobject
    (
        "YOHtest",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimless, Zero)

);


dictionary NOXDATA(thermo.subDict("NOxData"));
gasHThermoPhysics NOe(NOXDATA.subDict("NO"));
gasHThermoPhysics OHe(NOXDATA.subDict("OH"));
gasHThermoPhysics N2e(NOXDATA.subDict("N2"));
gasHThermoPhysics O2e(NOXDATA.subDict("O2"));
gasHThermoPhysics Ne(NOXDATA.subDict("N"));
gasHThermoPhysics Oe(NOXDATA.subDict("O"));
gasHThermoPhysics He(NOXDATA.subDict("H"));

