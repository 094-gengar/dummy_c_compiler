; ModuleID = './sample/test.dc'
source_filename = "./sample/test.dc"

declare i64 @printnum(i64)

declare i64 @inputnum()

define i64 @main() {
entry:
  %a1 = alloca i64, !upper_data !0
  %a2 = alloca i64, !upper_data !0
  %a3 = alloca i64, !upper_data !0
  %a4 = alloca i64, !upper_data !0
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
  store i64 %call_tmp, i64* %a1, !upper_data !0
  %call_tmp1 = call i64 @inputnum()
  store i64 %call_tmp1, i64* %a2, !upper_data !0
  %call_tmp2 = call i64 @inputnum()
  store i64 %call_tmp2, i64* %a3, !upper_data !0
  %call_tmp3 = call i64 @inputnum()
  store i64 %call_tmp3, i64* %a4, !upper_data !0
  %var_tmp = load i64, i64* %a4, !upper_data !0
  %var_tmp4 = load i64, i64* %a3, !upper_data !0
  %add_tmp = add i64 %var_tmp, %var_tmp4, !upper_data !1
  %var_tmp5 = load i64, i64* %a2, !upper_data !0
  %add_tmp6 = add i64 %add_tmp, %var_tmp5, !upper_data !2
  %var_tmp7 = load i64, i64* %a1, !upper_data !0
  %add_tmp8 = add i64 %add_tmp6, %var_tmp7, !upper_data !3
  store i64 %add_tmp8, i64* %a5, !upper_data !3
  %var_tmp9 = load i64, i64* %a5, !upper_data !3
  %var_tmp10 = load i64, i64* %a4, !upper_data !0
  %add_tmp11 = add i64 %var_tmp9, %var_tmp10, !upper_data !4
  %var_tmp12 = load i64, i64* %a3, !upper_data !0
  %add_tmp13 = add i64 %add_tmp11, %var_tmp12, !upper_data !5
  %var_tmp14 = load i64, i64* %a2, !upper_data !0
  %add_tmp15 = add i64 %add_tmp13, %var_tmp14, !upper_data !6
  %var_tmp16 = load i64, i64* %a1, !upper_data !0
  %add_tmp17 = add i64 %add_tmp15, %var_tmp16, !upper_data !7
  store i64 %add_tmp17, i64* %a6, !upper_data !7
  %var_tmp18 = load i64, i64* %a6, !upper_data !7
  %var_tmp19 = load i64, i64* %a5, !upper_data !3
  %add_tmp20 = add i64 %var_tmp18, %var_tmp19, !upper_data !8
  %var_tmp21 = load i64, i64* %a4, !upper_data !0
  %add_tmp22 = add i64 %add_tmp20, %var_tmp21, !upper_data !9
  %var_tmp23 = load i64, i64* %a3, !upper_data !0
  %add_tmp24 = add i64 %add_tmp22, %var_tmp23, !upper_data !10
  %var_tmp25 = load i64, i64* %a2, !upper_data !0
  %add_tmp26 = add i64 %add_tmp24, %var_tmp25, !upper_data !11
  store i64 %add_tmp26, i64* %a7, !upper_data !11
  %var_tmp27 = load i64, i64* %a7, !upper_data !11
  %var_tmp28 = load i64, i64* %a6, !upper_data !7
  %add_tmp29 = add i64 %var_tmp27, %var_tmp28, !upper_data !12
  %var_tmp30 = load i64, i64* %a5, !upper_data !3
  %add_tmp31 = add i64 %add_tmp29, %var_tmp30, !upper_data !13
  %var_tmp32 = load i64, i64* %a4, !upper_data !0
  %add_tmp33 = add i64 %add_tmp31, %var_tmp32, !upper_data !14
  %var_tmp34 = load i64, i64* %a3, !upper_data !0
  %add_tmp35 = add i64 %add_tmp33, %var_tmp34, !upper_data !15
  store i64 %add_tmp35, i64* %a8, !upper_data !15
  %var_tmp36 = load i64, i64* %a8, !upper_data !15
  %var_tmp37 = load i64, i64* %a7, !upper_data !11
  %add_tmp38 = add i64 %var_tmp36, %var_tmp37, !upper_data !16
  %var_tmp39 = load i64, i64* %a6, !upper_data !7
  %add_tmp40 = add i64 %add_tmp38, %var_tmp39, !upper_data !17
  %var_tmp41 = load i64, i64* %a5, !upper_data !3
  %add_tmp42 = add i64 %add_tmp40, %var_tmp41, !upper_data !18
  %var_tmp43 = load i64, i64* %a4, !upper_data !0
  %add_tmp44 = add i64 %add_tmp42, %var_tmp43, !upper_data !19
  store i64 %add_tmp44, i64* %a9, !upper_data !19
  %var_tmp45 = load i64, i64* %a9, !upper_data !19
  %var_tmp46 = load i64, i64* %a8, !upper_data !15
  %add_tmp47 = add i64 %var_tmp45, %var_tmp46, !upper_data !20
  %var_tmp48 = load i64, i64* %a7, !upper_data !11
  %add_tmp49 = add i64 %add_tmp47, %var_tmp48, !upper_data !21
  %var_tmp50 = load i64, i64* %a6, !upper_data !7
  %add_tmp51 = add i64 %add_tmp49, %var_tmp50, !upper_data !22
  %var_tmp52 = load i64, i64* %a5, !upper_data !3
  %add_tmp53 = add i64 %add_tmp51, %var_tmp52, !upper_data !23
  store i64 %add_tmp53, i64* %a10, !upper_data !23
  %var_tmp54 = load i64, i64* %a10, !upper_data !23
  %var_tmp55 = load i64, i64* %a9, !upper_data !19
  %add_tmp56 = add i64 %var_tmp54, %var_tmp55, !upper_data !24
  %var_tmp57 = load i64, i64* %a8, !upper_data !15
  %add_tmp58 = add i64 %add_tmp56, %var_tmp57, !upper_data !25
  %var_tmp59 = load i64, i64* %a7, !upper_data !11
  %add_tmp60 = add i64 %add_tmp58, %var_tmp59, !upper_data !26
  %var_tmp61 = load i64, i64* %a6, !upper_data !7
  %add_tmp62 = add i64 %add_tmp60, %var_tmp61, !upper_data !27
  store i64 %add_tmp62, i64* %a11, !upper_data !27
  %var_tmp63 = load i64, i64* %a11, !upper_data !27
  %var_tmp64 = load i64, i64* %a10, !upper_data !23
  %add_tmp65 = add i64 %var_tmp63, %var_tmp64, !upper_data !28
  %var_tmp66 = load i64, i64* %a9, !upper_data !19
  %add_tmp67 = add i64 %add_tmp65, %var_tmp66, !upper_data !29
  %var_tmp68 = load i64, i64* %a8, !upper_data !15
  %add_tmp69 = add i64 %add_tmp67, %var_tmp68, !upper_data !30
  %var_tmp70 = load i64, i64* %a7, !upper_data !11
  %add_tmp71 = add i64 %add_tmp69, %var_tmp70, !upper_data !31
  store i64 %add_tmp71, i64* %a12, !upper_data !31
  %var_tmp72 = load i64, i64* %a12, !upper_data !31
  %var_tmp73 = load i64, i64* %a11, !upper_data !27
  %add_tmp74 = add i64 %var_tmp72, %var_tmp73, !upper_data !32
  %var_tmp75 = load i64, i64* %a10, !upper_data !23
  %add_tmp76 = add i64 %add_tmp74, %var_tmp75, !upper_data !33
  %var_tmp77 = load i64, i64* %a9, !upper_data !19
  %add_tmp78 = add i64 %add_tmp76, %var_tmp77, !upper_data !34
  %var_tmp79 = load i64, i64* %a8, !upper_data !15
  %add_tmp80 = add i64 %add_tmp78, %var_tmp79, !upper_data !35
  store i64 %add_tmp80, i64* %a13, !upper_data !35
  %var_tmp81 = load i64, i64* %a13, !upper_data !35
  %var_tmp82 = load i64, i64* %a12, !upper_data !31
  %add_tmp83 = add i64 %var_tmp81, %var_tmp82, !upper_data !36
  %var_tmp84 = load i64, i64* %a11, !upper_data !27
  %add_tmp85 = add i64 %add_tmp83, %var_tmp84, !upper_data !37
  %var_tmp86 = load i64, i64* %a10, !upper_data !23
  %add_tmp87 = add i64 %add_tmp85, %var_tmp86, !upper_data !38
  %var_tmp88 = load i64, i64* %a9, !upper_data !19
  %add_tmp89 = add i64 %add_tmp87, %var_tmp88, !upper_data !39
  store i64 %add_tmp89, i64* %a14, !upper_data !39
  %var_tmp90 = load i64, i64* %a14, !upper_data !39
  %var_tmp91 = load i64, i64* %a13, !upper_data !35
  %add_tmp92 = add i64 %var_tmp90, %var_tmp91, !upper_data !40
  %var_tmp93 = load i64, i64* %a12, !upper_data !31
  %add_tmp94 = add i64 %add_tmp92, %var_tmp93, !upper_data !41
  %var_tmp95 = load i64, i64* %a11, !upper_data !27
  %add_tmp96 = add i64 %add_tmp94, %var_tmp95, !upper_data !42
  %var_tmp97 = load i64, i64* %a10, !upper_data !23
  %add_tmp98 = add i64 %add_tmp96, %var_tmp97, !upper_data !43
  store i64 %add_tmp98, i64* %a15, !upper_data !43
  %var_tmp99 = load i64, i64* %a15, !upper_data !43
  %var_tmp100 = load i64, i64* %a14, !upper_data !39
  %add_tmp101 = add i64 %var_tmp99, %var_tmp100, !upper_data !44
  %var_tmp102 = load i64, i64* %a13, !upper_data !35
  %add_tmp103 = add i64 %add_tmp101, %var_tmp102, !upper_data !45
  %var_tmp104 = load i64, i64* %a12, !upper_data !31
  %add_tmp105 = add i64 %add_tmp103, %var_tmp104, !upper_data !46
  %var_tmp106 = load i64, i64* %a11, !upper_data !27
  %add_tmp107 = add i64 %add_tmp105, %var_tmp106, !upper_data !47
  store i64 %add_tmp107, i64* %a16, !upper_data !47
  %var_tmp108 = load i64, i64* %a16, !upper_data !47
  %var_tmp109 = load i64, i64* %a15, !upper_data !43
  %add_tmp110 = add i64 %var_tmp108, %var_tmp109, !upper_data !48
  %var_tmp111 = load i64, i64* %a14, !upper_data !39
  %add_tmp112 = add i64 %add_tmp110, %var_tmp111, !upper_data !49
  %var_tmp113 = load i64, i64* %a13, !upper_data !35
  %add_tmp114 = add i64 %add_tmp112, %var_tmp113, !upper_data !50
  %var_tmp115 = load i64, i64* %a12, !upper_data !31
  %add_tmp116 = add i64 %add_tmp114, %var_tmp115, !upper_data !51
  store i64 %add_tmp116, i64* %a17, !upper_data !51
  %var_tmp117 = load i64, i64* %a17, !upper_data !51
  %var_tmp118 = load i64, i64* %a16, !upper_data !47
  %add_tmp119 = add i64 %var_tmp117, %var_tmp118, !upper_data !52
  %var_tmp120 = load i64, i64* %a15, !upper_data !43
  %add_tmp121 = add i64 %add_tmp119, %var_tmp120, !upper_data !53
  %var_tmp122 = load i64, i64* %a14, !upper_data !39
  %add_tmp123 = add i64 %add_tmp121, %var_tmp122, !upper_data !54
  %var_tmp124 = load i64, i64* %a13, !upper_data !35
  %add_tmp125 = add i64 %add_tmp123, %var_tmp124, !upper_data !55
  store i64 %add_tmp125, i64* %a18, !upper_data !55
  %var_tmp126 = load i64, i64* %a18, !upper_data !55
  %var_tmp127 = load i64, i64* %a17, !upper_data !51
  %add_tmp128 = add i64 %var_tmp126, %var_tmp127, !upper_data !56
  %var_tmp129 = load i64, i64* %a16, !upper_data !47
  %add_tmp130 = add i64 %add_tmp128, %var_tmp129, !upper_data !57
  %var_tmp131 = load i64, i64* %a15, !upper_data !43
  %add_tmp132 = add i64 %add_tmp130, %var_tmp131, !upper_data !58
  %var_tmp133 = load i64, i64* %a14, !upper_data !39
  %add_tmp134 = add i64 %add_tmp132, %var_tmp133, !upper_data !59
  store i64 %add_tmp134, i64* %a19, !upper_data !59
  %var_tmp135 = load i64, i64* %a19, !upper_data !59
  %var_tmp136 = load i64, i64* %a18, !upper_data !55
  %add_tmp137 = add i64 %var_tmp135, %var_tmp136, !upper_data !60
  %var_tmp138 = load i64, i64* %a17, !upper_data !51
  %add_tmp139 = add i64 %add_tmp137, %var_tmp138, !upper_data !61
  %var_tmp140 = load i64, i64* %a16, !upper_data !47
  %add_tmp141 = add i64 %add_tmp139, %var_tmp140, !upper_data !62
  %var_tmp142 = load i64, i64* %a15, !upper_data !43
  %add_tmp143 = add i64 %add_tmp141, %var_tmp142, !upper_data !63
  store i64 %add_tmp143, i64* %a20, !upper_data !63
  %var_tmp144 = load i64, i64* %a20, !upper_data !63
  %call_tmp145 = call i64 @printnum(i64 %var_tmp144)
  ret i64 0
}

