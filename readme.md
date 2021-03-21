# Simple Weather
## Simple app for checking weather in specific cities.

---

##### Required

* cmake (3.10 or higher)
* pkg-config
* libcurl
* gtk (3.0 or higher)
* Threads
* [json-c](https://github.com/json-c/json-c)

If you have different thread libraries force cmake to use pthreads instead of other.

##### Compiling
```
cmake  -S ./ -B ./build && cd build
make
./simple-weather
```