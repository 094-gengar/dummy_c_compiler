; ModuleID = './sample/optimized.bc'
source_filename = "./sample/test.dc"

declare i64 @printnum(i64)

declare i64 @inputnum()

define i64 @main() {
entry:
  %a = alloca i32
  %b = alloca i32
  %c = alloca i32
  %d = alloca i64
  %call_tmp = call i64 @inputnum()
  %0 = trunc i64 %call_tmp to i32
  store i32 %0, i32* %a
  %call_tmp1 = call i64 @inputnum()
  %1 = trunc i64 %call_tmp1 to i32
  store i32 %1, i32* %b
  %var_tmp = load i32, i32* %a
  %var_tmp2 = load i32, i32* %b
  %add_tmp = add i32 %var_tmp, %var_tmp2
  store i32 %add_tmp, i32* %c
  %var_tmp3 = load i32, i32* %c
  %var_tmp4 = load i32, i32* %c
  %var_tmp5 = load i32, i32* %c
  %mul_tmp = mul i32 %var_tmp4, %var_tmp5
  %2 = sext i32 %var_tmp3 to i64
  %3 = sext i32 %mul_tmp to i64
  %mul_tmp6 = mul i64 %2, %3
  store i64 %mul_tmp6, i64* %d
  ret i64 0
}
