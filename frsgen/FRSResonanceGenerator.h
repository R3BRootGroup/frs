/******************************************************************************
 *   Copyright (C) 2019 GSI Helmholtzzentrum für Schwerionenforschung GmbH    *
 *   Copyright (C) 2019 Members of R3B Collaboration                          *
 *                                                                            *
 *             This software is distributed under the terms of the            *
 *                 GNU General Public Licence (GPL) version 3,                *
 *                    copied verbatim in the file "LICENSE".                  *
 *                                                                            *
 * In applying this license GSI does not waive the privileges and immunities  *
 * granted to it by virtue of its status as an Intergovernmental Organization *
 * or submit itself to any jurisdiction.                                      *
 ******************************************************************************/


#ifndef _FRSResonanceGenerator_H_
#define _FRSResonanceGenerator_H_

#include <TRandom1.h>
#include <TVector3.h>
#include <TLorentzVector.h>

#include <FairGenerator.h>

class FRSResonanceGenerator : public FairGenerator
{
  public:
    FRSResonanceGenerator()
        : FairGenerator("FRSResonanceGenerator", "FRSResonanceGenerator")
    {
    }
    FRSResonanceGenerator(const char* name, const char* title)
        : FairGenerator(name, title)
    {
    }

    virtual Bool_t Init();
    virtual Bool_t ReadEvent(FairPrimaryGenerator* primGen);

    /**
     * Simulate in-flight emission of Gamma rays: Defines beta of emitting system
     * relative to lab frame.
     *
     * @param beta Direction and velocity (relativistiv beta, i.e. v/c) of emitting system (moving ion)
     */
    void SetLorentzBoost(TVector3& beta);

  protected:
    TVector3 DecayCM(Double_t M, Double_t m1, Double_t m2);
    void TargetExcitation(FairPrimaryGenerator* primGen, Double_t mres, Double_t wres, Double_t mnucleon);
    void TargetExcitation2pi(FairPrimaryGenerator* primGen, Double_t mres, Double_t wres, Double_t mnucleon);
    void ProjectileExcitation(FairPrimaryGenerator* primGen, Double_t mres, Double_t wres, Double_t mnucleon);

    Double_t fvx, fvy, fvz;
    TVector3 fBeta;
    TVector3 boostdelta;
    TLorentzVector lvpion1;
    TLorentzVector lvpion2;
    TLorentzVector lvn;

    Double_t massneutron,massproton, masspion;
    Double_t massDelta, wDelta, massRoper, wRoper;

    ClassDef(FRSResonanceGenerator, 1);
};

#endif
