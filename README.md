# cache_lab (minimal, buildable)

A tiny C++17 cache lab with three policies: **LRU**, **LFU**, and a simplified **LeCaR** (learning between LRU and LFU).  
Includes a micro-benchmark and unit tests.

## Build

### Linux (Ubuntu)
```bash
sudo apt-get update
sudo apt-get install -y build-essential cmake ninja-build
cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

### Windows (VS 2022)
```powershell
# Use "x64 Native Tools Command Prompt for VS 2022"
cmake -S . -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
ctest --test-dir build -C Release --output-on-failure
```

If Ninja is not installed, omit `-G "Ninja"`.

## Run benchmark
```bash
cd build
./bench lru 1024
./bench lfu 1024
./bench lecar 1024
```

Output example:
```
policy=lru cap=1024 gets=95000 hits=70000 misses=25000 hit_rate=0.7368
```

## Python plotting (optional)
After building:
```bash
cd build
python3 ../python/plot_results.py --caps 64 128 256 512 1024 2048 --policies lru lfu lecar > results.csv
```

## Project layout
See `skeleton.md`.
