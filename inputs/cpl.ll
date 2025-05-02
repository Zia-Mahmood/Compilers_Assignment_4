; ModuleID = 'inputs/cpl_inputs/cpl.c'
source_filename = "inputs/cpl_inputs/cpl.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @test_add() #0 {
  %add = add i32 5, 3
  ret i32 %add
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @test_sub() #0 {
  %sub = sub i32 10, 4
  ret i32 %sub
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @test_mul() #0 {
  %mul = mul i32 6, 7
  ret i32 %mul
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @test_sdiv() #0 {
  %sdiv = sdiv i32 -10, 2
  ret i32 %sdiv
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @test_udiv() #0 {
  %udiv = udiv i32 10, 2
  ret i32 %udiv
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @test_srem() #0 {
  %srem = srem i32 10, 3
  ret i32 %srem
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @test_urem() #0 {
  %urem = urem i32 10, 3
  ret i32 %urem
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @test_shl() #0 {
  %shl = shl i32 1, 3
  ret i32 %shl
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @test_lshr() #0 {
  %lshr = lshr i32 8, 1
  ret i32 %lshr
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @test_ashr() #0 {
  %ashr = ashr i32 -8, 1
  ret i32 %ashr
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @test_and() #0 {
  %and = and i32 5, 3
  ret i32 %and
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @test_or() #0 {
  %or = or i32 5, 3
  ret i32 %or
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @test_xor() #0 {
  %xor = xor i32 5, 3
  ret i32 %xor
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @main() #0 {
  %1 = alloca i32, align 4
  store i32 0, ptr %1, align 4
  ret i32 0
}

attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.module.flags = !{!0, !1, !2, !3, !4}
!llvm.ident = !{!5}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{i32 7, !"frame-pointer", i32 2}
!5 = !{!"Ubuntu clang version 19.1.7 (++20250114103332+cd708029e0b2-1~exp1~20250114103446.78)"}
