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

#include "FRSResonanceGenerator.h"

#include <TLorentzVector.h>
#include <TRandom1.h>
#include "TRandom.h"
#include <TVector3.h>

#include <FairLogger.h>
#include <FairPrimaryGenerator.h>

Bool_t FRSResonanceGenerator::Init()
{
    massDelta=1.232;
    wDelta=0.109;
    massRoper=1.440;
    wRoper=0.200;
    massproton=0.938272;
    massneutron=0.939565;
    masspion=0.13957018;
    fvx = 0.;
    fvy = 0.;
    fvz = 0.;
    fBeta.SetXYZ(0.,0.,0.9237);
    return kTRUE;
}

Bool_t FRSResonanceGenerator::ReadEvent(FairPrimaryGenerator* primGen)
{
    double rp = gRandom->Uniform(0.,1.0);
    if(rp<0.5){

    double r = gRandom->Uniform(0.,1.0);
    if(r<0.25)
       TargetExcitation(primGen,massDelta,wDelta,massproton);
    else if(r<0.6666)
       TargetExcitation(primGen,massDelta,wDelta,massneutron);
    else
       TargetExcitation(primGen,massRoper,wRoper,massproton);

/*    }else if(rp<0.5){

       TargetExcitation2pi(primGen,massRoper,wRoper,massneutron);
*/
    }else {
    double r = gRandom->Uniform(0.,1.0);
    if(r<0.25/2.)
       ProjectileExcitation(primGen,massDelta,wDelta,massneutron);
    else if(r<0.25)
       ProjectileExcitation(primGen,massDelta,wDelta,massproton);
    else if(r<(0.25+0.75/2.))
       ProjectileExcitation(primGen,massRoper,wRoper,massproton);
    else
       ProjectileExcitation(primGen,massRoper,wRoper,massneutron);
    }

    return kTRUE;
}

void FRSResonanceGenerator::ProjectileExcitation(FairPrimaryGenerator* primGen, Double_t mres, Double_t wres, Double_t mnucleon)
{
 Double_t MD = gRandom->BreitWigner(mres, wres);
 auto mom = DecayCM(MD, mnucleon, masspion);
 lvpion1.SetPxPyPzE(mom.X(),mom.Y(),mom.Z(),TMath::Sqrt(mom.Mag2()+masspion*masspion));
 lvpion1.Boost(fBeta);
 primGen->AddTrack(-211, lvpion1.X(), lvpion1.Y(), lvpion1.Z(), fvx, fvy, fvz);

 lvn.SetPxPyPzE(-mom.X(),-mom.Y(),-mom.Z(),TMath::Sqrt(mom.Mag2()+mnucleon*mnucleon));
 lvn.Boost(fBeta);
 if(mnucleon==massproton)
  primGen->AddTrack(2212, lvn.X(), lvn.Y(), lvn.Z(), fvx, fvy, fvz);
 else if(mnucleon==massneutron)
  primGen->AddTrack(2112, lvn.X(), lvn.Y(), lvn.Z(), fvx, fvy, fvz);

 return;
}

void FRSResonanceGenerator::TargetExcitation(FairPrimaryGenerator* primGen, Double_t mres, Double_t wres, Double_t mnucleon)
{
 Double_t MD = gRandom->BreitWigner(mres, wres);
 auto mom = DecayCM(MD, mnucleon, masspion);
 primGen->AddTrack(211, mom.X(), mom.Y(), mom.Z(), fvx, fvy, fvz);

 if(mnucleon==massproton)
  primGen->AddTrack(2212, -mom.X(), -mom.Y(), -mom.Z(), fvx, fvy, fvz);
 else if(mnucleon==massneutron)
  primGen->AddTrack(2112, -mom.X(), -mom.Y(), -mom.Z(), fvx, fvy, fvz);

 return;
}

void FRSResonanceGenerator::TargetExcitation2pi(FairPrimaryGenerator* primGen, Double_t mres, Double_t wres, Double_t mnucleon)
{
 // Decay in Delta+pi -> 2 pi + p
 // Final state: neutron + pi+ + pi-
 TLorentzVector lvdelta;

 again:

 Double_t MR = gRandom->BreitWigner(massRoper, wRoper);
 Double_t MD = gRandom->BreitWigner(massDelta, wDelta);

 if(MR<0 || MD<0)goto again;

 auto momD= DecayCM(MR,MD,masspion);
 //lvpion1.SetPxPyPzE(momD.X(),momD.Y(),momD.Z(),sqrt(momD.Mag2()+masspion*masspion));
 lvdelta.SetPxPyPzE(-momD.X(),-momD.Y(),-momD.Z(),sqrt(momD.Mag2()+MD*MD));

 double betadelta = lvdelta.Beta();
 boostdelta.SetMagThetaPhi(betadelta,lvdelta.Theta(),lvdelta.Phi());
 lvdelta.Boost(boostdelta);

 //std::cout <<"a:" <<MR<< " "<<MD<< " "<< boostdelta.Mag() << " "<< momD.Mag()  << std::endl;

 auto momD2= DecayCM(lvdelta.M(),mnucleon,masspion);
 //lvpion2.SetPxPyPzE(momD2.X(),momD2.Y(),momD2.Z(),sqrt(momD2.Mag2()+masspion*masspion));
 //lvproton1.SetPxPyPzE(-momD2.X(),-momD2.Y(),-momD2.Z(),sqrt(momD2.Mag2()+massp*massp));

 //std::cout <<"a:" << boostdelta.Mag()  << " "<< momD2.Mag()  << std::endl;

 primGen->AddTrack(211, momD.X(), momD.Y(), momD.Z(), fvx, fvy, fvz);
 primGen->AddTrack(-211, momD2.X(), momD2.Y(), momD2.Z(), fvx, fvy, fvz);
 primGen->AddTrack(2112, -momD2.X(), -momD2.Y(), -momD2.Z(), fvx, fvy, fvz);

 return;
}

TVector3 FRSResonanceGenerator::DecayCM(Double_t M, Double_t m1, Double_t m2)
{
 TVector3 p;
 Double_t px,py,pz;
 p.SetXYZ(0.,0.,0.);
 if(M<m1+m2)M=m1+m2+0.00001;
 Double_t mom = sqrt( (M*M-(m1+m2)*(m1+m2))*(M*M - (m1-m2)*(m1-m2)) )/2./M;
 auto rand = new TRandom1;
 rand->Sphere(px,py,pz,1.0);
 p.SetXYZ(mom*px,mom*py,mom*pz);
 return p;
}

void FRSResonanceGenerator::SetLorentzBoost(TVector3& beta) { fBeta = beta; }

ClassImp(FRSResonanceGenerator)
