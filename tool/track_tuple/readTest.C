void readTest() {
  TFile *f = TFile::Open("/exp/uboone/data/users/taniuchi/recoalg_testarea/assok_refined_KrecoAlg_debug_test3.root");
  TTree *t;
  f->GetObject("CCKaonAnalyzerRebuild/Event", t);
  Float_t test_x1;
  Float_t test_x2;
  TBranch *b_test1;
  TBranch *b_test2;
  t->SetBranchAddress("true_dau_muon_end_x", &test_x1, &b_test1);
  t->SetBranchAddress("true_dau_muon_start_x", &test_x2, &b_test2);

  Long64_t nentries = t->GetEntries();
  for (Long64_t j = 0; j < 100; j++) {
    t->GetEntry(j);
    if(test_x1!=-9999) std::cout << "true_dau_muon_end_x Entry " << j << ": " << test_x1 << std::endl;
    if(test_x1!=-9999) std::cout << "true_dau_muon_start_x Entry " << j << ": " << test_x2 << std::endl;
  }
  f->Close();
}
