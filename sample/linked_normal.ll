; ModuleID = 'llvm-link'
source_filename = "llvm-link"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@.str = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.str.5 = private unnamed_addr constant [4 x i8] c"%ld\00", align 1

define i64 @main() {
entry:
  %a1 = alloca i64, !upper_data !2
  %a2 = alloca i64, !upper_data !2
  %a3 = alloca i64, !upper_data !2
  %a4 = alloca i64, !upper_data !2
  %a5 = alloca i64
  %a6 = alloca i64
  %a7 = alloca i64
  %a8 = alloca i64
  %a9 = alloca i64
  %a10 = alloca i64
  %a11 = alloca i64
  %a12 = alloca i64
  %a13 = alloca i64
  %a14 = alloca i64
  %a15 = alloca i64
  %a16 = alloca i64
  %a17 = alloca i64
  %a18 = alloca i64
  %a19 = alloca i64
  %a20 = alloca i64
  %call_tmp = call i64 @inputnum()
  store i64 %call_tmp, i64* %a1, !upper_data !2
  %call_tmp1 = call i64 @inputnum()
  store i64 %call_tmp1, i64* %a2, !upper_data !2
  %call_tmp2 = call i64 @inputnum()
  store i64 %call_tmp2, i64* %a3, !upper_data !2
  %call_tmp3 = call i64 @inputnum()
  store i64 %call_tmp3, i64* %a4, !upper_data !2
  %var_tmp = load i64, i64* %a4, !upper_data !2
  %var_tmp4 = load i64, i64* %a3, !upper_data !2
  %add_tmp = add i64 %var_tmp, %var_tmp4, !upper_data !3
  %var_tmp5 = load i64, i64* %a2, !upper_data !2
  %add_tmp6 = add i64 %add_tmp, %var_tmp5, !upper_data !4
  %var_tmp7 = load i64, i64* %a1, !upper_data !2
  %add_tmp8 = add i64 %add_tmp6, %var_tmp7, !upper_data !5
  store i64 %add_tmp8, i64* %a5, !upper_data !5
  %var_tmp9 = load i64, i64* %a5, !upper_data !5
  %var_tmp10 = load i64, i64* %a4, !upper_data !2
  %add_tmp11 = add i64 %var_tmp9, %var_tmp10, !upper_data !6
  %var_tmp12 = load i64, i64* %a3, !upper_data !2
  %add_tmp13 = add i64 %add_tmp11, %var_tmp12, !upper_data !7
  %var_tmp14 = load i64, i64* %a2, !upper_data !2
  %add_tmp15 = add i64 %add_tmp13, %var_tmp14, !upper_data !8
  %var_tmp16 = load i64, i64* %a1, !upper_data !2
  %add_tmp17 = add i64 %add_tmp15, %var_tmp16, !upper_data !9
  store i64 %add_tmp17, i64* %a6, !upper_data !9
  %var_tmp18 = load i64, i64* %a6, !upper_data !9
  %var_tmp19 = load i64, i64* %a5, !upper_data !5
  %add_tmp20 = add i64 %var_tmp18, %var_tmp19, !upper_data !10
  %var_tmp21 = load i64, i64* %a4, !upper_data !2
  %add_tmp22 = add i64 %add_tmp20, %var_tmp21, !upper_data !11
  %var_tmp23 = load i64, i64* %a3, !upper_data !2
  %add_tmp24 = add i64 %add_tmp22, %var_tmp23, !upper_data !12
  %var_tmp25 = load i64, i64* %a2, !upper_data !2
  %add_tmp26 = add i64 %add_tmp24, %var_tmp25, !upper_data !13
  store i64 %add_tmp26, i64* %a7, !upper_data !13
  %var_tmp27 = load i64, i64* %a7, !upper_data !13
  %var_tmp28 = load i64, i64* %a6, !upper_data !9
  %add_tmp29 = add i64 %var_tmp27, %var_tmp28, !upper_data !14
  %var_tmp30 = load i64, i64* %a5, !upper_data !5
  %add_tmp31 = add i64 %add_tmp29, %var_tmp30, !upper_data !15
  %var_tmp32 = load i64, i64* %a4, !upper_data !2
  %add_tmp33 = add i64 %add_tmp31, %var_tmp32, !upper_data !16
  %var_tmp34 = load i64, i64* %a3, !upper_data !2
  %add_tmp35 = add i64 %add_tmp33, %var_tmp34, !upper_data !17
  store i64 %add_tmp35, i64* %a8, !upper_data !17
  %var_tmp36 = load i64, i64* %a8, !upper_data !17
  %var_tmp37 = load i64, i64* %a7, !upper_data !13
  %add_tmp38 = add i64 %var_tmp36, %var_tmp37, !upper_data !18
  %var_tmp39 = load i64, i64* %a6, !upper_data !9
  %add_tmp40 = add i64 %add_tmp38, %var_tmp39, !upper_data !19
  %var_tmp41 = load i64, i64* %a5, !upper_data !5
  %add_tmp42 = add i64 %add_tmp40, %var_tmp41, !upper_data !20
  %var_tmp43 = load i64, i64* %a4, !upper_data !2
  %add_tmp44 = add i64 %add_tmp42, %var_tmp43, !upper_data !21
  store i64 %add_tmp44, i64* %a9, !upper_data !21
  %var_tmp45 = load i64, i64* %a9, !upper_data !21
  %var_tmp46 = load i64, i64* %a8, !upper_data !17
  %add_tmp47 = add i64 %var_tmp45, %var_tmp46, !upper_data !22
  %var_tmp48 = load i64, i64* %a7, !upper_data !13
  %add_tmp49 = add i64 %add_tmp47, %var_tmp48, !upper_data !23
  %var_tmp50 = load i64, i64* %a6, !upper_data !9
  %add_tmp51 = add i64 %add_tmp49, %var_tmp50, !upper_data !24
  %var_tmp52 = load i64, i64* %a5, !upper_data !5
  %add_tmp53 = add i64 %add_tmp51, %var_tmp52, !upper_data !25
  store i64 %add_tmp53, i64* %a10, !upper_data !25
  %var_tmp54 = load i64, i64* %a10, !upper_data !25
  %var_tmp55 = load i64, i64* %a9, !upper_data !21
  %add_tmp56 = add i64 %var_tmp54, %var_tmp55, !upper_data !26
  %var_tmp57 = load i64, i64* %a8, !upper_data !17
  %add_tmp58 = add i64 %add_tmp56, %var_tmp57, !upper_data !27
  %var_tmp59 = load i64, i64* %a7, !upper_data !13
  %add_tmp60 = add i64 %add_tmp58, %var_tmp59, !upper_data !28
  %var_tmp61 = load i64, i64* %a6, !upper_data !9
  %add_tmp62 = add i64 %add_tmp60, %var_tmp61, !upper_data !29
  store i64 %add_tmp62, i64* %a11, !upper_data !29
  %var_tmp63 = load i64, i64* %a11, !upper_data !29
  %var_tmp64 = load i64, i64* %a10, !upper_data !25
  %add_tmp65 = add i64 %var_tmp63, %var_tmp64, !upper_data !30
  %var_tmp66 = load i64, i64* %a9, !upper_data !21
  %add_tmp67 = add i64 %add_tmp65, %var_tmp66, !upper_data !31
  %var_tmp68 = load i64, i64* %a8, !upper_data !17
  %add_tmp69 = add i64 %add_tmp67, %var_tmp68, !upper_data !32
  %var_tmp70 = load i64, i64* %a7, !upper_data !13
  %add_tmp71 = add i64 %add_tmp69, %var_tmp70, !upper_data !33
  store i64 %add_tmp71, i64* %a12, !upper_data !33
  %var_tmp72 = load i64, i64* %a12, !upper_data !33
  %var_tmp73 = load i64, i64* %a11, !upper_data !29
  %add_tmp74 = add i64 %var_tmp72, %var_tmp73, !upper_data !34
  %var_tmp75 = load i64, i64* %a10, !upper_data !25
  %add_tmp76 = add i64 %add_tmp74, %var_tmp75, !upper_data !35
  %var_tmp77 = load i64, i64* %a9, !upper_data !21
  %add_tmp78 = add i64 %add_tmp76, %var_tmp77, !upper_data !36
  %var_tmp79 = load i64, i64* %a8, !upper_data !17
  %add_tmp80 = add i64 %add_tmp78, %var_tmp79, !upper_data !37
  store i64 %add_tmp80, i64* %a13, !upper_data !37
  %var_tmp81 = load i64, i64* %a13, !upper_data !37
  %var_tmp82 = load i64, i64* %a12, !upper_data !33
  %add_tmp83 = add i64 %var_tmp81, %var_tmp82, !upper_data !38
  %var_tmp84 = load i64, i64* %a11, !upper_data !29
  %add_tmp85 = add i64 %add_tmp83, %var_tmp84, !upper_data !39
  %var_tmp86 = load i64, i64* %a10, !upper_data !25
  %add_tmp87 = add i64 %add_tmp85, %var_tmp86, !upper_data !40
  %var_tmp88 = load i64, i64* %a9, !upper_data !21
  %add_tmp89 = add i64 %add_tmp87, %var_tmp88, !upper_data !41
  store i64 %add_tmp89, i64* %a14, !upper_data !41
  %var_tmp90 = load i64, i64* %a14, !upper_data !41
  %var_tmp91 = load i64, i64* %a13, !upper_data !37
  %add_tmp92 = add i64 %var_tmp90, %var_tmp91, !upper_data !42
  %var_tmp93 = load i64, i64* %a12, !upper_data !33
  %add_tmp94 = add i64 %add_tmp92, %var_tmp93, !upper_data !43
  %var_tmp95 = load i64, i64* %a11, !upper_data !29
  %add_tmp96 = add i64 %add_tmp94, %var_tmp95, !upper_data !44
  %var_tmp97 = load i64, i64* %a10, !upper_data !25
  %add_tmp98 = add i64 %add_tmp96, %var_tmp97, !upper_data !45
  store i64 %add_tmp98, i64* %a15, !upper_data !45
  %var_tmp99 = load i64, i64* %a15, !upper_data !45
  %var_tmp100 = load i64, i64* %a14, !upper_data !41
  %add_tmp101 = add i64 %var_tmp99, %var_tmp100, !upper_data !46
  %var_tmp102 = load i64, i64* %a13, !upper_data !37
  %add_tmp103 = add i64 %add_tmp101, %var_tmp102, !upper_data !47
  %var_tmp104 = load i64, i64* %a12, !upper_data !33
  %add_tmp105 = add i64 %add_tmp103, %var_tmp104, !upper_data !48
  %var_tmp106 = load i64, i64* %a11, !upper_data !29
  %add_tmp107 = add i64 %add_tmp105, %var_tmp106, !upper_data !49
  store i64 %add_tmp107, i64* %a16, !upper_data !49
  %var_tmp108 = load i64, i64* %a16, !upper_data !49
  %var_tmp109 = load i64, i64* %a15, !upper_data !45
  %add_tmp110 = add i64 %var_tmp108, %var_tmp109, !upper_data !50
  %var_tmp111 = load i64, i64* %a14, !upper_data !41
  %add_tmp112 = add i64 %add_tmp110, %var_tmp111, !upper_data !51
  %var_tmp113 = load i64, i64* %a13, !upper_data !37
  %add_tmp114 = add i64 %add_tmp112, %var_tmp113, !upper_data !52
  %var_tmp115 = load i64, i64* %a12, !upper_data !33
  %add_tmp116 = add i64 %add_tmp114, %var_tmp115, !upper_data !53
  store i64 %add_tmp116, i64* %a17, !upper_data !53
  %var_tmp117 = load i64, i64* %a17, !upper_data !53
  %var_tmp118 = load i64, i64* %a16, !upper_data !49
  %add_tmp119 = add i64 %var_tmp117, %var_tmp118, !upper_data !54
  %var_tmp120 = load i64, i64* %a15, !upper_data !45
  %add_tmp121 = add i64 %add_tmp119, %var_tmp120, !upper_data !55
  %var_tmp122 = load i64, i64* %a14, !upper_data !41
  %add_tmp123 = add i64 %add_tmp121, %var_tmp122, !upper_data !56
  %var_tmp124 = load i64, i64* %a13, !upper_data !37
  %add_tmp125 = add i64 %add_tmp123, %var_tmp124, !upper_data !57
  store i64 %add_tmp125, i64* %a18, !upper_data !57
  %var_tmp126 = load i64, i64* %a18, !upper_data !57
  %var_tmp127 = load i64, i64* %a17, !upper_data !53
  %add_tmp128 = add i64 %var_tmp126, %var_tmp127, !upper_data !58
  %var_tmp129 = load i64, i64* %a16, !upper_data !49
  %add_tmp130 = add i64 %add_tmp128, %var_tmp129, !upper_data !59
  %var_tmp131 = load i64, i64* %a15, !upper_data !45
  %add_tmp132 = add i64 %add_tmp130, %var_tmp131, !upper_data !60
  %var_tmp133 = load i64, i64* %a14, !upper_data !41
  %add_tmp134 = add i64 %add_tmp132, %var_tmp133, !upper_data !61
  store i64 %add_tmp134, i64* %a19, !upper_data !61
  %var_tmp135 = load i64, i64* %a19, !upper_data !61
  %var_tmp136 = load i64, i64* %a18, !upper_data !57
  %add_tmp137 = add i64 %var_tmp135, %var_tmp136, !upper_data !62
  %var_tmp138 = load i64, i64* %a17, !upper_data !53
  %add_tmp139 = add i64 %add_tmp137, %var_tmp138, !upper_data !63
  %var_tmp140 = load i64, i64* %a16, !upper_data !49
  %add_tmp141 = add i64 %add_tmp139, %var_tmp140, !upper_data !64
  %var_tmp142 = load i64, i64* %a15, !upper_data !45
  %add_tmp143 = add i64 %add_tmp141, %var_tmp142, !upper_data !65
  store i64 %add_tmp143, i64* %a20, !upper_data !65
  %var_tmp144 = load i64, i64* %a20, !upper_data !65
  %call_tmp145 = call i64 @printnum(i64 %var_tmp144)
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
  %4 = load i64, i64* %1, align 8, !tbaa !66
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
!2 = !{!"100"}
!3 = !{!"200"}
!4 = !{!"300"}
!5 = !{!"400"}
!6 = !{!"500"}
!7 = !{!"600"}
!8 = !{!"700"}
!9 = !{!"800"}
!10 = !{!"1200"}
!11 = !{!"1300"}
!12 = !{!"1400"}
!13 = !{!"1500"}
!14 = !{!"2300"}
!15 = !{!"2700"}
!16 = !{!"2800"}
!17 = !{!"2900"}
!18 = !{!"4400"}
!19 = !{!"5200"}
!20 = !{!"5600"}
!21 = !{!"5700"}
!22 = !{!"8600"}
!23 = !{!"10100"}
!24 = !{!"10900"}
!25 = !{!"11300"}
!26 = !{!"17000"}
!27 = !{!"19900"}
!28 = !{!"21400"}
!29 = !{!"22200"}
!30 = !{!"33500"}
!31 = !{!"39200"}
!32 = !{!"42100"}
!33 = !{!"43600"}
!34 = !{!"65800"}
!35 = !{!"77100"}
!36 = !{!"82800"}
!37 = !{!"85700"}
!38 = !{!"129300"}
!39 = !{!"151500"}
!40 = !{!"162800"}
!41 = !{!"168500"}
!42 = !{!"254200"}
!43 = !{!"297800"}
!44 = !{!"320000"}
!45 = !{!"331300"}
!46 = !{!"499800"}
!47 = !{!"585500"}
!48 = !{!"629100"}
!49 = !{!"651300"}
!50 = !{!"982600"}
!51 = !{!"1151100"}
!52 = !{!"1236800"}
!53 = !{!"1280400"}
!54 = !{!"1931700"}
!55 = !{!"2263000"}
!56 = !{!"2431500"}
!57 = !{!"2517200"}
!58 = !{!"3797600"}
!59 = !{!"4448900"}
!60 = !{!"4780200"}
!61 = !{!"4948700"}
!62 = !{!"7465900"}
!63 = !{!"8746300"}
!64 = !{!"9397600"}
!65 = !{!"9728900"}
!66 = !{!67, !67, i64 0}
!67 = !{!"long", !68, i64 0}
!68 = !{!"omnipotent char", !69, i64 0}
!69 = !{!"Simple C/C++ TBAA"}
