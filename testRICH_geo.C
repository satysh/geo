void testRICH_geo()
{
    TGeoManager* geoM = new TGeoManager("geoM", "geoM");

    // Materials and media --------------------------------------------------------------

    TGeoMaterial* vacMat = new TGeoMaterial("vacuum", 0, 0, 0);
    TGeoMedium* vacMed = new TGeoMedium("vacuumMed", 1, vacMat);

    TGeoMaterial* chaMat = new TGeoMaterial("aluminium", 0, 1, 0);
    TGeoMedium* chaMed = new TGeoMedium("chassisMed", 1, chaMat);

    TGeoMaterial* radMat = new TGeoMaterial("RICHgas_CO2_dis", 0, 1, 0);
    TGeoMedium* radMed = new TGeoMedium("RICHgasMed", 1, radMat);

    TGeoMaterial* sciMat = new TGeoMaterial("CsI", 0, 1, 0);
    TGeoMedium* sciMed = new TGeoMedium("CsIMed", 1, sciMat);

    TGeoMaterial* glassMat = new TGeoMaterial("RICH_glass", 0, 1, 0);
    TGeoMedium* glassMed = new TGeoMedium("RICH_glassMed", 1, glassMat);

    // Shapes and volumes ---------------------------------------------------------------

    // Top - cave volume-assembly
    TGeoVolumeAssembly* TOP = new TGeoVolumeAssembly("TOP");

    // Detector system main volume
    TGeoBBox* sDetSys = new TGeoBBox("sDetSys", 510., 510., 1010.);
    TGeoVolume* vDetSys = new TGeoVolume("vDetSys", sDetSys, vacMed);

    // Chassis
    TGeoBBox* sChassis = new TGeoBBox("sChassis", 500., 500., 1000.);
    TGeoVolume* vChassis = new TGeoVolume("vChassis", sChassis, chaMed);

    // Radiator
    TGeoBBox* sRad = new TGeoBBox("sRad", 450., 450., 900.);
    TGeoVolume* vRad = new TGeoVolume("vRad", sRad, radMed);

    //Scintillator
    TGeoBBox* sSci = new TGeoBBox("sSci", 50., 400., 650.);
    TGeoVolume* vSci = new TGeoVolume("vSci", sSci, sciMed);

    // RICH glass
    TGeoBBox* sGlass = new TGeoBBox("sGlass", 25., 400., 230.);
    TGeoVolume* vGlass = new TGeoVolume("vGlass", sGlass, glassMed);

    // Volume hierarchy -----------------------------------------------------------------

    // Set position to first and second scintillators
    TGeoTranslation* tSci1 = new TGeoTranslation("tSci1", 400., 0., -200.);
    TGeoTranslation* tSci2 = new TGeoTranslation("tSci2", -400., 0., -200.);

    // Set position to first and second glasses
    TGeoRotation* rotGlass1 = new TGeoRotation("rotGlass1");
    rotGlass1->RotateY(60.);
    TGeoCombiTrans* tGlass1 = new TGeoCombiTrans("tGlass1", 215., 0., 650., rotGlass1);
    tGlass1->RegisterYourself();
    TGeoRotation* rotGlass2 = new TGeoRotation("rotGlass2");
    rotGlass2->RotateY(-60.);
    TGeoCombiTrans* tGlass2 = new TGeoCombiTrans("tGlass2", -215., 0., 650., rotGlass2);
    tGlass2->RegisterYourself();

    // Set position to the detector system
    TGeoTranslation* tDetSys = new TGeoTranslation("tDetSys", 0., 0., 1010.);

    // Filling detector system
    vDetSys->AddNodeOverlap(vSci, 1, tSci1);
    vDetSys->AddNodeOverlap(vSci, 2, tSci2);
    vDetSys->AddNodeOverlap(vGlass, 1, tGlass1);
    vDetSys->AddNodeOverlap(vGlass, 2, tGlass2);
    vDetSys->AddNodeOverlap(vRad, 1);
    vDetSys->AddNodeOverlap(vChassis, 1);

    // Adding detector system to the TOP volume
    TOP->AddNode(vDetSys, 1, tDetSys);

    // Finalization ---------------------------------------------------------------------

    geoM->SetTopVolume(TOP);
    geoM->CloseGeometry();

    geoM->CheckOverlaps();
    geoM->CheckGeometry();

    geoM->GetTopVolume()->Export("richTest.geo.root");
    geoM->Export("richTest.gdml");
}
