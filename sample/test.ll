; ModuleID = './sample/test.dc'
source_filename = "./sample/test.dc"

declare i64 @printnum(i64)

declare i64 @inputnum()

define i64 @main() {
entry:
  %a = alloca [1000000 x i64], !upper_data !0
  %gep = getelementptr [1000000 x i64], [1000000 x i64]* %a, i32 0, i32 0, !upper_data !0
  %t0 = load i64, i64* %gep, !upper_data !0
  %inc_add_tmp = add i64 %t0, 1, !upper_data !1
  store volatile i64 %inc_add_tmp, i64* %gep, !upper_data !1
  ret i64 0
}

!0 = !{!"10"}
!1 = !{!"11"}
