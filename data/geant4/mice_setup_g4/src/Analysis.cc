#include "Analysis.hh"
#include "G4AutoDelete.hh"
#include "G4ParticleTable.hh"

G4ThreadLocal Analysis *the_analysis = 0;

Analysis::Analysis(){

}

Analysis::~Analysis(){

}

Analysis *Analysis::GetAnalysis() {
      if (!the_analysis) {
          the_analysis = new Analysis();
          G4AutoDelete::Register(the_analysis);
      }
  return the_analysis;
}

void Analysis::SetAnalysis(SimulationParameters* aSMP){
  SMP   = aSMP;
  WDF   = 1;
  WEF   = 1;
}

void Analysis::Book() {
  auto analysisManager = G4AnalysisManager::Instance();
  num_Histograms = (int)SMP->GetHistogramParameters().size();
  for(int i = 0; i<num_Histograms; i++){
    histogram_parameter h = SMP->GetHistogramParameters()[i];
    int dimension = h.numbers[0], x = 0, y = 0, z = 0;
    if(dimension == 1){
      x = h.numbers[10]-1;
      y = -1;
      z = -1;
      histo.push_back(analysisManager->CreateH1(h.name, h.title, h.numbers[(3*x)+1], h.numbers[(3*x)+2], h.numbers[(3*x)+3]));
      histo_dimension.push_back(dimension);
      histo_xaxis.push_back(x);
      histo_yaxis.push_back(y);
      histo_zaxis.push_back(z);
    }

    else if(dimension == 2){
      x = h.numbers[10]-1;
      y = h.numbers[11]-1;
      z = -1;
      histo.push_back(analysisManager->CreateH2(h.name, h.title, h.numbers[(3*x)+1], h.numbers[(3*x)+2], h.numbers[(3*x)+3],
                                                                 h.numbers[(3*y)+1], h.numbers[(3*y)+2], h.numbers[(3*y)+3]));
      histo_dimension.push_back(dimension);
      histo_xaxis.push_back(x);
      histo_yaxis.push_back(y);
      histo_zaxis.push_back(-1);
    }
    else if(dimension == 3){
      x = h.numbers[10]-1;
      y = h.numbers[11]-1;
      z = h.numbers[12]-1;
      histo.push_back(analysisManager->CreateH3(h.name, h.title, h.numbers[(3*x)+1], h.numbers[(3*x)+2], h.numbers[(3*x)+3],
                                                                 h.numbers[(3*y)+1], h.numbers[(3*y)+2], h.numbers[(3*y)+3],
                                                                 h.numbers[(3*z)+1], h.numbers[(3*z)+2], h.numbers[(3*z)+3]));
      histo_dimension.push_back(dimension);
      histo_xaxis.push_back(x);
      histo_yaxis.push_back(y);
      histo_zaxis.push_back(z);
    }

    histo_nBinx.push_back(h.numbers[1]);
    histo_nBiny.push_back(h.numbers[4]);
    histo_nBinz.push_back(h.numbers[7]);
    histo_xmin.push_back(h.numbers[2]);
    histo_xmax.push_back(h.numbers[3]);
    histo_ymin.push_back(h.numbers[5]);
    histo_ymax.push_back(h.numbers[6]);
    histo_zmin.push_back(h.numbers[8]);
    histo_zmax.push_back(h.numbers[9]);
    histo_binVolume.push_back(GetBinVolume(i));
    histo_quantity.push_back(h.quantity);
    histo_particleName.push_back(h.particle);
    histo_watequ.push_back(h.waterEquivalent);
    histo_quantityID.push_back(GetQuantityCode(h.quantity));
    histo_particleID.push_back(GetPGDCode(h.particle));
    histo_particleType.push_back(h.particleType);
  }
}

void Analysis::Open(){
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->OpenFile(SMP->GetSetupParameters().out_file);
}

void Analysis::Save(){
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(SMP->GetSetupParameters().out_file);
  analysisManager->Write();
}

void Analysis::Close(){
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->CloseFile();
}

double Analysis::GetBinVolume(int i){
   histogram_parameter h = SMP->GetHistogramParameters()[i];
   double x_lenght = (h.numbers[3] - h.numbers[2])/h.numbers[1];
   double y_lenght = (h.numbers[6] - h.numbers[5])/h.numbers[4];
   double z_lenght = (h.numbers[9] - h.numbers[8])/h.numbers[7];
   double volume = x_lenght*y_lenght*z_lenght;
   return volume;
}

bool Analysis::StringCompare(string s1, string s2){
  transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
  transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
  if(s1.compare(s2) == 0){return true;}
  return false;
}

int Analysis::GetPGDCode(string name){
  if (StringCompare(name, "All")){
      return   ALL_PARTICLES;
  }
  else{
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particle = particleTable->FindParticle(name);
    return  particle->GetPDGEncoding(); }
}
