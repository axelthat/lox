```
cmake -S . -B build
make -C build && ./build/lox --file "<FILE>"
```

```
clang++ -std=c++20 -Isrc src/Util.cpp scripts/GenerateAst.cpp -o generate_ast && ./generate_ast "src"
```
