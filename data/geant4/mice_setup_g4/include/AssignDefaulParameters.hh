#ifndef AssignDefaultParameters_h
#define AssignDefaultParameters_h 1

#include <vector>
#include "DataType.hh"

using namespace std;

void DefaultBeamParameters(std::vector<string> bp, beam_parameter *beam){
  beam->particle = "proton";
  beam->energy   = 150.0;
  beam->e_spread = 1.5;
  beam->type     = "GAUSSIAN";
  if(bp.size()>5){
    beam->position[0] = 0;
    beam->position[1] = 0.0;
    beam->position[2] = 0.0;
    beam->position[3] = -500.0;
  }
  if(bp.size()>7){
    beam->sad[0] = 1;
    beam->sad[1] = 2500.0;
    beam->sad[2] = 2000.0;
  }
  return;
}

#endif
