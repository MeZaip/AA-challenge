#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

using namespace std;

long long sum_of(vector<int> &a, vector<int> &pick) {
    long long s = 0;
    int i;
    for (i = 0; i < (int)a.size(); i++) {
        if (pick[i] == 1) s += a[i];
    }
    return s;
}

/*
Fitness for "maximize S subject to S <= T" with negatives allowed:
- If S <= T : fitness = S (bigger is better)
- If S > T  : fitness = T - penalty*(S - T) (so it becomes much worse)
*/
long long fitness_of(long long S, long long T, int penalty) {
    if (S <= T) return S;
    return T - (long long)penalty * (S - T);
}

int tournament_pick(vector<long long> &fit, int POP) {
    int a = rand() % POP;
    int b = rand() % POP;
    int c = rand() % POP;
    int best = a;
    if (fit[b] > fit[best]) best = b;
    if (fit[c] > fit[best]) best = c;
    return best;
}

vector<int> crossover(vector<int> &p1, vector<int> &p2) {
    int N = (int)p1.size();
    vector<int> child;
    int i;
    for (i = 0; i < N; i++) child.push_back(0);

    for (i = 0; i < N; i++) {
        if (rand() % 2 == 0) child[i] = p1[i];
        else child[i] = p2[i];
    }
    return child;
}

vector<int> random_individual(int N) {
    vector<int> pick;
    int i;
    for (i = 0; i < N; i++) pick.push_back(rand() % 2);
    return pick;
}

/*
Directional mutation (works with negatives too):
- If S <= T, try to increase S (add positive / remove negative)
- If S > T, try to decrease S (add negative / remove positive)
We do a few random tries to find a helpful flip, otherwise random flip.
*/
void mutate(vector<int> &pick, vector<int> &a, long long &S, long long T, int prob_percent) {
    if ((rand() % 100) >= prob_percent) return;

    int N = (int)a.size();
    int tries = 25;
    int i;

    if (S <= T) {
        // Try to increase sum
        for (i = 0; i < tries; i++) {
            int j = rand() % N;

            // If not selected and positive -> adding increases S
            if (pick[j] == 0 && a[j] > 0) {
                pick[j] = 1;
                S += a[j];
                return;
            }

            // If selected and negative -> removing increases S
            if (pick[j] == 1 && a[j] < 0) {
                pick[j] = 0;
                S -= a[j];
                return;
            }
        }
    } else {
        // S > T, try to decrease sum
        for (i = 0; i < tries; i++) {
            int j = rand() % N;

            // If not selected and negative -> adding decreases S
            if (pick[j] == 0 && a[j] < 0) {
                pick[j] = 1;
                S += a[j];
                return;
            }

            // If selected and positive -> removing decreases S
            if (pick[j] == 1 && a[j] > 0) {
                pick[j] = 0;
                S -= a[j];
                return;
            }
        }
    }

    // Fallback: random flip
    int j = rand() % N;
    if (pick[j] == 1) { pick[j] = 0; S -= a[j]; }
    else { pick[j] = 1; S += a[j]; }
}

int main(int argc, char **argv) {
    srand((unsigned)time(0));

    if (argc < 2) {
        cout << "Usage: " << argv[0] << " input.txt\n";
        return 0;
    }

    ifstream in(argv[1]);
    if (!in.is_open()) {
        cout << "Could not open input file.\n";
        return 0;
    }

    int N;
    long long T;
    in >> N >> T;

    vector<int> a;
    int i;
    for (i = 0; i < N; i++) {
        int x;
        in >> x;
        a.push_back(x);
    }

    // GA parameters (kept basic)
    int POP = 220;
    int ELITE = 10;
    double LIMIT = 5.0;          // secunde
    clock_t start_time = clock();

    // mutation probability in percent
    int MUT = 8;

    // penalty for sums that exceed T (bigger = pushes more under/near T)
    int PENALTY = 20;

    // population
    vector< vector<int> > pop;
    vector<long long> sumv;
    vector<long long> fit;

    for (i = 0; i < POP; i++) {
        vector<int> ind = random_individual(N);
        long long S = sum_of(a, ind);
        long long F = fitness_of(S, T, PENALTY);

        pop.push_back(ind);
        sumv.push_back(S);
        fit.push_back(F);
    }

    // best feasible (S <= T) we found
    vector<int> best_pick;
    long long best_sum = -(1LL<<60);

    // initialize best
    for (i = 0; i < POP; i++) {
        if (sumv[i] <= T && sumv[i] > best_sum) {
            best_sum = sumv[i];
            best_pick = pop[i];
        }
    }
    // if none feasible, still keep the least-over (closest)
    if ((int)best_pick.size() == 0) {
        int best_i = 0;
        long long best_over = (sumv[0] > T) ? (sumv[0] - T) : (T - sumv[0]);
        for (i = 1; i < POP; i++) {
            long long d = (sumv[i] > T) ? (sumv[i] - T) : (T - sumv[i]);
            if (d < best_over) { best_over = d; best_i = i; }
        }
        best_pick = pop[best_i];
        best_sum = sumv[best_i];
    }

    int g = 0;
    while (1) {
        double elapsed = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        if (elapsed >= LIMIT) break;
        g++;
        vector<int> order;
        for (i = 0; i < POP; i++) order.push_back(i);

        sort(order.begin(), order.end(), [&](int x, int y) {
            return fit[x] > fit[y];
        });

        vector< vector<int> > next_pop;
        vector<long long> next_sumv;
        vector<long long> next_fit;

        // keep elites
        for (i = 0; i < ELITE; i++) {
            int id = order[i];
            next_pop.push_back(pop[id]);
            next_sumv.push_back(sumv[id]);
            next_fit.push_back(fit[id]);
        }

        // build rest
        while ((int)next_pop.size() < POP) {
            int p1 = tournament_pick(fit, POP);
            int p2 = tournament_pick(fit, POP);

            vector<int> child = crossover(pop[p1], pop[p2]);
            long long S = sum_of(a, child);

            mutate(child, a, S, T, MUT);

            long long F = fitness_of(S, T, PENALTY);

            next_pop.push_back(child);
            next_sumv.push_back(S);
            next_fit.push_back(F);
        }

        pop = next_pop;
        sumv = next_sumv;
        fit = next_fit;

        // update best feasible
        for (i = 0; i < POP; i++) {
            if (sumv[i] <= T && sumv[i] > best_sum) {
                best_sum = sumv[i];
                best_pick = pop[i];
            }
        }

        // mild adaptation if we stagnate: bump mutation slightly
        if (g % 150 == 149) {
            if (MUT < 25) MUT += 1;
        }

        if (best_sum == T) break;
    }

    // Output best_pick
    vector<int> idxs;
    vector<int> vals;

    for (i = 0; i < N; i++) {
        if (best_pick[i] == 1) {
            idxs.push_back(i + 1);  // 1-based index
            vals.push_back(a[i]);
        }
    }

    cout << "Size: " << idxs.size() << "\n\nIndexes:\n\n";
    for (i = 0; i < (int)idxs.size(); i++) {
        if (i) cout << " ";
        cout << idxs[i];
    }
    cout << "\n\nSubset:\n\n";
    for (i = 0; i < (int)vals.size(); i++) {
        if (i) cout << " ";
        cout << vals[i];
    }
    cout << "\n\nSum: " << best_sum << "\n";

    return 0;
}
