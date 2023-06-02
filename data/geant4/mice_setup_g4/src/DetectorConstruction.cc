#include "DetectorConstruction.hh"
#include "G4UserLimits.hh"
#include "G4NistManager.hh"
#include "G4Tubs.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"
#include "G4MultiUnion.hh"
#include "G4Region.hh"
#include "G4ProductionCuts.hh"

//****************************************************************************//

DetectorConstruction::DetectorConstruction(SimulationParameters* aSMP)
{
  SMP = aSMP;
  StepLimit = new G4UserLimits(SMP->GetPhysicsParameters().step_length);
  shift = (SMP->GetSetupParameters().n_pos - 1)*4.0;
}

//****************************************************************************//

DetectorConstruction::~DetectorConstruction()
{
  delete StepLimit;
}

//****************************************************************************//

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  // Construct World volume
  G4VPhysicalVolume* physical_world       = ConstructWorldVolume();
  G4VPhysicalVolume* physical_air         = ConstructAirVolume(physical_world->GetLogicalVolume());

  G4VPhysicalVolume* physical_container   = ConstructContainer(physical_air->GetLogicalVolume());
  physical_container->GetLogicalVolume()->SetUserLimits(StepLimit);
  ProCut.resize(ProCut.size()+1);
  ProCut.back().region = new G4Region("Region_Container");
  physical_container->GetLogicalVolume()->SetRegion(ProCut.back().region);
  ProCut.back().region->AddRootLogicalVolume(physical_container->GetLogicalVolume());
  ProCut.back().density = G4NistManager::Instance()->FindOrBuildMaterial("G4_PLEXIGLASS")->GetDensity()/(kg/m3);
  ProCut.back().mat = "G4_PLEXIGLASS";


  G4VPhysicalVolume* physical_water       = ConstructWater(physical_air->GetLogicalVolume());
  physical_water->GetLogicalVolume()->SetUserLimits(StepLimit);
  ProCut.resize(ProCut.size()+1);
  ProCut.back().region = new G4Region("Region_Water");
  physical_water->GetLogicalVolume()->SetRegion(ProCut.back().region);
  ProCut.back().region->AddRootLogicalVolume(physical_water->GetLogicalVolume());
  ProCut.back().density = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER")->GetDensity()/(kg/m3);
  ProCut.back().mat = "G4_WATER";

  G4VPhysicalVolume* physical_lid         = ConstructLid(physical_water->GetLogicalVolume());
  physical_lid->GetLogicalVolume()->SetUserLimits(StepLimit);
  ProCut.resize(ProCut.size()+1);
  ProCut.back().region = new G4Region("Region_Lid");
  physical_lid->GetLogicalVolume()->SetRegion(ProCut.back().region);
  ProCut.back().region->AddRootLogicalVolume(physical_lid->GetLogicalVolume());
  ProCut.back().density = G4NistManager::Instance()->FindOrBuildMaterial("G4_PLEXIGLASS")->GetDensity()/(kg/m3);
  ProCut.back().mat = "G4_PLEXIGLASS";

  G4VPhysicalVolume* physical_collimator  = ConstructBarCollimator(physical_air->GetLogicalVolume());

  int c;
  double cut_range, energy = 0.1;
  vector<G4ProductionCuts*> pcuts;
  const G4Region* constRegion;

  for(c = 0; c<(int)ProCut.size();c++){
    pcuts.resize(pcuts.size()+1);
    pcuts[pcuts.size()-1] = new G4ProductionCuts();
    constRegion = ProCut[c].region;
    cut_range =0.1*G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER")->GetDensity()/(kg/m3)/
                                ProCut[c].density;

    std::cout<<ProCut[c].mat<<"  "<<ProCut[c].density<<"  " << cut_range << '\n';
    pcuts[pcuts.size()-1]->SetProductionCut(cut_range, G4ProductionCuts::GetIndex("proton"));
    pcuts[pcuts.size()-1]->SetProductionCut(cut_range, G4ProductionCuts::GetIndex("gamma"));
    pcuts[pcuts.size()-1]->SetProductionCut(cut_range, G4ProductionCuts::GetIndex("e-"));
    pcuts[pcuts.size()-1]->SetProductionCut(cut_range, G4ProductionCuts::GetIndex("e+"));
    ProCut[c].region->SetProductionCuts(pcuts[pcuts.size()-1]);
  }
 return physical_world;
}

