{

  TGeoManager::Import("geofile_mft.root");

  TGeoVolume *t = gGeoManager->GetVolume("MFT");
  gGeoManager->SetVisLevel(10);
  t->Draw("ogl"); 

}

