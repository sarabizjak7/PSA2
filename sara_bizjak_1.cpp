// Naloga 1: Prepogosto
// Sara Bizjak, 27161075
// Matematika, PSA2

#include<iostream>
#include<vector>

using namespace std;

int main() {

  // vhodni podatki
  /*
  N: stevilo stevil v seznamu
  K: stevilo obdrzanih pojavitev
  S1: prvi clen seznama
  S2: drugi clen seznama
  X, Y: parametra v generatorju
  M: modul
  A, B: na koncu zelimo popravljen seznam izpisati od A-tega do B-tega mesta
  */

  long long N, K, S1, S2, X, Y, M, A, B;
  cin >> N >> K >> S1 >> S2 >> X >> Y >> M >> A >> B;

  // naredimo vektor, kjer bomo hranili stevila, podana z generatorjem seznama
  vector<int> v(N);
  // prvi dve stevili sta podani direktno in ju kar vstavimo v vektor na prvi dve mesti
  v[0] = S1;
  v[1] = S2;

  // naredimo se vektor, v katerem bomo steli pojavitve stevil - vseh moznih razlicnih stevil je M, ker delimo po modulu M
  // pripravimo torej vektor z M ponovitvami nicel
  vector<int> pojavitve(M + 1, 0);

  // izracunamo se naslednje clene seznama, upostevamo rekurzivno zvezo

  for (int i = 2; i < N; ++i) {
    v[i] = int((v[i - 2] * X + v[i - 1] * Y) % M);
  }

  // prestejemo ponovitve (od zadaj naprej) - ko stevilo pojavitev preseze K, nastavimo na 3*M, da bomo kasneje te clene preskocili
  for (int i = N - 1; i >= 0; --i) {
      ++pojavitve[v[i]];

      if (pojavitve[v[i]] > K) {
        v[i] = 3 * M;
      }
    }

  // stevilo j bo merilo mesto v "novem seznamu"
  int j = 0;

  for (int i = 0; i < N; ++i) {
    // ce 3*M, te pojavitve ne upostevamo
    if (v[i] == 3 * M) {
      continue;
    }
    // sicer pa stevilo izpisemo, ce lezi med A-tim in B-tim clenom
    if (j >= A - 1 && j < B) {
      cout << v[i] << ' ';
    }
    if (j > B) {
      break;
    }
    ++j;
  }
  return 0;
}
