; ModuleID = './sample/optimized.bc'
source_filename = "./sample/test.dc"

declare i64 @printnum(i64)

declare i64 @inputnum()

define i64 @main() {
entry:
  %a = alloca [1000000 x i32]
  %gep = getelementptr [1000000 x i32], [1000000 x i32]* %a, i32 0, i32 0
  %t0 = load i32, i32* %gep
  %inc_add_tmp = add i32 %t0, 1
  store volatile i32 %inc_add_tmp, i32* %gep
  ret i64 0
}
