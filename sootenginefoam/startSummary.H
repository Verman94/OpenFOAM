Info<< "Total cylinder mass: " << fvc::domainIntegrate(rho).value() << endl;
//Info<< "Total fuel mass: "
//    << fvc::domainIntegrate(rho*compostion.ft()).value() << endl;

OFstream logSummaryFile
(
    runTime.path()/("logSummary." + runTime.timeName() + ".dat")
);

logSummaryFile
    << "CA" << tab << "v" << tab << "p" << tab <<"T" << tab <<"NOX" << tab << "Soot" << tab <<"Qdot(J/deg)" << tab <<"u'" << endl;
