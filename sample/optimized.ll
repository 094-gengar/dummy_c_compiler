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
  %2 = sext i32 %var_tmp to i64
  %call_tmp2 = call i64 @printnum(i64 %2)
  %var_tmp3 = load i32, i32* %a
  %var_tmp4 = load i32, i32* %b
  %add_tmp = add i32 %var_tmp3, %var_tmp4
  store i32 %add_tmp, i32* %c
  %var_tmp5 = load i32, i32* %c
  %var_tmp6 = load i32, i32* %c
  %mul_tmp = mul i32 %var_tmp5, %var_tmp6
  %var_tmp7 = load i32, i32* %c
  %3 = sext i32 %mul_tmp to i64
  %4 = sext i32 %var_tmp7 to i64
  %mul_tmp8 = mul i64 %3, %4
  store i64 %mul_tmp8, i64* %d
  %var_tmp9 = load i64, i64* %d
  %call_tmp10 = call i64 @printnum(i64 %var_tmp9)
  ret i64 0
}
