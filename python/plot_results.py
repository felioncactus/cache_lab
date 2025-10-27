import argparse, glob, csv, collections
import matplotlib.pyplot as plt

def load_rows(paths):
    rows=[]
    for p in paths:
        with open(p, newline='') as f:
            r=csv.DictReader(f)
            rows += list(r)
    return rows

if __name__ == "__main__":
    ap = argparse.ArgumentParser()
    ap.add_argument("--glob", default="../results/*.csv")
    ap.add_argument("--metric", choices=["hit_rate","elapsed_ms"], default="hit_rate")
    args = ap.parse_args()

    rows = load_rows(glob.glob(args.glob))
    by = collections.defaultdict(list)
    for r in rows:
        key = (r["workload"], r["policy"])
        by[key].append((int(r["capacity"]), float(r[args.metric])))

    for (workload, policy), pts in by.items():
        pts.sort()
        xs = [c for c,_ in pts]
        ys = [v for _,v in pts]
        plt.plot(xs, ys, label=f"{policy} ({workload})")

    plt.xlabel("Capacity (items)")
    plt.ylabel(args.metric)
    plt.title(f"cachelab: {args.metric} vs capacity")
    plt.legend()
    plt.grid(True)
    plt.show()