G4VPhysicalVolume* DetectorConstruction::ConstructWorldVolume(){
  G4Material* vacuum = G4NistManager::Instance()->FindOrBuildMaterial("G4_Galactic");
  G4bool checkOverlaps = true;

  // Construct World volume
  G4double world_x = 1000*mm, world_y = 1000*mm, world_z = 1600*mm;

  G4Box* solid_world             = new G4Box("World", world_x/2, world_y/2, world_z/2);
  G4LogicalVolume* logical_world =
               new G4LogicalVolume(solid_world,                           //its solid
                                   vacuum,                                //its material
                                   "world");                              //its name

  // Visual attributes of the world
  G4VisAttributes * world_visAtt = new G4VisAttributes(G4Colour(0.0,1.0,1.0));
  world_visAtt->SetForceWireframe(true);
  logical_world->SetVisAttributes(world_visAtt);

  // Physical placment of the world volume
  G4VPhysicalVolume* physical_world =
                    new G4PVPlacement(0,                                  //no rotation
                                      G4ThreeVector(),                    //at (0,0,0)
                                      logical_world,                      //its logical volume
                                      "world",                            //its name
                                      0,                                  //its mother  volume
                                      false,                              //no boolean operation
                                      0,                                  //copy number
                                      checkOverlaps);                     //overlaps checking
 return physical_world;
}

G4VPhysicalVolume* DetectorConstruction::ConstructAirVolume(G4LogicalVolume* MotherVolume){
  G4Material* air = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
  G4bool checkOverlaps = true;

  G4double air_x = 800*mm, air_y = 800*mm, air_z = 1400*mm;
  G4Box* solid_air             = new G4Box("air", air_x/2, air_y/2, air_z/2);
  G4LogicalVolume* logical_air =
             new G4LogicalVolume(solid_air,              //its solid
                                 air,                    //its material
                                 "air");                 //its name
  // Visual attributes of the air
  G4VisAttributes* air_visAtt = new G4VisAttributes(G4Colour(0.0,1.0,1.0));
  air_visAtt->SetForceWireframe(true);
  logical_air->SetVisAttributes(air_visAtt);

  // Physical placment of the air volume
  G4VPhysicalVolume* physical_air =
                  new G4PVPlacement(0,                   //no rotation
                                    G4ThreeVector(),     //at (0,0,0)
                                    logical_air,         //its logical volume
                                    "air",               //its name
                                    MotherVolume,        //its mother  volume
                                    false,               //no boolean operation
                                    0,                   //copy number
                                    checkOverlaps);      //overlaps checking
 return physical_air;
}

