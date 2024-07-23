# dummy_c_compiler


- きつねさんでもわかるLLVMを実装する
- 実装参考：https://github.com/Kmotiko/DummyCCompiler

## コンパイル
```
g++ -g ./src/dcc.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/dcc.o
g++ -g ./src/lexer.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/lexer.o
g++ -g ./src/AST.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/AST.o
g++ -g ./src/parser.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/parser.o
g++ -g ./src/codegen.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/codegen.o
g++ -g ./obj/dcc.o ./obj/lexer.o ./obj/AST.o ./obj/parser.o ./obj/codegen.o `llvm-config --cxxflags --ldflags --libs` -ldl -o ./bin/dcc
```

```
g++ -g ./src/dcc.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/dcc.o; g++ -g ./src/lexer.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/lexer.o; g++ -g ./src/AST.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/AST.o; g++ -g ./src/parser.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/parser.o; g++ -g ./src/codegen.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/codegen.o; g++ -g ./obj/dcc.o ./obj/lexer.o ./obj/AST.o ./obj/parser.o ./obj/codegen.o `llvm-config --cxxflags --ldflags --libs` -ldl -o ./bin/dcc

```

```
// g++ -g ./pass/downcast/downcast.cpp -I./include `llvm-config --cxxflags --idflags -libs` -c -o downcast.o; g++ -g -shared -o ./bin/downcast.so downcast.o
g++ -O3 -fPIC -shared -o ./pass/downcast/downcast.so ./pass/downcast/downcast.cpp `llvm-config --cxxflags --ldflags --libs core passes` -std=c++17
opt -load ./pass/downcast/downcast.so -downcastpass < ./sample/test.ll -o ./sample/optimized.bc
llvm-dis -o ./sample/optimized.ll ./sample/optimized.bc
```

## 実行
```
./bin/dcc ./sample/test.dc -o ./sample/test.ll
```

## TODO
- 関数内での動作未確認
- 代入以外の部分でオーバーフローが起きるかもしれない→起きません！たぶん...
- 代入は基本的に一回を想定（渾身の`std::unordered_map`がバグる）
- `pass/downcast`は実装中（今は`!upper_data`を取り出してくれるようになっている）→実装しました！