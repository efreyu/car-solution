
# Test task ![Linux build](https://github.com/efreyu/test-task/workflows/Linux%20build/badge.svg?branch=master) 

#### First of all, you need to clone repo:
```bash
git clone git@github.com:efreyu/test-task.git test-task 
cd test-task
```

#### Usage (Linux) :

```bash
mkdir build
cd build
cmake ..
make -j$(nproc)
make test
./main
```