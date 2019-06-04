// Naloga 4: Enaki nizi
// Sara Bizjak, 27161075
// Matematika, PSA2

// Vzeto iz:
// https://www.geeksforgeeks.org/check-whether-two-strings-are-equivalent-or-not-according-to-given-condition/?fbclid=IwAR295LOcELUpCEAI0ZvOsry1M4qyfJgiRjA9S5xBEFO0Y5m4lJKarGgEfsA

#include <iostream>
#include <string>

using namespace std;


string preveri (string s) {
  if (s.size() == 1) {
    return s;
  }
  else {
    string x = preveri(s.substr(0, s.size() / 3));
    string y = preveri(s.substr(s.size() / 3, s.size() / 3));
    string z = preveri(s.substr(2 * s.size() / 3));

    string m1 = min(x + y + z, x + z + y);
    string m2 = min(y + x + z, y + z + x);
    string m3 = min( z + x + y, z + y + x);

    return min(min(m1, m2), m3);
  }
}

int main() {
  int N;
  cin >> N;

  for (int i = 0; i < N; ++i) {
    string n1, n2;
    cin >> n1 >> n2;

    if (preveri(n1) == preveri(n2)) {
      cout << "enaka" << endl;
    }
    else {
      cout << "razlicna" << endl;
    }
  }
  return 0;
}
