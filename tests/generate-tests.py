import random

random.seed(67)

def gen_test(name, n, lo, hi):
    arr = [random.randint(lo, hi) for _ in range(n)]
    T = random.randint(1, min(abs(sum(arr)) // 2, 1000000))
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