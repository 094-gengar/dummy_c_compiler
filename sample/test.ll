; ModuleID = './sample/test.dc'
source_filename = "./sample/test.dc"

declare i64 @printnum(i64)

declare i64 @inputnum()

define i64 @main() {
entry:
  %a = alloca i64, !upper_data !0
  %b = alloca i64, !upper_data !0
  %c = alloca i64
  %d = alloca i64
  %call_tmp = call i64 @inputnum()
  store i64 %call_tmp, i64* %a, !upper_data !0
  %call_tmp1 = call i64 @inputnum()
  store i64 %call_tmp1, i64* %b, !upper_data !0
  %var_tmp = load i64, i64* %a, !upper_data !0
  %var_tmp2 = load i64, i64* %b, !upper_data !0
  %add_tmp = add i64 %var_tmp, %var_tmp2, !upper_data !1
  store i64 %add_tmp, i64* %c, !upper_data !1
  %var_tmp3 = load i64, i64* %c, !upper_data !1
  %var_tmp4 = load i64, i64* %c, !upper_data !1
  %var_tmp5 = load i64, i64* %c, !upper_data !1
  %mul_tmp = mul i64 %var_tmp4, %var_tmp5, !upper_data !2
  %mul_tmp6 = mul i64 %var_tmp3, %mul_tmp, !upper_data !3
  store i64 %mul_tmp6, i64* %d, !upper_data !3
  ret i64 0
}

!0 = !{!"1000"}
!1 = !{!"2000"}
!2 = !{!"4000000"}
!3 = !{!"8000000000"}