G4VPhysicalVolume* DetectorConstruction::ConstructContainer(G4LogicalVolume* MotherVolume){
  G4bool checkOverlaps = true;
  G4NistManager* nist = G4NistManager::Instance();
  G4Material* pmma = nist->FindOrBuildMaterial("G4_PLEXIGLASS");
  G4Transform3D Transformation3D;
  G4ThreeVector apos;


  G4Box* solid_phantom_out  = new G4Box("phantom_out", (SMP->GetPhantomOut()[1] - SMP->GetPhantomOut()[0])/2,
                                                       (SMP->GetPhantomOut()[3] - SMP->GetPhantomOut()[2])/2,
                                                       (SMP->GetPhantomOut()[5] - SMP->GetPhantomOut()[4])/2);

  G4Box* solid_phantom_in   = new G4Box("phantom_in",  (SMP->GetPhantomIn()[1] - SMP->GetPhantomIn()[0])/2,
                                                       (SMP->GetPhantomIn()[3] - SMP->GetPhantomIn()[2])/2,
                                                       (SMP->GetPhantomIn()[5] - SMP->GetPhantomIn()[4])/2);

 double xOutCenter   = SMP->GetPhantomOut()[1] - (SMP->GetPhantomOut()[1] - SMP->GetPhantomOut()[0])/2;
 double xInCenter    = SMP->GetPhantomIn()[1]  - (SMP->GetPhantomIn()[1]  - SMP->GetPhantomIn()[0])/2;

 double yOutCenter   = SMP->GetPhantomOut()[3] - (SMP->GetPhantomOut()[3] - SMP->GetPhantomOut()[2])/2;
 double yInCenter    = SMP->GetPhantomIn()[3]  - (SMP->GetPhantomIn()[3]  - SMP->GetPhantomIn()[2])/2;

 double zOutCenter   = SMP->GetPhantomOut()[5] - (SMP->GetPhantomOut()[5] - SMP->GetPhantomOut()[4])/2;
 double zInCenter    = SMP->GetPhantomIn()[5]  - (SMP->GetPhantomIn()[5]  - SMP->GetPhantomIn()[4])/2;

 apos = G4ThreeVector( xInCenter - xOutCenter, yInCenter - yOutCenter, zInCenter - zOutCenter);



  G4SubtractionSolid* solid_phantom =
              new G4SubtractionSolid("phantom", solid_phantom_out, solid_phantom_in, 0, apos);

  G4LogicalVolume* logical_phantom =
              new G4LogicalVolume(solid_phantom,      //its solid
                                  pmma,               //its material
                                  "phantom");         //its name

  // Visual attributes of the water container (phantom)
  G4VisAttributes* phantom_visAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.7));
  phantom_visAtt->SetForceWireframe(true);
  logical_phantom->SetVisAttributes(phantom_visAtt);

  Transformation3D =  G4Transform3D(G4RotationMatrix(0.0, 0.0, 0.0),
                      G4ThreeVector(SMP->GetPhantomOut()[1] - (SMP->GetPhantomOut()[1] - SMP->GetPhantomOut()[0])/2,
                                    SMP->GetPhantomOut()[3] - (SMP->GetPhantomOut()[3] - SMP->GetPhantomOut()[2])/2,
                                    SMP->GetPhantomOut()[5] - (SMP->GetPhantomOut()[5] - SMP->GetPhantomOut()[4])/2));

  G4VPhysicalVolume* physical_phantom =
                     new G4PVPlacement( Transformation3D,     //its position(center) relative to the world/air center
                                        logical_phantom,      //its logical volume
                                        "phantom",            //its name
                                        MotherVolume,         //its mother  volume
                                        false,                //no boolean operation
                                        0,                    //copy number
                                        checkOverlaps);       //overlaps checking
  return physical_phantom;
}

G4VPhysicalVolume* DetectorConstruction::ConstructWater(G4LogicalVolume* MotherVolume){
  G4bool checkOverlaps = true;
  G4Material* watermat = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
  G4Transform3D Transformation3D;
  G4ThreeVector apos;

  G4Box* solid_water_full  = new G4Box("waterf", (SMP->GetWater()[1] - SMP->GetWater()[0])/2,
                                                 (SMP->GetWater()[3] - SMP->GetWater()[2])/2,
                                                 (SMP->GetWater()[5] - SMP->GetWater()[4])/2);

  G4Box* solid_water_coll  = new G4Box("waterg", (SMP->GetColl()[1]  - SMP->GetColl()[0])/2,
                                                 (SMP->GetLid()[3]   - SMP->GetLid()[2])/2,
                                                 (SMP->GetColl()[5]  - SMP->GetColl()[4])/2);

  apos = G4ThreeVector((SMP->GetColl()[1]  - (SMP->GetColl()[1]  - SMP->GetColl()[0])/2) - (SMP->GetWater()[1] - (SMP->GetWater()[1] - SMP->GetWater()[0])/2),
                       (SMP->GetLid()[3]   - (SMP->GetLid()[3]   - SMP->GetLid()[2])/2)  - (SMP->GetWater()[3] - (SMP->GetWater()[3] - SMP->GetWater()[2])/2),
              (shift +  SMP->GetColl()[5]  - (SMP->GetColl()[5]  - SMP->GetColl()[4])/2) - (SMP->GetWater()[5] - (SMP->GetWater()[5] - SMP->GetWater()[4])/2));



  G4SubtractionSolid* solid_water =
                        new G4SubtractionSolid("water", solid_water_full, solid_water_coll, 0, apos);

  G4LogicalVolume* logical_water =
                   new G4LogicalVolume(solid_water,          //its solid
                                       watermat,             //its material
                                       "water");             //its name


  G4VisAttributes * water_VisAtt = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0, 0.5));
  water_VisAtt->SetForceSolid(true);
  logical_water->SetVisAttributes(water_VisAtt);

  Transformation3D =  G4Transform3D(G4RotationMatrix(0.0, 0.0, 0.0),
                      G4ThreeVector(SMP->GetWater()[1] - (SMP->GetWater()[1] - SMP->GetWater()[0])/2,
                                    SMP->GetWater()[3] - (SMP->GetWater()[3] - SMP->GetWater()[2])/2,
                                    SMP->GetWater()[5] - (SMP->GetWater()[5] - SMP->GetWater()[4])/2));

  G4VPhysicalVolume* physical_water
                    = new G4PVPlacement(Transformation3D,           //Relative to the global/world/air center
                                        logical_water,              //its logical volume
                                        "water",                    //its name
                                        MotherVolume,               //its mother  volume
                                        false,                      //no boolean operation
                                        0,                          //copy number
                                        checkOverlaps);             //overlaps checking

  return physical_water;
}

