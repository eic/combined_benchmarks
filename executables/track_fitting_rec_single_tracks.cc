// Created by Dmitry Romanov
// Subject to the terms in the LICENSE file found in the top-level directory.
//

int rec_single_tracks(const char* fname = "topside/rec_single_tracks.root");

int main() {
    rec_single_tracks("/home/romanov/work/data/eicrecon_test/tracking_test_gun.ana.root");
    return 0;
}