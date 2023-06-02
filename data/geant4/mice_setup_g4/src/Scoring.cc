#include "Analysis.hh"

using namespace std;

void Analysis::Fill(scored_quatity sd){
  sdata = sd;
  // auto analysisManager = G4AnalysisManager::Instance();
  pos_edep[0] = sdata.EnergyDepositPoint.x();
  pos_edep[1] = sdata.EnergyDepositPoint.y();
  pos_edep[2] = sdata.EnergyDepositPoint.z();
  for(int i = 0; i<num_Histograms; i++){
    WDF  = 1;
    WEF  = 1;
    WSPF = 1;
    if(histo_watequ[i]){
      WDF = sdata.WatDoseFactor;
      WEF = sdata.WatEnergyFactor;
      WEF = sdata.WatSPFactor;
    }
    if(histo_xmin[i]<=pos_edep[0] && pos_edep[0] <histo_xmax[i] &&
       histo_ymin[i]<=pos_edep[1] && pos_edep[1] <histo_ymax[i] &&
       histo_zmin[i]<=pos_edep[2] && pos_edep[2] <histo_zmax[i]){
         // Placeholder for Dose Scoring
         if((histo_quantityID[i] == 1)){
           if((histo_particleID[i] == ALL_PARTICLES)){
               FillHisto(i, WDF*(sdata.EnergyDeposit/joule)/(sdata.MaterialDensity*histo_binVolume[i]/m3));
            }

           else if(2212 == sdata.ParticlePDGcode){
               FillHisto(i, WDF*(sdata.EnergyDeposit/joule)/(sdata.MaterialDensity*histo_binVolume[i]/m3));
           }
         }
         // Placeholder for Energy Scoring
         else if(histo_quantityID[i] == 2){
           if(histo_particleID[i] == ALL_PARTICLES) {
             FillHisto(i, (WEF*sdata.EnergyDeposit/keV));
           }
           else if(histo_particleID[i] == sdata.ParticlePDGcode){
             FillHisto(i, (WEF*sdata.EnergyDeposit/keV));
           }
         }
         // Placeholder for Fluence Scoring
         else if(histo_quantityID[i] == 3){
           if(histo_particleID[i] == ALL_PARTICLES) {
             FillHisto(i, (sdata.StepLength/cm)/(histo_binVolume[i]/cm3));
           }
           else if(histo_particleID[i] == sdata.ParticlePDGcode){
             FillHisto(i, (sdata.StepLength/cm)/(histo_binVolume[i]/cm3));
           }
         }
         // Placeholder for LETd (actual)  Scoring
         else if(histo_quantityID[i] == 4){
           if(histo_particleID[i] == ALL_PARTICLES) {
             FillHisto(i, (WEF*sdata.EnergyDeposit/keV)*(WEF*sdata.StoppingPower/(keV/um)));
           }
           else if(histo_particleID[i] == sdata.ParticlePDGcode){
             FillHisto(i, (WEF*sdata.EnergyDeposit/keV)*(WEF*sdata.StoppingPower/(keV/um)));
           }
         }
         // Placeholder for LETt (actual)  Scoring
         else if(histo_quantityID[i] == 5){
           if(histo_particleID[i] == ALL_PARTICLES) {
             FillHisto(i, WSPF*(sdata.StepLength/um)*(sdata.StoppingPower/(keV/um)));
           }
           else if(histo_particleID[i] == sdata.ParticlePDGcode){
             FillHisto(i, WEF*(sdata.StepLength/um)*(sdata.StoppingPower/(keV/um)));
           }
         }
         // Placeholder for LETd (Calculated)  Scoring
         else if(histo_quantityID[i] == 6){
           if(histo_particleID[i] == ALL_PARTICLES) {
             FillHisto(i, WEF*(sdata.EnergyDeposit/keV*sdata.EnergyDeposit/keV)/sdata.StepLength/um);
           }
           else if(histo_particleID[i] == sdata.ParticlePDGcode){
             FillHisto(i, WEF*(sdata.EnergyDeposit/keV*sdata.EnergyDeposit/keV)/sdata.StepLength/um);
           }
         }
         // Placeholder for LETt (Calculated)  Scoring
         else if(histo_quantityID[i] == 7){
           if(histo_particleID[i] == ALL_PARTICLES) {
             FillHisto(i, WEF*(sdata.StepLength/um*sdata.EnergyDeposit/keV)/sdata.StepLength/um);
           }
           else if(histo_particleID[i] == sdata.ParticlePDGcode){
             FillHisto(i, WEF*(sdata.StepLength/um*sdata.EnergyDeposit/keV)/sdata.StepLength/um);
           }
         }
         // Placeholder for Kerma  Scoring
         else if(histo_quantityID[i] == 8){
           if(histo_particleID[i] == ALL_PARTICLES) {
             FillHisto(i, (sdata.StepLength/cm)/(histo_binVolume[i]*cm3));
           }
           else if(histo_particleID[i] == sdata.ParticlePDGcode){
             FillHisto(i, (sdata.StepLength/cm)/(histo_binVolume[i]*cm3));
           }
         }
         // Placeholder for Dose (Fluence)  Scoring
         else if(histo_quantityID[i] == 9 && sdata.StoppingPower!=0 && sdata.StepLength !=0){
           if(histo_particleID[i] == ALL_PARTICLES){ //&& sdata.EnergyDeposit!=0) {
             FillHisto(i, WDF*((sdata.StoppingPower*(e_SI/pow(10, -9)))/(sdata.MaterialDensity))*((sdata.StepLength/m)/(histo_binVolume[i]/m3)));
           }
           else if(histo_particleID[i] == sdata.ParticlePDGcode){
             FillHisto(i, WDF*((sdata.StoppingPower*(e_SI/pow(10, -9)))/(sdata.MaterialDensity))*((sdata.StepLength/m)/(histo_binVolume[i]/m3)));
           }
         }
         // Placeholder for Step length Scoring
         else if(histo_quantityID[i] == 10){
           if(histo_particleID[i] == ALL_PARTICLES) {
             FillHisto(i, sdata.StepLength/um);
           }
           else if(histo_particleID[i] == sdata.ParticlePDGcode){
             FillHisto(i, sdata.StepLength/um);
           }
         }
         // Placeholder for Particle Scoring
         else if(histo_quantityID[i] == 0){
           if(histo_particleID[i] == ALL_PARTICLES) {
             // FillHisto(i, WDF*((sdata.StoppingPower/joule/m)/(sdata.MaterialDensity))*((sdata.StepLength/m)/(histo_binVolume[i]*m3)));
           }
           else if(histo_particleID[i] == sdata.ParticlePDGcode){
               // FillHisto(i, WDF*((sdata.StoppingPower/joule/m)/(sdata.MaterialDensity))*((sdata.StepLength/m)/(histo_binVolume[i]*m3)));
           }
         }

         else {
           continue;
         }
       }
    }
}

