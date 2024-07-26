# dummy_c_compiler


- 「きつねさんでもわかるLLVM」の`DummyC`を実装する
- 発展として、
	- `int`を`Int64`で定義
	- 変数の制約条件の注釈をつける二項演算子`$`を定義し、可能（制約条件に従ったときに`Int32`に収まる）ならば、`Int64`から`Int32`への変換を行う
- 実装参考：https://github.com/Kmotiko/DummyCCompiler

## コンパイル・実行
- dummy_c_compilerのコンパイル
```
g++ -g ./src/dcc.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/dcc.o
g++ -g ./src/lexer.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/lexer.o
g++ -g ./src/AST.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/AST.o
g++ -g ./src/parser.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/parser.o
g++ -g ./src/codegen.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/codegen.o
g++ -g ./obj/dcc.o ./obj/lexer.o ./obj/AST.o ./obj/parser.o ./obj/codegen.o `llvm-config --cxxflags --ldflags --libs` -ldl -o ./bin/dcc
```

- ↑を一行で行う場合
```
g++ -g ./src/dcc.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/dcc.o; g++ -g ./src/lexer.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/lexer.o; g++ -g ./src/AST.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/AST.o; g++ -g ./src/parser.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/parser.o; g++ -g ./src/codegen.cpp -I./include `llvm-config --cxxflags --ldflags --libs` -c -o ./obj/codegen.o; g++ -g ./obj/dcc.o ./obj/lexer.o ./obj/AST.o ./obj/parser.o ./obj/codegen.o `llvm-config --cxxflags --ldflags --libs` -ldl -o ./bin/dcc

```

- `.dc`ファイルの実行
```
./bin/dcc ./sample/test.dc -o ./sample/test.ll
```

- `DowncastPass`のコンパイル&実行
```
g++ -O3 -fPIC -shared -o ./pass/downcast/downcast.so ./pass/downcast/downcast.cpp `llvm-config --cxxflags --ldflags --libs core passes` -std=c++17
opt -load ./pass/downcast/downcast.so -downcastpass < ./sample/test.ll -o ./sample/optimized.bc
llvm-dis -o ./sample/optimized.ll ./sample/optimized.bc
```

- `printnum`と`inputnum`のlink
```
llvm-link ./sample/test.ll ./lib/printnum.ll ./lib/inputnum.ll -S -o ./sample/linked_normal.ll
llvm-link ./sample/optimized.ll ./lib/printnum.ll ./lib/inputnum.ll -S -o ./sample/linked_optimized.ll
```

- linkしたファイルの実行
```
lli ./sample/linked_normal.ll 
lli ./sample/linked_optimized.ll 
```

```
./bin/dcc ./sample/test.dc -o ./sample/test.ll
opt -load ./pass/downcast/downcast.so -downcastpass < ./sample/test.ll -o ./sample/optimized.bc
llvm-dis -o ./sample/optimized.ll ./sample/optimized.bc
llvm-link ./sample/test.ll ./lib/printnum.ll ./lib/inputnum.ll -S -o ./sample/linked_normal.ll
llvm-link ./sample/optimized.ll ./lib/printnum.ll ./lib/inputnum.ll -S -o ./sample/linked_optimized.ll
opt --O3 -o ./sample/test_O3.bc ./sample/test.ll
opt --O3 -o ./sample/optimized_O3.bc ./sample/optimized.ll
llvm-dis -o ./sample/test_O3.ll ./sample/test_O3.bc
llvm-dis -o ./sample/optimized_O3.ll ./sample/optimized_O3.bc
llvm-link ./sample/test_O3.ll ./lib/printnum.ll ./lib/inputnum.ll -S -o ./sample/linked_normal_O3.ll
llvm-link ./sample/optimized_O3.ll ./lib/printnum.ll ./lib/inputnum.ll -S -o ./sample/linked_optimized_O3.ll

llc ./sample/linked_normal.ll -o ./sample/linked_normal.s
as ./sample/linked_normal.s -o ./sample/linked_normal.o
clang ./sample/linked_normal.o -o ./sample/linked_normal
valgrind --tool=massif ./sample/linked_normal
ms_print massif.out.xxxxx > log.txt

llc ./sample/linked_optimized.ll -o ./sample/linked_optimized.s
as ./sample/linked_optimized.s -o ./sample/linked_optimized.o
clang ./sample/linked_optimized.o -o ./sample/linked_optimized
valgrind --tool=massif ./sample/linked_optimized
ms_print massif.out.xxxxx > log2.txt

llc ./sample/linked_normal_O3.ll -o ./sample/linked_normal_O3.s
as ./sample/linked_normal_O3.s -o ./sample/linked_normal_O3.o
clang ./sample/linked_normal_O3.o -o ./sample/linked_normal_O3
valgrind --tool=massif ./sample/linked_normal_O3
ms_print massif.out.xxxxx > log3.txt

llc ./sample/linked_optimized_O3.ll -o ./sample/linked_optimized_O3.s
as ./sample/linked_optimized_O3.s -o ./sample/linked_optimized_O3.o
clang ./sample/linked_optimized_O3.o -o ./sample/linked_optimized_O3
valgrind --tool=massif ./sample/linked_optimized_O3


llc ./sample/linked_normal_O3.ll -o ./sample/linked_normal_O3.s
llc ./sample/linked_optimized_O3.ll -o ./sample/linked_optimized_O3.s



```


## 

## TODO
- 関数内での動作未確認
- 代入以外の部分でオーバーフローが起きるかもしれない→起きません！たぶん...
- 代入は基本的に一回を想定（渾身の`std::unordered_map`がバグる）
	- 今回は変数の実装がmutableなものになっているので、将来的にimmutableな変数系の言語でこの機能を再実装したいと思っています
- `pass/downcast`は実装中（今は`!upper_data`を取り出してくれるようになっている）→実装しました！