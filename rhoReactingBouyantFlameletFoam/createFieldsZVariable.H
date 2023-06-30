//Header for flameletReader

Info<< "Reading ZVariableProperties\n" << endl;

IOdictionary ZVariableProperties
(
    IOobject
    (
        "ZVariableProperties",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ_IF_MODIFIED,
        IOobject::NO_WRITE
    )
);

const string Q_dot(ZVariableProperties.lookup("Q_dot"));   // Q_dot==rate of Q
const string T_T(ZVariableProperties.lookup("T_T"));   // T_T==Temperature from the Table
const string Rho_T(ZVariableProperties.lookup("Densit"));   // Density from Table
const string Cp_T(ZVariableProperties.lookup("Specific_heat")); // Cp from Table
const string Visc_T(ZVariableProperties.lookup("viscosit")); // Visc from Table
const string Alpha_T(ZVariableProperties.lookup("Diffusivity")); // Diffusivity from Table
const string Mol_weight(ZVariableProperties.lookup("Mol_weight")); // Mol_weight from Table
const string enthalpy(ZVariableProperties.lookup("Enthalpy")); // Enthalpy from Table

const string flameletModelc(ZVariableProperties.lookup("flameletModel"));
int flameletModel = atoi(flameletModelc.c_str());

const string cDZHatt(ZVariableProperties.lookup("cDZHat"));
double cDZHat = atof(cDZHatt.c_str());

const string cZPrime2Hatt(ZVariableProperties.lookup("cZPrime2Hat"));
double cZPrime2Hat = atof(cZPrime2Hatt.c_str());

const string cChiHatt(ZVariableProperties.lookup("cChiHat"));
double cChiHat = atof(cChiHatt.c_str());

const string Pratt(ZVariableProperties.lookup("Prat"));
double Prat = atof(Pratt.c_str());

const string PratTt(ZVariableProperties.lookup("PratT"));
double PratT = atof(PratTt.c_str());

/////
//int
const string Nz_Hatt(ZVariableProperties.lookup("Nz_Hat"));
int Nz_Hat = atoi(Nz_Hatt.c_str());

const string Nz_Prime2Hatt(ZVariableProperties.lookup("Nz_Prime2Hat"));
int Nz_Prime2Hat = atoi(Nz_Prime2Hatt.c_str());

const string Nchi_Hatt(ZVariableProperties.lookup("Nchi_Hat"));
int Nchi_Hat = atoi(Nchi_Hatt.c_str());

const string NhNorm_Hatt(ZVariableProperties.lookup("NhNorm_Hat"));
int NhNorm_Hat = atoi(NhNorm_Hatt.c_str());

const string Z_Prime2Hat_Modelss(ZVariableProperties.lookup("Z_Prime2Hat_Models"));
int Z_Prime2Hat_Models = atoi(Z_Prime2Hat_Modelss.c_str());

const string T_Modelss(ZVariableProperties.lookup("T_Models"));
int T_Models = atoi(T_Modelss.c_str());

//double
const string z_HatUU(ZVariableProperties.lookup("z_HatU"));
double z_HatU = atof(z_HatUU.c_str());

const string hNorm_HatUU(ZVariableProperties.lookup("hNorm_HatU"));
double hNorm_HatU = atof(hNorm_HatUU.c_str());

const string z_Prime2HatUU(ZVariableProperties.lookup("z_Prime2HatU"));
double z_Prime2HatU = atof(z_Prime2HatUU.c_str());

const string chi_HatUU(ZVariableProperties.lookup("chi_HatU"));
double chi_HatU= atof(chi_HatUU.c_str());

const string z_HatBB(ZVariableProperties.lookup("z_HatB"));
double z_HatB = atof(z_HatBB.c_str());

const string hNorm_HatBB(ZVariableProperties.lookup("hNorm_HatB"));
double hNorm_HatB = atof(hNorm_HatBB.c_str());

const string z_Prime2HatBB(ZVariableProperties.lookup("z_Prime2HatB"));
double z_Prime2HatB = atof(z_Prime2HatBB.c_str());

const string chi_HatBB(ZVariableProperties.lookup("chi_HatB"));
double chi_HatB= atof(chi_HatBB.c_str());

const string schmitt(ZVariableProperties.lookup("schmit"));
double schmit= atof(schmitt.c_str());

const string schmitTt(ZVariableProperties.lookup("schmitT"));
double schmitT= atof(schmitTt.c_str());

const string Cgt(ZVariableProperties.lookup("Cg"));
double Cg= atof(Cgt.c_str());

const string Cdt(ZVariableProperties.lookup("Cd"));
double Cd= atof(Cdt.c_str());

const string pReft(ZVariableProperties.lookup("pRef"));
double pRef = atof(pReft.c_str());

/////
double  z_Hat[Nz_Hat] , z_Prime2Hat[Nz_Prime2Hat] , chi_Hat[Nchi_Hat] , hNorm_Hat[NhNorm_Hat] ;


//////////////////////////////////////////////////////////////////////////////

bool coupledRho(ZVariableProperties.lookupOrDefault("coupledRho",true));
List<word> specieExport_param (ZVariableProperties.lookup("specieExport_param"));


///////////////////////////////////////////////////////////////////////////////

Info<< "Reading field zHat\n" << endl;
volScalarField zHat
(
    IOobject
    (
        "zHat",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field zPrime2Hat\n" << endl;
volScalarField zPrime2Hat
(
    IOobject
    (
        "zPrime2Hat",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh
);

Info<< "Reading field chiHat\n" << endl;
volScalarField chiHat
(
    IOobject
    (
        "chiHat",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh
);


volScalarField RhoT
(
    IOobject
    (
        "RhoT",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimMass/dimVolume, Zero)
);


volScalarField ViscT
(
    IOobject
    (
        "ViscT",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimMass/dimLength/dimTime, Zero)
);


volScalarField CpT
(
    IOobject
    (
        "CpT",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimEnergy/dimMass/dimTemperature, Zero)
);


volScalarField AlphaT
(
    IOobject
    (
        "AlphaT",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(pow(dimLength,2)/dimTime, Zero)
);


volScalarField QdotTEqn
(
    IOobject
    (
        "QdotTEqn",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimMass*dimTemperature/dimVolume/dimTime, Zero)
);


volScalarField MolweightT
(
    IOobject
    (
        "MolweightT",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimMass/dimMoles, Zero)
);

volScalarField TT
(
    IOobject
    (
        "TT",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimTemperature, Zero)
);


volScalarField CPTInv
(
    IOobject
    (
        "CPTInv",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimTemperature*dimMass/dimEnergy, Zero)
);

volScalarField drhodt
(
    IOobject
    (
        "drhodt",
        runTime.timeName(),
        mesh,
        IOobject::READ_IF_PRESENT,
        IOobject::AUTO_WRITE
    ),
    mesh,
    dimensionedScalar(dimDensity/dimTime, Zero)
);

