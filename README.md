# pattern
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
