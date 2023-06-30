//*****************************************************//
//						       //
//      this is for taking input from the user         //
//						       //
//*****************************************************//


Info<< "Reading libVarInput\n" << endl;

IOdictionary libVarInput
(
    IOobject
    (
        "libVarInput",
        runTime.constant(),
        mesh,
        IOobject::MUST_READ,
        IOobject::NO_WRITE
    )
);

List<scalar> chi0 (libVarInput.lookup("chi0"));
List<scalar> hNorm_Param (libVarInput.lookup("hNorm_Param"));

///read int parameter
const string Nzz(libVarInput.lookup("Nz"));
int Nz = atoi(Nzz.c_str());

const string Nz_Hatt(libVarInput.lookup("Nz_Hat"));
int Nz_Hat = atoi(Nz_Hatt.c_str());

const string Nz_Prime2Hatt(libVarInput.lookup("Nz_Prime2Hat"));
int Nz_Prime2Hat = atoi(Nz_Prime2Hatt.c_str());

const string Nchi_Hatt(libVarInput.lookup("Nchi_Hat"));
int Nchi_Hat = atoi(Nchi_Hatt.c_str());



///read double parameter
const string zUu(libVarInput.lookup("zU"));
double zU = atof(zUu.c_str());

const string zBb(libVarInput.lookup("zB"));
double zB = atof(zBb.c_str());

const string z_HatUu(libVarInput.lookup("z_HatU"));
double z_HatU = atof(z_HatUu.c_str());

const string z_HatBb(libVarInput.lookup("z_HatB"));
double z_HatB = atof(z_HatBb.c_str());

const string z_Prime2HatUu(libVarInput.lookup("z_Prime2HatU"));
double z_Prime2HatU = atof(z_Prime2HatUu.c_str());

const string z_Prime2HatBb(libVarInput.lookup("z_Prime2HatB"));
double z_Prime2HatB = atof(z_Prime2HatBb.c_str());

const string chi_HatUu(libVarInput.lookup("chi_HatU"));
double chi_HatU = atof(chi_HatUu.c_str());

const string chi_HatBb(libVarInput.lookup("chi_HatB"));
double chi_HatB = atof(chi_HatBb.c_str());

const string hNorm_HatUu(libVarInput.lookup("hNorm_HatU"));
double hNorm_HatU = atof(hNorm_HatUu.c_str());

const string hNorm_HatBb(libVarInput.lookup("hNorm_HatB"));
double hNorm_HatB = atof(hNorm_HatBb.c_str());

int Nchi0 = chi0.size();
int NhNorm_Param = hNorm_Param.size();

/// other parameter and array
double z[Nz], z_Hat[Nz_Hat], z_Prime2Hat[Nz_Prime2Hat] ;
double chi_Hat[Nchi_Hat] ;
double hNorm_Hat[NhNorm_Param] ;



makeGridZ(Nz, Nz_Hat, Nz_Prime2Hat, zU, zB, z_HatU, z_HatB, z_Prime2HatU, z_Prime2HatB, z, z_Hat, z_Prime2Hat);
makeGridChi(Nchi_Hat, chi_HatU, chi_HatB, chi_Hat);
makeGridhNorm(NhNorm_Param, hNorm_HatU, hNorm_HatB, hNorm_Hat);

double PDF[Nz-1];
double dx, chiS;
double  intF, deltaChiU, deltaChiB;
double  fZ_,phiLB,phiLU;
int  chi0State,chiRange;

// parameter for read laminar library 
const string Zmf(libVarInput.lookup("mixtureFraction"));   // Z==mixture fraction
const string tableFileName(libVarInput.lookup("laminarTableImport"));   
const string tableExportName(libVarInput.lookup("turbulenceTableExport"));  
int Z_N;

//remove & create Turbulent Folder
const string mkr = "mkdir ";
const string rem = "rm -r ";
string zrt = rem + tableExportName;
system(zrt.c_str());
string frt = mkr + tableExportName;
system(frt.c_str());
