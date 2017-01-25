# pattern [![Build Status](https://travis-ci.org/chino540off/pattern.svg?branch=master)](https://travis-ci.org/chino540off/pattern) [![Coverage Status](https://coveralls.io/repos/github/chino540off/pattern/badge.svg?branch=master)](https://coveralls.io/github/chino540off/pattern?branch=master)
## Build
```
./build.sh
./pattern ...
```
## Usage
`pattern file nbthreads patterns...`
- file: the read file
- nbthreads: number of threads allocated
- patterns...: a list of pattern

Example:
```
cat file.txt
blabla
blabla
blabla
blabla
blabla
blabla
blabla
blabla
blabla
blabla
./pattern file.txt 4 b l a bl la bla blabla
pattern a == 20
pattern b == 20
pattern bl == 20
pattern bla == 20
pattern blabla == 10
pattern l == 20
pattern la == 20
```

```
cat file.txt
aaaaaaa
./pattern file.txt 4 aaa
pattern aaa == 5
