; ModuleID = 'flowscript_module'
source_filename = "flowscript_module"

@.fmt_int_global = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

declare i32 @printf(ptr, ...)

define i32 @main() {
entry:
  %myVar = alloca i32, align 4
  store i32 10, ptr %myVar, align 4
  %printfcall_pipe = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 10)
  %printfcall_pipe1 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 13)
  br label %loop_preheader

loop_preheader:                                   ; preds = %entry
  %loop_var = alloca i32, align 4
  store i32 1, ptr %loop_var, align 4
  br label %loop_cond_check

loop_cond_check:                                  ; preds = %loop_increment, %loop_preheader
  %current_loop_val = load i32, ptr %loop_var, align 4
  %loop_cond = icmp slt i32 %current_loop_val, 3
  br i1 %loop_cond, label %loop_body, label %loop_exit

loop_body:                                        ; preds = %loop_cond_check
  %loop_val_for_body = load i32, ptr %loop_var, align 4
  %doubletmp_pipe = mul i32 %loop_val_for_body, 2
  %printfcall_pipe2 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 %doubletmp_pipe)
  br label %loop_increment

loop_increment:                                   ; preds = %loop_body
  %val_before_inc = load i32, ptr %loop_var, align 4
  %loop_var_inc = add i32 %val_before_inc, 1
  store i32 %loop_var_inc, ptr %loop_var, align 4
  br label %loop_cond_check

loop_exit:                                        ; preds = %loop_cond_check
  %myVar3 = load i32, ptr %myVar, align 4
  %gttmp = icmp sgt i32 %myVar3, 5
  br i1 %gttmp, label %then, label %else

then:                                             ; preds = %loop_exit
  %printfcall_explicit = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 1)
  br label %ifcont

else:                                             ; preds = %loop_exit
  %printfcall_explicit4 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 0)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  br i1 false, label %then5, label %else6

then5:                                            ; preds = %ifcont
  %printfcall_explicit8 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 100)
  br label %ifcont7

else6:                                            ; preds = %ifcont
  %printfcall_explicit9 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 200)
  br label %ifcont7

ifcont7:                                          ; preds = %else6, %then5
  %printfcall_pipe10 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 5)
  ret i32 0
}
