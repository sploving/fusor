; ModuleID = 'main.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@main.a = private unnamed_addr constant [10 x i32] [i32 3, i32 4, i32 5, i32 6, i32 7, i32 1, i32 2, i32 8, i32 9, i32 0], align 16
@main.b = private unnamed_addr constant [10 x i32] [i32 9, i32 5, i32 6, i32 0, i32 1, i32 2, i32 3, i32 4, i32 8, i32 7], align 16
@main.c = private unnamed_addr constant [10 x i32] [i32 1, i32 2, i32 3, i32 4, i32 5, i32 6, i32 8, i32 9, i32 6, i32 0], align 16
@main.d = private unnamed_addr constant [10 x i32] [i32 1, i32 2, i32 3, i32 4, i32 5, i32 6, i32 7, i32 8, i32 9, i32 0], align 16
@.str = private unnamed_addr constant [51 x i8] c"Type I opaque predicate should not be satisfiable\0A\00", align 1
@.str.1 = private unnamed_addr constant [48 x i8] c"Type II opaque predicate should be satisfiable\0A\00", align 1

; Function Attrs: nounwind uwtable
define i32 @main(i32 %argc, i8** %argv) #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i8**, align 8
  %i = alloca i32, align 4
  %a = alloca [10 x i32], align 16
  %b = alloca [10 x i32], align 16
  %c = alloca [10 x i32], align 16
  %d = alloca [10 x i32], align 16
  %j = alloca i32, align 4
  store i32 0, i32* %1, align 4
  store i32 %argc, i32* %2, align 4
  store i8** %argv, i8*** %3, align 8
  %4 = load i8**, i8*** %3, align 8
  %5 = getelementptr inbounds i8*, i8** %4, i64 1
  %6 = load i8*, i8** %5, align 8
  %7 = call i32 (i8*, ...) bitcast (i32 (...)* @atoi to i32 (i8*, ...)*)(i8* %6)
  %8 = srem i32 %7, 10
  %9 = add nsw i32 %8, 10
  %10 = srem i32 %9, 10
  store i32 %10, i32* %i, align 4
  %11 = bitcast [10 x i32]* %a to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %11, i8* bitcast ([10 x i32]* @main.a to i8*), i64 40, i32 16, i1 false)
  %12 = bitcast [10 x i32]* %b to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %12, i8* bitcast ([10 x i32]* @main.b to i8*), i64 40, i32 16, i1 false)
  %13 = bitcast [10 x i32]* %c to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %13, i8* bitcast ([10 x i32]* @main.c to i8*), i64 40, i32 16, i1 false)
  %14 = bitcast [10 x i32]* %d to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* %14, i8* bitcast ([10 x i32]* @main.d to i8*), i64 40, i32 16, i1 false)
  %15 = load i32, i32* %i, align 4
  %16 = sext i32 %15 to i64
  %17 = getelementptr inbounds [10 x i32], [10 x i32]* %a, i64 0, i64 %16
  %18 = load i32, i32* %17, align 4
  %19 = sext i32 %18 to i64
  %20 = getelementptr inbounds [10 x i32], [10 x i32]* %b, i64 0, i64 %19
  %21 = load i32, i32* %20, align 4
  %22 = sext i32 %21 to i64
  %23 = getelementptr inbounds [10 x i32], [10 x i32]* %c, i64 0, i64 %22
  %24 = load i32, i32* %23, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds [10 x i32], [10 x i32]* %d, i64 0, i64 %25
  %27 = load i32, i32* %26, align 4
  store i32 %27, i32* %j, align 4
  %28 = load i32, i32* %i, align 4
  %29 = load i32, i32* %j, align 4
  %30 = icmp ne i32 %28, %29
  br i1 %30, label %31, label %33

; <label>:31                                      ; preds = %0
  %32 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str, i32 0, i32 0))
  br label %33

; <label>:33                                      ; preds = %31, %0
  %34 = load i32, i32* %j, align 4
  %35 = icmp eq i32 %34, 7
  br i1 %35, label %36, label %41

; <label>:36                                      ; preds = %33
  %37 = load i32, i32* %i, align 4
  %38 = icmp eq i32 %37, 7
  br i1 %38, label %39, label %41

; <label>:39                                      ; preds = %36
  %40 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([48 x i8], [48 x i8]* @.str.1, i32 0, i32 0))
  br label %41

; <label>:41                                      ; preds = %39, %36, %33
  %42 = load i32, i32* %1, align 4
  ret i32 %42
}

declare i32 @atoi(...) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture, i8* nocapture readonly, i64, i32, i1) #2

declare i32 @printf(i8*, ...) #1

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { argmemonly nounwind }

!llvm.ident = !{!0}

!0 = !{!"clang version 3.8.1-24 (tags/RELEASE_381/final)"}
