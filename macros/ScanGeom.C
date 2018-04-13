#if !defined(__CINT__) || defined(__MAKECINT__)

#include <TGeoManager.h>
#include <TGeoNode.h>
#include <TGeoVolume.h>
#include <TString.h>
#include <TObjArray.h>

void PrintNodes(TGeoNode *tnode, Int_t depth);

#endif

void ScanGeom() {

  TGeoManager::Import("geofile_mft_old.root");

  gGeoManager->GetTopVolume()->PrintNodes();

  TGeoNode* tnode = gGeoManager->GetTopVolume()->FindNode("MFT_0");

  PrintNodes(tnode,0);

}

void PrintNodes(TGeoNode *tnode, Int_t depth) {

  Double_t master[3], local[3] = {0.,0.,0.};
  Double_t Aeff, Zeff, rho, radlen, intlen;
  TGeoVolume *v;
  TGeoMedium *med;
  TGeoMaterial *mat;
  TGeoBBox *bb;
  Double_t bbDx, bbDy, bbDz;

  depth++;

  TGeoVolume *vol = tnode->GetVolume();
  for (Int_t id = 0; id < depth; id++) printf("=");
  printf("Volume %s assm %d \n",vol->GetName(),vol->IsAssembly());

  TObjArray *nlist = vol->GetNodes();
  if (nlist == 0x0) {
    printf(".......... no more nodes\n");
    return;
  }

  Int_t nNodes = (Int_t)nlist->GetEntries();

  TGeoNode *node;
  for (Int_t in = 0; in < nNodes; in++) {
    node = (TGeoNode*)nlist->At(in);
    for (Int_t id = 0; id < depth; id++) printf("-");
    //printf("Node %s vis %1d \n",node->GetName(),node->IsVisible());

    printf("Node %s vis %1d : ",node->GetName(),node->IsVisible());

    v = node->GetVolume();

    mat = v->GetMaterial();
    Aeff = mat->GetA();
    Zeff = mat->GetZ();
    rho = mat->GetDensity();
    radlen = mat->GetRadLen();
    intlen = mat->GetIntLen();
    printf("Material %d  %s Aeff=%9.4f Zeff=%9.4f rho=%9.5f radlen=%12.5f intlen=%12.5f , ",mat->GetIndex(),mat->GetName(),Aeff,Zeff,rho,radlen,intlen);

    bb = ((TGeoBBox*)v->GetShape());
    bbDx = bb->GetDX();
    bbDy = bb->GetDY();
    bbDz = bb->GetDZ();
    printf("BBox dx=%9.4f dy=%9.4f dz=%9.4f \n",bbDx,bbDy,bbDz);

    med = v->GetMedium();
    printf("Medium  %d  %s \n",med->GetId(),med->GetName());
    //med->Print();

    PrintNodes(node,depth);
  }

}

