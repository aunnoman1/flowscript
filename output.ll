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
  %printfcall_pipe3 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 0)
  %startRange = alloca i32, align 4
  store i32 2, ptr %startRange, align 4
  %endRange = alloca i32, align 4
  store i32 5, ptr %endRange, align 4
  br label %loop_preheader4

loop_preheader4:                                  ; preds = %loop_exit
  %startRange9 = load i32, ptr %startRange, align 4
  %endRange10 = load i32, ptr %endRange, align 4
  %loop_var11 = alloca i32, align 4
  store i32 %startRange9, ptr %loop_var11, align 4
  br label %loop_cond_check5

loop_cond_check5:                                 ; preds = %loop_increment7, %loop_preheader4
  %current_loop_val12 = load i32, ptr %loop_var11, align 4
  %loop_cond13 = icmp slt i32 %current_loop_val12, %endRange10
  br i1 %loop_cond13, label %loop_body6, label %loop_exit8

loop_body6:                                       ; preds = %loop_cond_check5
  %loop_val_for_body14 = load i32, ptr %loop_var11, align 4
  %doubletmp_pipe15 = mul i32 %loop_val_for_body14, 2
  %printfcall_pipe16 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 %doubletmp_pipe15)
  br label %loop_increment7

loop_increment7:                                  ; preds = %loop_body6
  %val_before_inc17 = load i32, ptr %loop_var11, align 4
  %loop_var_inc18 = add i32 %val_before_inc17, 1
  store i32 %loop_var_inc18, ptr %loop_var11, align 4
  br label %loop_cond_check5

loop_exit8:                                       ; preds = %loop_cond_check5
  %printfcall_pipe19 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 0)
  br label %loop_preheader20

loop_preheader20:                                 ; preds = %loop_exit8
  %loop_var25 = alloca i32, align 4
  store i32 5, ptr %loop_var25, align 4
  br label %loop_cond_check21

loop_cond_check21:                                ; preds = %loop_increment23, %loop_preheader20
  %current_loop_val26 = load i32, ptr %loop_var25, align 4
  %loop_cond27 = icmp slt i32 %current_loop_val26, 5
  br i1 %loop_cond27, label %loop_body22, label %loop_exit24

loop_body22:                                      ; preds = %loop_cond_check21
  %loop_val_for_body28 = load i32, ptr %loop_var25, align 4
  %printfcall_pipe29 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 999)
  br label %loop_increment23

loop_increment23:                                 ; preds = %loop_body22
  %val_before_inc30 = load i32, ptr %loop_var25, align 4
  %loop_var_inc31 = add i32 %val_before_inc30, 1
  store i32 %loop_var_inc31, ptr %loop_var25, align 4
  br label %loop_cond_check21

loop_exit24:                                      ; preds = %loop_cond_check21
  %printfcall_pipe32 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 0)
  br label %loop_preheader33

loop_preheader33:                                 ; preds = %loop_exit24
  %startRange38 = load i32, ptr %startRange, align 4
  %endRange39 = load i32, ptr %endRange, align 4
  %loop_var40 = alloca i32, align 4
  store i32 %startRange38, ptr %loop_var40, align 4
  br label %loop_cond_check34

loop_cond_check34:                                ; preds = %loop_increment36, %loop_preheader33
  %current_loop_val41 = load i32, ptr %loop_var40, align 4
  %loop_cond42 = icmp slt i32 %current_loop_val41, %endRange39
  br i1 %loop_cond42, label %loop_body35, label %loop_exit37

loop_body35:                                      ; preds = %loop_cond_check34
  %loop_val_for_body43 = load i32, ptr %loop_var40, align 4
  %addtmp_pipe_arg = add i32 %loop_val_for_body43, 10
  %printfcall_pipe44 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 %addtmp_pipe_arg)
  br label %loop_increment36

loop_increment36:                                 ; preds = %loop_body35
  %val_before_inc45 = load i32, ptr %loop_var40, align 4
  %loop_var_inc46 = add i32 %val_before_inc45, 1
  store i32 %loop_var_inc46, ptr %loop_var40, align 4
  br label %loop_cond_check34

loop_exit37:                                      ; preds = %loop_cond_check34
  %myVar47 = load i32, ptr %myVar, align 4
  %pipeif_cond = icmp sgt i32 %myVar47, 5
  br i1 %pipeif_cond, label %then, label %else

then:                                             ; preds = %loop_exit37
  %printfcall_pipe48 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 1)
  br label %ifcont

else:                                             ; preds = %loop_exit37
  %printfcall_pipe49 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 0)
  br label %ifcont

ifcont:                                           ; preds = %else, %then
  br i1 false, label %then50, label %else51

then50:                                           ; preds = %ifcont
  %printfcall_pipe53 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 100)
  br label %ifcont52

else51:                                           ; preds = %ifcont
  %printfcall_pipe54 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 200)
  br label %ifcont52

ifcont52:                                         ; preds = %else51, %then50
  %printfcall_pipe55 = call i32 (ptr, ...) @printf(ptr @.fmt_int_global, i32 5)
  ret i32 0
}
