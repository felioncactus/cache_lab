import argparse, subprocess, csv, os, sys

def run(policy, cap):
    # build has to be done already; we assume ./bench exists
    out = subprocess.check_output(["./bench", policy, str(cap)], text=True)
    return out.strip()

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--caps", type=int, nargs="+", default=[64,128,256,512,1024,2048])
    ap.add_argument("--policies", type=str, nargs="+", default=["lru","lfu","lecar"])
    args = ap.parse_args()

    rows = []
    for p in args.policies:
        for c in args.caps:
            line = run(p, c)
            print(line)
            parts = dict(kv.split("=") for kv in line.split())
            rows.append([p, c, parts["hit_rate"]])

    # simple stdout CSV
    print("policy,cap,hit_rate")
    for p,c,h in rows:
        print(f"{p},{c},{h}")

if __name__ == "__main__":
    main()
