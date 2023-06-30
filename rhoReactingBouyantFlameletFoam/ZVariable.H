// Solve the mixture fraction equation

fvScalarMatrix zHatEqn
    (
	(
	  fvm::ddt(rho, zHat)
	+ fvm::div(phi, zHat)
        - fvm::laplacian((ViscT/schmit+turbulence->mut()/schmitT), zHat)
        )
    );
    zHatEqn.relax();
    fvOptions.constrain(zHatEqn);
    zHatEqn.solve(mesh.solver("zHat"));
    zHat.correctBoundaryConditions();

    const compressible::LESModel& lesModel =
        zHat.db().lookupObject<compressible::LESModel>
        (
            turbulenceModel::propertiesName
        );
    const volScalarField& delta = lesModel.delta();


// evaluate the zPrime2Hat
if (Z_Prime2Hat_Models == 1)  { zPrime2Hat = cZPrime2Hat * pow(delta,2.) * magSqr(fvc::grad(zHat)); }
else if (Z_Prime2Hat_Models == 2)
{
  fvScalarMatrix zPrime2HatEqn
    (
	(
	  fvm::ddt(rho, zPrime2Hat)
	+ fvm::div(phi, zPrime2Hat)
        - fvm::laplacian((ViscT/schmit+turbulence->mut()/schmitT), zPrime2Hat)
	==
	 Cg*(turbulence->mut())*(magSqr(fvc::grad(zHat)))
         - Cd*(rho*chiHat/cChiHat)
        )
    );
    zPrime2HatEqn.relax();
    fvOptions.constrain(zPrime2HatEqn);
    zPrime2HatEqn.solve(mesh.solver("zPrime2Hat"));
}
zPrime2Hat.correctBoundaryConditions();
bound(zPrime2Hat,0);

// evaluate the chiHat

chiHat = cChiHat * (turbulence->epsilon() / turbulence->k()) * zPrime2Hat; ///test
chiHat.correctBoundaryConditions();
bound(chiHat,0);
    Info<< "min/max(zPrime2Hat) = "
        << min(zPrime2Hat).value() << ", " << max(zPrime2Hat).value() << endl;

    Info<< "min/max(chiHat) = "
        << min(chiHat).value() << ", " << max(chiHat).value() << endl;


