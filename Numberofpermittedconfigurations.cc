#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

int main()
{
    vector<vector<size_t> > v;
    for (size_t a = 0; a <= 12; a++) {
        size_t limb = (12 - a);
        for (size_t b = 0; b <= limb; b++) {
            size_t limc = min((12 - a - b), size_t(10));
            for (size_t c = 0; c <= limc; c++) {
                size_t limd = min((12 - a - b - c), (10 - c));
                for (size_t d = 0; d <= limd; d++) {
                    size_t lime = min((12 - a - b - c - d), (10 - c - d));
                    for (size_t e = 0; e <= lime; e++) {
                        size_t limf = min((12 - a - b - c - d - e), (10 - c - d - e));
                        for (size_t f = 0; f <= limf; f++) {
                            size_t limg = min((12 - a - b - c - d - e - f), size_t(5 - 0.5 * (c + d + e + f)));
                            for (size_t g = 0; g <= limg; g++) {
                                size_t limh = min((12 - a - b - c - d - e - f - g),
                                    size_t(5 - g - 0.5 * (c + d + e + f)));
                                for (size_t h = 0; h <= limh; h++) {
                                    if ((a + b + c + d + e + f + g + h) == 12 and ((c + d + e + f) * 2 + (g + h) * 4) ==
                                      20)
                                    {
                                        v.push_back({ a, b, c, d, e, f, g, h });
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    cout << v.size();
} // main