!0 = !{!"100"}
!1 = !{!"200"}
!2 = !{!"300"}
!3 = !{!"400"}
!4 = !{!"500"}
!5 = !{!"600"}
!6 = !{!"700"}
!7 = !{!"800"}
!8 = !{!"1200"}
!9 = !{!"1300"}
!10 = !{!"1400"}
!11 = !{!"1500"}
!12 = !{!"2300"}
!13 = !{!"2700"}
!14 = !{!"2800"}
!15 = !{!"2900"}
!16 = !{!"4400"}
!17 = !{!"5200"}
!18 = !{!"5600"}
!19 = !{!"5700"}
!20 = !{!"8600"}
!21 = !{!"10100"}
!22 = !{!"10900"}
!23 = !{!"11300"}
!24 = !{!"17000"}
!25 = !{!"19900"}
!26 = !{!"21400"}
!27 = !{!"22200"}
!28 = !{!"33500"}
!29 = !{!"39200"}
!30 = !{!"42100"}
!31 = !{!"43600"}
!32 = !{!"65800"}
!33 = !{!"77100"}
!34 = !{!"82800"}
!35 = !{!"85700"}
!36 = !{!"129300"}
!37 = !{!"151500"}
!38 = !{!"162800"}
!39 = !{!"168500"}
!40 = !{!"254200"}
!41 = !{!"297800"}
!42 = !{!"320000"}
!43 = !{!"331300"}
!44 = !{!"499800"}
!45 = !{!"585500"}
!46 = !{!"629100"}
!47 = !{!"651300"}
!48 = !{!"982600"}
!49 = !{!"1151100"}
!50 = !{!"1236800"}
!51 = !{!"1280400"}
!52 = !{!"1931700"}
!53 = !{!"2263000"}
!54 = !{!"2431500"}
!55 = !{!"2517200"}
!56 = !{!"3797600"}
!57 = !{!"4448900"}
!58 = !{!"4780200"}
!59 = !{!"4948700"}
!60 = !{!"7465900"}
!61 = !{!"8746300"}
!62 = !{!"9397600"}
!63 = !{!"9728900"}
