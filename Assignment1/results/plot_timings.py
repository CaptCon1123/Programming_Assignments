import csv
import matplotlib.pyplot as plt

def read_csv(path):
    n_vals = []
    matcher_us = []
    verifier_us = []
    with open(path, newline="", encoding="utf-8-sig") as f:
        reader = csv.DictReader(f)
        for row in reader:
            n_vals.append(int(row["n"]))
            matcher_us.append(float(row["matcher_us"]))
            verifier_us.append(float(row["verifier_us"]))
    return n_vals, matcher_us, verifier_us

def main():
    csv_path = "timings.csv"          
    out_path = "runtime_plot.png"     
    n, matcher, verifier = read_csv(csv_path)

    plt.figure()
    plt.plot(n, matcher, marker="o", label="Matcher (Gale–Shapley)")
    plt.plot(n, verifier, marker="o", label="Verifier")

    plt.xlabel("n (number of hospitals/students)")
    plt.ylabel("Runtime (microseconds)")
    plt.title("Runtime vs n")
    plt.xscale("log", base=2)  # helpful since n doubles each step
    plt.grid(True, which="both", linestyle="--", linewidth=0.5)
    plt.legend()

    plt.tight_layout()
    plt.savefig(out_path, dpi=200)
    print(f"Saved plot to {out_path}")

if __name__ == "__main__":
    main()
