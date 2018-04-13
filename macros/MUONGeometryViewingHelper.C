/**************************************************************************
 * Copyright(c) 1998-1999, ALICE Experiment at CERN, All rights reserved. *
 *                                                                        *
 * Author: The ALICE Off-line Project.                                    *
 * Contributors are mentioned in the code where appropriate.              *
 *                                                                        *
 * Permission to use, copy, modify and distribute this software and its   *
 * documentation strictly for non-commercial purposes is hereby granted   *
 * without fee, provided that the above copyright notice appears in all   *
 * copies and that both the copyright notice and this permission notice   *
 * appear in the supporting documentation. The authors make no claims     *
 * about the suitability of this software for any purpose. It is          *
 * provided "as is" without express or implied warranty.                  *
 **************************************************************************/

// $Id$
//
/// \ingroup macros
/// \file MUONGeometryViewingHelper.C
/// \brief Macro providing methods helping in viewing geometry
///
/// To be run from aliroot:
/// <pre>
/// root[0] .x MUONGeometryViewingHelper.C
/// root[0] buildGeometry();
/// </pre>
///
/// \author: I. Hrivnacova, IPN Orsay

#if !defined(__CINT__) || defined(__MAKECINT__)

#include <Riostream.h>
#include <TObjArray.h>
#include <TBrowser.h>
#include <TGeoManager.h>
#include <TGeoVolume.h>

void setVisibility(const TString& volumeName, Bool_t visibility= kTRUE); 

#endif

void visibilityOff() 
{
/// Set all volumes invisible

  TObjArray* volumes = gGeoManager->GetListOfVolumes();
  for (Int_t i=0; i<volumes->GetEntriesFast(); i++)
    ((TGeoVolume*)volumes->At(i))->SetVisibility(kFALSE);
    
}  


void setVisibility(const TString& volumeName, Bool_t visibility) 
{
/// Set visibility to the volume specified by name

  static Int_t colourNo = 1;     
 
  TGeoVolume* volume = gGeoManager->FindVolumeFast(volumeName.Data());

  if ( ! volume ) {
    cerr << "Volume " <<  volumeName.Data() << " not found." << endl;
    return;
  }  

  volume->SetVisibility(visibility);

  ++colourNo;
  if ( colourNo > 9 ) colourNo = 1;
  colourNo = 4;
  volume->SetLineColor(colourNo); 
  
  return;

  // set visibility for a node (or more) only
  if (strncmp(volumeName.Data(),"MFT_S_0",7) == 0) {
    TGeoShape *shape = volume->GetShape();
    TObjArray *nodes = volume->GetNodes();
    for (Int_t i = 0; i < nodes->GetEntries(); i++) {
      TGeoNode *node = (TGeoNode*)nodes->At(i);
      cout << node->GetName() << endl;
      if (strncmp(node->GetName(),"MFTSensor",9) == 0) {
	node->SetVisibility(visibility);
      }
    }
  }
  if (strncmp(volumeName.Data(),"S0R",3) == 0) {
    TGeoShape *shape = volume->GetShape();
    TObjArray *nodes = volume->GetNodes();
    for (Int_t i = 0; i < nodes->GetEntries(); i++) {
      TGeoNode *node = (TGeoNode*)nodes->At(i);
      cout << node->GetName() << endl;
      if (strncmp(node->GetName(),"SC1A",4) == 0) {
	node->SetVisibility(visibility);
      }
    }
  }
  
  // set visibility for the whole volume
  if (strcmp(volumeName.Data(),"SC11") == 0) {
    volume->SetVisibility(visibility);
  }

}  

void setDaughtersVisibility(const TString& volumeName, Bool_t visibility= kTRUE)  
{
/// Set visibility to daughter of the volume specified by name.
/// If the daughter volume is an assembly the visibility setting
/// is propagated to its real volumes daughters.

   TGeoVolume* volume = gGeoManager->FindVolumeFast(volumeName.Data());
   
   if ( ! volume ) { 
     cerr << "Volume " <<  volumeName.Data() << " not found." << endl;
     return;
   }  
     
   Int_t colourNo = 1;
   for ( Int_t i=0; i<volume->GetNdaughters(); i++ ) {
   
     TGeoVolume* dvolume = volume->GetNode(i)->GetVolume();
     if ( dvolume->IsAssembly() ) {
       // Do no set visibility to assembly but to its daughters
       setDaughtersVisibility(dvolume->GetName(), visibility);
       printf("Volume %s is assembly %1d \n",dvolume->GetName(),dvolume->IsAssembly());
     }
     else {  
       cout << "Setting visibility to " <<  dvolume->GetName() << endl;
       /*
       dvolume->SetVisibility(visibility);

       // change colors
       ++colourNo;
       if ( colourNo > 9 ) colourNo = 1;
       //colourNo = 4;
       dvolume->SetLineColor(colourNo); 
       */
       setVisibility(dvolume->GetName(),visibility);

     }     
   }
}

void buildGeometry(Bool_t allVisible = kFALSE ) 
{  

  /// Build the ideal geometry, make all volumes 

  TGeoManager::Import("geofile_mft.root");
  //TGeoManager::Import("geofile_mft_new.root");
  //TGeoManager::Import("old_04/geofile_mft_old.root");

  new TBrowser();
  
  if ( ! allVisible ) visibilityOff();

  gGeoManager->SetVisLevel(10);
  gGeoManager->GetTopVolume()->SetVisContainers(kTRUE);
  gGeoManager->GetTopVolume()->Draw("ogl");

  cout << endl;
  cout << "You can now add volumes in the scene: " << endl;
  cout << "    setVisibility(\"MyVolume\") "  <<  endl;
  cout << "    setDaughtersVisibility(\"MyVolume\") " <<  endl;
  cout << "or remove them from the scene: " << endl;
  cout << "    setVisibility(\"MyVolume\", kFALSE);" << endl;
  cout << "    setDaughtersVisibility(\"MyVolume\", kFALSE);" << endl;  
  cout << endl;
}  