int Analysis::GetQuantityCode(string quantity){
  if     (StringCompare(quantity, "Dose"))      {return 1;}
  else if(StringCompare(quantity, "Energy"))    {return 2;}
  else if(StringCompare(quantity, "Fluence"))   {return 3;}
  else if(StringCompare(quantity, "aLETd"))     {return 4;}
  else if(StringCompare(quantity, "aLETt"))     {return 5;}
  else if(StringCompare(quantity, "fLETd"))     {return 6;}
  else if(StringCompare(quantity, "fLETt"))     {return 7;}
  else if(StringCompare(quantity, "Kerma"))     {return 8;}
  else if(StringCompare(quantity, "fDose"))     {return 9;}
  else if(StringCompare(quantity, "SLEN"))      {return 10;}
  else if(StringCompare(quantity, "Particle"))  {return 0;}
  else                                          {return -1;}
}

void Analysis::FillHisto(int histoIndex, double value){
  auto analysisManager = G4AnalysisManager::Instance();
  if(histo_particleType[histoIndex] == 0){
    if     (histo_dimension[histoIndex] == 1){analysisManager->FillH1(histo[histoIndex], pos_edep[histo_xaxis[histoIndex]], value);}
    else if(histo_dimension[histoIndex] == 2){analysisManager->FillH2(histo[histoIndex], pos_edep[histo_xaxis[histoIndex]],
                                                                                         pos_edep[histo_yaxis[histoIndex]], value);}
    else if(histo_dimension[histoIndex] == 3){analysisManager->FillH3(histo[histoIndex], pos_edep[histo_xaxis[histoIndex]],
                                                                                         pos_edep[histo_yaxis[histoIndex]],
                                                                                         pos_edep[histo_zaxis[histoIndex]], value);}
  }

  else if(histo_particleType[histoIndex] == sdata.ParticleGenType){
    if     (histo_dimension[histoIndex] == 1){analysisManager->FillH1(histo[histoIndex], pos_edep[histo_xaxis[histoIndex]], value);}
    else if(histo_dimension[histoIndex] == 2){analysisManager->FillH2(histo[histoIndex], pos_edep[histo_xaxis[histoIndex]],
                                                                                         pos_edep[histo_yaxis[histoIndex]], value);}
    else if(histo_dimension[histoIndex] == 3){analysisManager->FillH3(histo[histoIndex], pos_edep[histo_xaxis[histoIndex]],
                                                                                         pos_edep[histo_yaxis[histoIndex]],
                                                                                         pos_edep[histo_zaxis[histoIndex]], value);}
  }
}
