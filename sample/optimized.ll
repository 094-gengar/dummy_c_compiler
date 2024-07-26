; ModuleID = './sample/optimized.bc'
source_filename = "./sample/test.dc"

declare i64 @printnum(i64)

declare i64 @inputnum()

define i64 @main() {
entry:
  %a1 = alloca i32
  %a2 = alloca i32
  %a3 = alloca i32
  %a4 = alloca i32
  %a5 = alloca i32
  %a6 = alloca i32
  %a7 = alloca i32
  %a8 = alloca i32
  %a9 = alloca i32
  %a10 = alloca i32
  %a11 = alloca i32
  %a12 = alloca i32
  %a13 = alloca i32
  %a14 = alloca i32
  %a15 = alloca i32
  %a16 = alloca i32
  %a17 = alloca i32
  %a18 = alloca i32
  %a19 = alloca i32
  %a20 = alloca i32
  %call_tmp = call i64 @inputnum()
  %0 = trunc i64 %call_tmp to i32
  store i32 %0, i32* %a1
  %call_tmp1 = call i64 @inputnum()
  %1 = trunc i64 %call_tmp1 to i32
  store i32 %1, i32* %a2
  %call_tmp2 = call i64 @inputnum()
  %2 = trunc i64 %call_tmp2 to i32
  store i32 %2, i32* %a3
  %call_tmp3 = call i64 @inputnum()
  %3 = trunc i64 %call_tmp3 to i32
  store i32 %3, i32* %a4
  %var_tmp = load i32, i32* %a4
  %var_tmp4 = load i32, i32* %a3
  %add_tmp = add i32 %var_tmp, %var_tmp4
  %var_tmp5 = load i32, i32* %a2
  %add_tmp6 = add i32 %add_tmp, %var_tmp5
  %var_tmp7 = load i32, i32* %a1
  %add_tmp8 = add i32 %add_tmp6, %var_tmp7
  store i32 %add_tmp8, i32* %a5
  %var_tmp9 = load i32, i32* %a5
  %var_tmp10 = load i32, i32* %a4
  %add_tmp11 = add i32 %var_tmp9, %var_tmp10
  %var_tmp12 = load i32, i32* %a3
  %add_tmp13 = add i32 %add_tmp11, %var_tmp12
  %var_tmp14 = load i32, i32* %a2
  %add_tmp15 = add i32 %add_tmp13, %var_tmp14
  %var_tmp16 = load i32, i32* %a1
  %add_tmp17 = add i32 %add_tmp15, %var_tmp16
  store i32 %add_tmp17, i32* %a6
  %var_tmp18 = load i32, i32* %a6
  %var_tmp19 = load i32, i32* %a5
  %add_tmp20 = add i32 %var_tmp18, %var_tmp19
  %var_tmp21 = load i32, i32* %a4
  %add_tmp22 = add i32 %add_tmp20, %var_tmp21
  %var_tmp23 = load i32, i32* %a3
  %add_tmp24 = add i32 %add_tmp22, %var_tmp23
  %var_tmp25 = load i32, i32* %a2
  %add_tmp26 = add i32 %add_tmp24, %var_tmp25
  store i32 %add_tmp26, i32* %a7
  %var_tmp27 = load i32, i32* %a7
  %var_tmp28 = load i32, i32* %a6
  %add_tmp29 = add i32 %var_tmp27, %var_tmp28
  %var_tmp30 = load i32, i32* %a5
  %add_tmp31 = add i32 %add_tmp29, %var_tmp30
  %var_tmp32 = load i32, i32* %a4
  %add_tmp33 = add i32 %add_tmp31, %var_tmp32
  %var_tmp34 = load i32, i32* %a3
  %add_tmp35 = add i32 %add_tmp33, %var_tmp34
  store i32 %add_tmp35, i32* %a8
  %var_tmp36 = load i32, i32* %a8
  %var_tmp37 = load i32, i32* %a7
  %add_tmp38 = add i32 %var_tmp36, %var_tmp37
  %var_tmp39 = load i32, i32* %a6
  %add_tmp40 = add i32 %add_tmp38, %var_tmp39
  %var_tmp41 = load i32, i32* %a5
  %add_tmp42 = add i32 %add_tmp40, %var_tmp41
  %var_tmp43 = load i32, i32* %a4
  %add_tmp44 = add i32 %add_tmp42, %var_tmp43
  store i32 %add_tmp44, i32* %a9
  %var_tmp45 = load i32, i32* %a9
  %var_tmp46 = load i32, i32* %a8
  %add_tmp47 = add i32 %var_tmp45, %var_tmp46
  %var_tmp48 = load i32, i32* %a7
  %add_tmp49 = add i32 %add_tmp47, %var_tmp48
  %var_tmp50 = load i32, i32* %a6
  %add_tmp51 = add i32 %add_tmp49, %var_tmp50
  %var_tmp52 = load i32, i32* %a5
  %add_tmp53 = add i32 %add_tmp51, %var_tmp52
  store i32 %add_tmp53, i32* %a10
  %var_tmp54 = load i32, i32* %a10
  %var_tmp55 = load i32, i32* %a9
  %add_tmp56 = add i32 %var_tmp54, %var_tmp55
  %var_tmp57 = load i32, i32* %a8
  %add_tmp58 = add i32 %add_tmp56, %var_tmp57
  %var_tmp59 = load i32, i32* %a7
  %add_tmp60 = add i32 %add_tmp58, %var_tmp59
  %var_tmp61 = load i32, i32* %a6
  %add_tmp62 = add i32 %add_tmp60, %var_tmp61
  store i32 %add_tmp62, i32* %a11
  %var_tmp63 = load i32, i32* %a11
  %var_tmp64 = load i32, i32* %a10
  %add_tmp65 = add i32 %var_tmp63, %var_tmp64
  %var_tmp66 = load i32, i32* %a9
  %add_tmp67 = add i32 %add_tmp65, %var_tmp66
  %var_tmp68 = load i32, i32* %a8
  %add_tmp69 = add i32 %add_tmp67, %var_tmp68
  %var_tmp70 = load i32, i32* %a7
  %add_tmp71 = add i32 %add_tmp69, %var_tmp70
  store i32 %add_tmp71, i32* %a12
  %var_tmp72 = load i32, i32* %a12
  %var_tmp73 = load i32, i32* %a11
  %add_tmp74 = add i32 %var_tmp72, %var_tmp73
  %var_tmp75 = load i32, i32* %a10
  %add_tmp76 = add i32 %add_tmp74, %var_tmp75
  %var_tmp77 = load i32, i32* %a9
  %add_tmp78 = add i32 %add_tmp76, %var_tmp77
  %var_tmp79 = load i32, i32* %a8
  %add_tmp80 = add i32 %add_tmp78, %var_tmp79
  store i32 %add_tmp80, i32* %a13
  %var_tmp81 = load i32, i32* %a13
  %var_tmp82 = load i32, i32* %a12
  %add_tmp83 = add i32 %var_tmp81, %var_tmp82
  %var_tmp84 = load i32, i32* %a11
  %add_tmp85 = add i32 %add_tmp83, %var_tmp84
  %var_tmp86 = load i32, i32* %a10
  %add_tmp87 = add i32 %add_tmp85, %var_tmp86
  %var_tmp88 = load i32, i32* %a9
  %add_tmp89 = add i32 %add_tmp87, %var_tmp88
  store i32 %add_tmp89, i32* %a14
  %var_tmp90 = load i32, i32* %a14
  %var_tmp91 = load i32, i32* %a13
  %add_tmp92 = add i32 %var_tmp90, %var_tmp91
  %var_tmp93 = load i32, i32* %a12
  %add_tmp94 = add i32 %add_tmp92, %var_tmp93
  %var_tmp95 = load i32, i32* %a11
  %add_tmp96 = add i32 %add_tmp94, %var_tmp95
  %var_tmp97 = load i32, i32* %a10
  %add_tmp98 = add i32 %add_tmp96, %var_tmp97
  store i32 %add_tmp98, i32* %a15
  %var_tmp99 = load i32, i32* %a15
  %var_tmp100 = load i32, i32* %a14
  %add_tmp101 = add i32 %var_tmp99, %var_tmp100
  %var_tmp102 = load i32, i32* %a13
  %add_tmp103 = add i32 %add_tmp101, %var_tmp102
  %var_tmp104 = load i32, i32* %a12
  %add_tmp105 = add i32 %add_tmp103, %var_tmp104
  %var_tmp106 = load i32, i32* %a11
  %add_tmp107 = add i32 %add_tmp105, %var_tmp106
  store i32 %add_tmp107, i32* %a16
  %var_tmp108 = load i32, i32* %a16
  %var_tmp109 = load i32, i32* %a15
  %add_tmp110 = add i32 %var_tmp108, %var_tmp109
  %var_tmp111 = load i32, i32* %a14
  %add_tmp112 = add i32 %add_tmp110, %var_tmp111
  %var_tmp113 = load i32, i32* %a13
  %add_tmp114 = add i32 %add_tmp112, %var_tmp113
  %var_tmp115 = load i32, i32* %a12
  %add_tmp116 = add i32 %add_tmp114, %var_tmp115
  store i32 %add_tmp116, i32* %a17
  %var_tmp117 = load i32, i32* %a17
  %var_tmp118 = load i32, i32* %a16
  %add_tmp119 = add i32 %var_tmp117, %var_tmp118
  %var_tmp120 = load i32, i32* %a15
  %add_tmp121 = add i32 %add_tmp119, %var_tmp120
  %var_tmp122 = load i32, i32* %a14
  %add_tmp123 = add i32 %add_tmp121, %var_tmp122
  %var_tmp124 = load i32, i32* %a13
  %add_tmp125 = add i32 %add_tmp123, %var_tmp124
  store i32 %add_tmp125, i32* %a18
  %var_tmp126 = load i32, i32* %a18
  %var_tmp127 = load i32, i32* %a17
  %add_tmp128 = add i32 %var_tmp126, %var_tmp127
  %var_tmp129 = load i32, i32* %a16
  %add_tmp130 = add i32 %add_tmp128, %var_tmp129
  %var_tmp131 = load i32, i32* %a15
  %add_tmp132 = add i32 %add_tmp130, %var_tmp131
  %var_tmp133 = load i32, i32* %a14
  %add_tmp134 = add i32 %add_tmp132, %var_tmp133
  store i32 %add_tmp134, i32* %a19
  %var_tmp135 = load i32, i32* %a19
  %var_tmp136 = load i32, i32* %a18
  %add_tmp137 = add i32 %var_tmp135, %var_tmp136
  %var_tmp138 = load i32, i32* %a17
  %add_tmp139 = add i32 %add_tmp137, %var_tmp138
  %var_tmp140 = load i32, i32* %a16
  %add_tmp141 = add i32 %add_tmp139, %var_tmp140
  %var_tmp142 = load i32, i32* %a15
  %add_tmp143 = add i32 %add_tmp141, %var_tmp142
  store i32 %add_tmp143, i32* %a20
  %var_tmp144 = load i32, i32* %a20
  %4 = sext i32 %var_tmp144 to i64
  %call_tmp145 = call i64 @printnum(i64 %4)
  ret i64 0
}
