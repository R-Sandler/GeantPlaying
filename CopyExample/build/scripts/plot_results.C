/* Read the hits.txt file and put the hits and energy depositions into
 * histograms. */
void plot_results() {
  // Open the file
  ifstream in_file("hits.txt");

  // Create some histograms
  auto hE = new TH1D("hE", "Energy Depositions", 1000, 0, 1000);
  hE->GetXaxis()->SetTitle("Energy (keV)");
  hE->GetYaxis()->SetTitle("Counts/keV");
  auto hXZ = new TH2D("hXZ", "Hit Pattern", 50, -25, 25, 50, -25, 25);
  hXZ->GetXaxis()->SetTitle("X (cm)");
  hXZ->GetYaxis()->SetTitle("Z (cm)");

  double x, z, e;
  string proc;
  // Read the data
  while (in_file >> x >> z >> e >> proc) {
    cout << x << " " << z << " " << e << " " << proc << endl;
    hE->Fill(e);
    hXZ->Fill(x, z);
  }

  auto c1 = new TCanvas("c1", "Energy Depositions", 1000, 800);
  hE->Draw("hist");
  auto c2 = new TCanvas("c2", "Hit Pattern", 1000, 800);
  hXZ->Draw("colz");
  return;
}
