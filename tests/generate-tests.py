import random

random.seed(67)

# Generic tests:
def gen_test(name, n, lo, hi):
    arr = [random.randint(lo, hi) for _ in range(n)]
    T = random.randint(1, min(abs(sum(arr)) // 2, 1000000))
    with open(f"{name}.txt", "w+") as f:
        f.write(f"{n} {T}\n")
        f.write(" ".join(map(str, arr)) + "\n")

# Worst-case tests for backtracking approach (search sum = sum of all numbers):
def gen_test_worst(name, n, lo, hi):
    arr = [random.randint(lo, hi) for _ in range(n)]
    T = sum(arr)
    with open(f"{name}.txt", "w+") as f:
        f.write(f"{n} {T}\n")
        f.write(" ".join(map(str, arr)) + "\n")

# Worst-ish-case tests for DP approach (difference between the lowest and the highest sum possible is really big):
def gen_test_dp_bad_offset(name, n, big=2000, T=3):
    arr = []

    arr.append(T)

    for i in range(n - 1):
        if i % 2 == 0:
            arr.append(big)
        else:
            arr.append(-big)

    random.shuffle(arr)

    with open(f"{name}.txt", "w+") as f:
        f.write(f"{n} {T}\n")
        f.write(" ".join(map(str, arr)) + "\n")

# Worst-ish-case tests for genetic approach (N = 1000, T = 3, numbers: 1,1,1, 1000,1000,...):
def gen_test_ga_bad_smallT(name, n, T=3, small_val=1, small_count=3, big_val=1000):
    if small_count > n:
        small_count = n

    arr = [small_val] * small_count + [big_val] * (n - small_count)

    random.shuffle(arr)

    with open(f"{name}.txt", "w+") as f:
        f.write(f"{n} {T}\n")
        f.write(" ".join(map(str, arr)) + "\n")

gen_test("test_10_small", 10, -10, 10)
gen_test("test_20_small", 20, -20, 20)
gen_test("test_30_small", 30, -25, 25)
gen_test("test_100_medium", 100, -200, 200)
gen_test("test_500_large", 500, -1000, 1000)
gen_test("test_1000_large", 1000, -5000, 5000)
gen_test("test_2000_large", 2000, -10000, 10000)
gen_test("test_2500_large", 2500, -25000, 25000)
gen_test("test_5000_xlarge", 5000, -50000, 50000)
gen_test_worst("test_30_special", 30, 1, 1000)
gen_test_worst("test_31_special", 31, 1, 1000)
gen_test_worst("test_32_special", 32, 1, 1000)
gen_test_ga_bad_smallT("test_200_ga_bad", 200, T=10, small_val=1, small_count=10, big_val=1000)
gen_test_ga_bad_smallT("test_300_ga_bad", 300, T=100, small_val=1, small_count=100, big_val=1000)
gen_test_ga_bad_smallT("test_1000_ga_bad", 1000, T=3, small_val=1, small_count=3, big_val=1000)
gen_test_dp_bad_offset("test_200_dp_bad_offset", 200, big=100000, T=3)
gen_test_dp_bad_offset("test_1000_dp_bad_offset", 1000, big=2000, T=3)
gen_test_dp_bad_offset("test_2000_dp_bad_offset", 2000, big=2000, T=3)
