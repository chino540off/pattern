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

## Known issues
#### Test_0002: Similarity pattern on a part border
Example:
```
cat file.txt
aaaaaaa
./pattern file.txt 1 a aa aaa aaaa aaaaa
pattern a == 7
pattern aa == 3
pattern aaa == 2
pattern aaaa == 1
pattern aaaaa == 1
./pattern file.txt 2 a aa aaa aaaa aaaaa
pattern a == 7
pattern aa == 3
pattern aaa == 3
pattern aaaa == 1
pattern aaaaa == 1
```

Problem:
```
- 1 Thread ----------------------------------------------
|th1          | => "aaa" == 2
|aaa  |aaa  |
+-+-+-+-+-+-+-+
|a|a|a|a|a|a|a|
+-+-+-+-+-+-+-+

- 2 Threads ---------------------------------------------
|th1    | => "aaa" == 2
|aaa  |aaa  |
+-+-+-+-+-+-+-+
|a|a|a|a|a|a|a|
+-+-+-+-+-+-+-+
|       |th2  | => "aaa" == 1
        |aaa  |
```
