    PtrList<gasHThermoPhysics> specieData(Y.size());
    forAll(specieData, i)
    {
        specieData.set
        (
            i,
            new gasHThermoPhysics
            (
                dynamic_cast<const reactingMixture<gasHThermoPhysics>&>
                    (thermo).speciesData()[i]
            )
        );
    }
