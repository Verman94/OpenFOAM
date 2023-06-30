Info<< "Mean volume:" << gSum(mesh.V()) << endl;
Info<< "Mean pressure:" << p.weightedAverage(mesh.V()).value() << endl;
Info<< "Mean temperature:" << T.weightedAverage(mesh.V()).value() << endl;
Info<< "Mean NOx:" << YNOx.weightedAverage(mesh.V()).value() << endl;
Info<< "Mean Soot:" << Ysoot.weightedAverage(mesh.V()).value() << endl;
Info<< "Mean u':"
    << (sqrt((2.0/3.0)*turbulence->k()))().weightedAverage(mesh.V()).value()
    << endl;

logSummaryFile
    << runTime.theta() << tab
    << gSum(mesh.V()) << tab
    << p.weightedAverage(mesh.V()).value() << tab
    << T.weightedAverage(mesh.V()).value() << tab
    << YNOx.weightedAverage(mesh.V()).value() << tab
    << Ysoot.weightedAverage(mesh.V()).value() << tab
    << Qdot.weightedAverage(mesh.V()).value()*gSum(mesh.V())/(6*2000) << tab
    << (sqrt((2.0/3.0)*turbulence->k()))().weightedAverage(mesh.V()).value()
    << endl;
