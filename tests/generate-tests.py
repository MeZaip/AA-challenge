import random

random.seed(67)

def gen_test(name, n, lo, hi):
    arr = [random.randint(lo, hi) for _ in range(n)]
    T = random.randint(1, min(abs(sum(arr)) // 2, 100000))
    with open(f"{name}.txt", "w+") as f:
        f.write(f"{n} {T}\n")
        f.write(" ".join(map(str, arr)) + "\n")

gen_test("test_small_10", 10, -10, 10)
gen_test("test_small_20", 20, -20, 20)
gen_test("test_small_30", 30, -25, 25)
gen_test("test_medium_100", 100, -200, 200)
gen_test("test_large_500", 500, -1000, 1000)
gen_test("test_xlarge_5000", 5000, -10000, 10000)