G4VPhysicalVolume* DetectorConstruction::ConstructLid(G4LogicalVolume* MotherVolume){
  G4bool checkOverlaps = true;
  G4Material* lidmat = G4NistManager::Instance()->FindOrBuildMaterial("G4_WATER");
  G4Transform3D Transformation3D;
  G4ThreeVector apos;

  G4Box* solid_lid_full  = new G4Box("lidf", (SMP->GetLid()[1] - SMP->GetLid()[0])/2,
                                             (SMP->GetLid()[3] - SMP->GetLid()[2])/2,
                                             (SMP->GetLid()[5] - SMP->GetLid()[4])/2);

  G4Box* solid_lid_coll  = new G4Box("lidg", (SMP->GetColl()[1]  - SMP->GetColl()[0])/2,
                                             (SMP->GetLid()[3]   - SMP->GetLid()[2])/2,
                                             (SMP->GetColl()[5]  - SMP->GetColl()[4])/2);

  apos = G4ThreeVector((SMP->GetColl()[1]  - (SMP->GetColl()[1]  - SMP->GetColl()[0])/2) - (SMP->GetLid()[1] - (SMP->GetLid()[1] - SMP->GetLid()[0])/2),
                       (SMP->GetLid()[3]   - (SMP->GetLid()[3]   - SMP->GetLid()[2])/2)  - (SMP->GetLid()[3] - (SMP->GetLid()[3] - SMP->GetLid()[2])/2),
               (shift + SMP->GetColl()[5]  - (SMP->GetColl()[5]  - SMP->GetColl()[4])/2) - (SMP->GetLid()[5] - (SMP->GetLid()[5] - SMP->GetLid()[4])/2));



  G4SubtractionSolid* solid_lid =
                        new G4SubtractionSolid("lid", solid_lid_full, solid_lid_coll, 0, apos);

  G4LogicalVolume* logical_lid =
                   new G4LogicalVolume(solid_lid,          //its solid
                                       lidmat,             //its material
                                       "lid");             //its name


  G4VisAttributes * lid_VisAtt = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0, 0.5));
  lid_VisAtt->SetForceSolid(true);
  logical_lid->SetVisAttributes(lid_VisAtt);

  Transformation3D =  G4Transform3D(G4RotationMatrix(0.0, 0.0, 0.0),
                      G4ThreeVector((SMP->GetLid()[1] -   (SMP->GetLid()[1] - SMP->GetLid()[0])/2)
                                  - (SMP->GetWater()[1] - (SMP->GetWater()[1] - SMP->GetWater()[0])/2),
                                    (SMP->GetLid()[3] -   (SMP->GetLid()[3] - SMP->GetLid()[2])/2)
                                  - (SMP->GetWater()[3] - (SMP->GetWater()[3] - SMP->GetWater()[2])/2),
                                    (SMP->GetLid()[5] -   (SMP->GetLid()[5] - SMP->GetLid()[4])/2)
                                  - (SMP->GetWater()[5] - (SMP->GetWater()[5] - SMP->GetWater()[4])/2)));

  G4VPhysicalVolume* physical_lid
                    = new G4PVPlacement(Transformation3D,         //Relative to the global/world/air center
                                        logical_lid,              //its logical volume
                                        "lid",                    //its name
                                        MotherVolume,             //its mother  volume
                                        false,                    //no boolean operation
                                        0,                        //copy number
                                        checkOverlaps);           //overlaps checking

  return physical_lid;
}


