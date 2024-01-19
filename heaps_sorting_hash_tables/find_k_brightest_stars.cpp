// enable assertions in release build
#ifdef NDEBUG
#undef NDEBUG
#endif

#include <cassert>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

using namespace std;

/************** begin assignment **************/
// Find k (= 8) brightest stars in a stream. To measure the brightness we use
// the visual magnitude (Vmag). The smaller Vmag the brighter the star appears
// to us. If you want to know more about Vmag read this:
// https://de.wikipedia.org/wiki/Scheinbare_Helligkeit
// We work with the file stars.txt. Look at the structure of the file, because
// you will parse it line by line to extract information about the stars.

struct Star {
    string name;  // name of the star
    double vmag;  // stars brightness (the smaller vmag the brighter the star)
};

// You get the input file stream "ifs" to the "stars.txt" file and a parameter
// "k". "k" is the amount of the brightest stars we wan't to extract from the
// stream. Try to extract the "k" brightest stars in O(n * log(k)) time with
// O(log n) extra space.
vector<Star> find_k_brightest_stars(ifstream &ifs, const size_t k) {
    // "result" contains in the end the k brightest stars in sorted order
    // (brightest first)

    vector<Star> result;

    auto comparator = [](const Star &a, const Star &b) {
        // to be able to use a min_heap map the small vmag values to big values and vice versa
        // vmag value does not succeed the value -2
        return 1 / (a.vmag + 2) > 1 / (b.vmag + 2);
    };
    // use a min heap
    priority_queue<Star, vector<Star>, decltype(comparator)> min_heap(comparator);

    // TODO: extract k brightest stars from the stream

    string line;
    while (getline(ifs, line)) {
        if (line[0] == '#' || line == "") {
            continue;
        }
        stringstream ss(line);
        string word;
        Star star;
        int info_counter = 0;
        int vmag_id = 8;
        while (ss >> word) {
            if (info_counter == 0) {
                star.name = word;
            }

            // check if star has a double name
            if (info_counter == 1) {
                if (word.compare("HR") != 0 && word.compare("GJ") != 0 && word.compare("HD") != 0) {
                    star.name += " " + word;
                    vmag_id++;
                }
            }
            if (info_counter == vmag_id) {
                star.vmag = stod(word);
            }
            info_counter++;
        }
        min_heap.push(star);

        // if the heap size exceeds k pop the less brighter elements
        if (min_heap.size() > k) {
            min_heap.pop();
        }
    }

    for (int i = 0; i < k; i++) {
        Star star = min_heap.top();
        min_heap.pop();
        // put the brightest stars at the beginning
        result.insert(result.begin(), star);
    }

    // return stars in sorted order (brightest first)
    return result;
}
/*************** end assignment ***************/

double absolute(double a) {
    return (-a) * (a < 0) + a * (a >= 0);
}

int main() {
    string path = "stars.txt";
    ifstream ifs{path};  // open file as a stream
    if (ifs.fail()) {
        cerr << "cannot find: " << path << endl;
        return 1;
    }
    size_t k = 8;  // k brightest stars
    vector<Star> brightest_stars = find_k_brightest_stars(ifs, k);

    vector<Star> correct_stars{{"Sirius", -1.45}, {"Canopus", -0.62}, {"Arcturus", -0.05}, {"Rigil Kentaurus", -0.01}, {"Vega", 0.03}, {"Capella", 0.08}, {"Rigel", 0.18}, {"Procyon", 0.4}};

    // test correctness of solution
    assert(brightest_stars.size() == correct_stars.size());
    const double epsilon = 1.0e-12;  // almost 0
    for (size_t i = 0; i < brightest_stars.size(); ++i) {
        assert(absolute(brightest_stars[i].vmag - correct_stars[i].vmag) < epsilon);
        assert(brightest_stars[i].name == correct_stars[i].name);
    }

    // output brightest stars
    for (const auto &star : brightest_stars) {
        cout << star.name << endl;
        cout << star.vmag << endl;
        cout << endl;
    }
}
