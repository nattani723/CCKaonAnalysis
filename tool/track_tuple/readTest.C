void readTest() {
  TFile *f = TFile::Open("/exp/uboone/data/users/taniuchi/recoalg_testarea/assok_refined_KrecoAlg_debug_test3.root");
  TTree *t;
  f->GetObject("CCKaonAnalyzerRebuild/Event", t);
  Float_t test_x;
  TBranch *b_test;
  t->SetBranchAddress("true_dau_muon_end_x", &test_x, &b_test);

  Long64_t nentries = t->GetEntries();
  for (Long64_t j = 0; j < nentries; j++) {
    t->GetEntry(j);
    std::cout << "Entry " << j << ": " << test_x << std::endl;
  }
  f->Close();
}