G4VPhysicalVolume* DetectorConstruction::ConstructBarCollimator(G4LogicalVolume* MotherVolume){
  G4bool checkOverlaps = true;
  G4Material* Collmat = G4NistManager::Instance()->FindOrBuildMaterial("G4_BRASS");
  G4Transform3D Transformation3D;
  G4ThreeVector apos;

  G4Box* solid_Coll_full  =  new G4Box("Collf", (SMP->GetColl()[1] - SMP->GetColl()[0])/2,
                                                (SMP->GetColl()[3] - SMP->GetColl()[2])/2,
                                                (SMP->GetColl()[5] - SMP->GetColl()[4])/2);

  G4Box* solid_Coll_spac  = new G4Box("Colls", (SMP->GetCollGap()[1] - SMP->GetCollGap()[0])/2,
                                               (SMP->GetCollGap()[3] - SMP->GetCollGap()[2])/2,
                                               (SMP->GetCollGap()[5] - SMP->GetCollGap()[4])/2);

  apos = G4ThreeVector((SMP->GetCollGap()[1] - (SMP->GetCollGap()[1] - SMP->GetCollGap()[0])/2) - (SMP->GetColl()[1] - (SMP->GetColl()[1] - SMP->GetColl()[0])/2),
                       (SMP->GetCollGap()[3] - (SMP->GetCollGap()[3] - SMP->GetCollGap()[2])/2) - (SMP->GetColl()[3] - (SMP->GetColl()[3] - SMP->GetColl()[2])/2),
                       (SMP->GetCollGap()[5] - (SMP->GetCollGap()[5] - SMP->GetCollGap()[4])/2) - (SMP->GetColl()[5] - (SMP->GetColl()[5] - SMP->GetColl()[4])/2));



  G4SubtractionSolid* solid_coll =
                        new G4SubtractionSolid("Collimator", solid_Coll_full, solid_Coll_spac, 0, apos);


  G4LogicalVolume* logical_Coll =
                   new G4LogicalVolume(solid_coll,          //its soColl
                                       Collmat,             //its material
                                       "Coll");             //its name


  G4VisAttributes * Coll_VisAtt = new G4VisAttributes(G4Colour(0.0, 1.0, 1.0, 0.5));
  Coll_VisAtt->SetForceSolid(true);
  logical_Coll->SetVisAttributes(Coll_VisAtt);

  Transformation3D =  G4Transform3D(G4RotationMatrix(0.0, 0.0, 0.0),
                      G4ThreeVector(SMP->GetColl()[1] - (SMP->GetColl()[1] - SMP->GetColl()[0])/2,
                                    SMP->GetColl()[3] - (SMP->GetColl()[3] - SMP->GetColl()[2])/2,
                            shift + SMP->GetColl()[5] - (SMP->GetColl()[5] - SMP->GetColl()[4])/2));

  G4VPhysicalVolume* physical_Coll
                    = new G4PVPlacement(Transformation3D,         //Relative to the global/world/air center
                                        logical_Coll,             //its logical volume
                                        "Coll",                   //its name
                                        MotherVolume,             //its mother  volume
                                        false,                    //no boolean operation
                                        0,                        //copy number
                                        checkOverlaps);           //overlaps checking

  return physical_Coll;
}
