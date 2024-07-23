; ModuleID = 'llvm-link'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"%ld\00", align 1

define i64 @main() {
entry:
  %a = alloca i64, !upper_data !2
  %b = alloca i64, !upper_data !2
  %c = alloca i64
  %d = alloca i64
  %call_tmp = call i64 @inputnum()
  store i64 %call_tmp, i64* %a, !upper_data !2
  %call_tmp1 = call i64 @inputnum()
  store i64 %call_tmp1, i64* %b, !upper_data !2
  %var_tmp = load i64, i64* %a, !upper_data !2
  %call_tmp2 = call i64 @printnum(i64 %var_tmp)
  %var_tmp3 = load i64, i64* %a, !upper_data !2
  %var_tmp4 = load i64, i64* %b, !upper_data !2
  %add_tmp = add i64 %var_tmp3, %var_tmp4, !upper_data !3
  store i64 %add_tmp, i64* %c, !upper_data !3
  %var_tmp5 = load i64, i64* %c, !upper_data !3
  %var_tmp6 = load i64, i64* %c, !upper_data !3
  %mul_tmp = mul i64 %var_tmp5, %var_tmp6, !upper_data !4
  %var_tmp7 = load i64, i64* %c, !upper_data !3
  %mul_tmp8 = mul i64 %mul_tmp, %var_tmp7, !upper_data !5
  store i64 %mul_tmp8, i64* %d, !upper_data !5
  %var_tmp9 = load i64, i64* %d, !upper_data !5
  %call_tmp10 = call i64 @printnum(i64 %var_tmp9)
  ret i64 0
}

; Function Attrs: nofree nounwind uwtable
define dso_local i64 @printnum(i64 %0) #0 {
  %2 = tail call i32 (i8*, ...) @printf(i8* nonnull dereferenceable(1) getelementptr inbounds ([5 x i8], [5 x i8]* @.str, i64 0, i64 0), i64 %0)
  %3 = sext i32 %2 to i64
  ret i64 %3
}

; Function Attrs: nofree nounwind
declare dso_local i32 @printf(i8* nocapture readonly, ...) local_unnamed_addr #1

; Function Attrs: nounwind uwtable
define dso_local i64 @inputnum() #2 {
  %1 = alloca i64, align 8
  %2 = bitcast i64* %1 to i8*
  call void @llvm.lifetime.start.p0i8(i64 8, i8* nonnull %2) #4
  %3 = call i32 (i8*, ...) @__isoc99_scanf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.5, i64 0, i64 0), i64* nonnull %1)
  %4 = load i64, i64* %1, align 8, !tbaa !6
  call void @llvm.lifetime.end.p0i8(i64 8, i8* nonnull %2) #4
  ret i64 %4
}

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.lifetime.start.p0i8(i64 immarg, i8* nocapture) #3

; Function Attrs: nofree nounwind
declare dso_local i32 @__isoc99_scanf(i8* nocapture readonly, ...) local_unnamed_addr #1

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.lifetime.end.p0i8(i64 immarg, i8* nocapture) #3

attributes #0 = { nofree nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nofree nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="none" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { argmemonly nounwind willreturn }
attributes #4 = { nounwind }

!llvm.ident = !{!0, !0}
!llvm.module.flags = !{!1}

!0 = !{!"clang version 10.0.0-4ubuntu1 "}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{!"1000"}
!3 = !{!"2000"}
!4 = !{!"4000000"}
!5 = !{!"8000000000"}
!6 = !{!7, !7, i64 0}
!7 = !{!"long", !8, i64 0}
!8 = !{!"omnipotent char", !9, i64 0}
!9 = !{!"Simple C/C++ TBAA"}
