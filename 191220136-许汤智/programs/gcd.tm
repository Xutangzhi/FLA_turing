;实现函数功能：找出两个数的最大公约数
;输入两个整数，我们用1的数量来表示输入的正整数，用0来分隔两个输入整数
;使用辗转相减法

#Q = {q0,copy,error,error1,error2,error3,error4,halt_error,beginindex,find,accept_erase,halt_accept,recover,erase1,erase2}
#S = {0,1}
#G = {0,1,_,e,r,o}
#q0 = q0
#B = _
#F = {halt_error,halt_accept}
#N = 2

;初始状态
q0 1_ 1_ ** copy
;若第一个读到0，说明没有第一个数，错误
q0 0_ __ r* error

;处理错误
error 1_ __ r* error
error 0_ __ r* error
error __ r_ l* error1
error1 __ o_ l* error2
error2 __ r_ l* error3
error3 __ r_ l* error4
error4 __ e_ ** halt_error

;将第二条带上复写第一条带
copy 1_ 11 rr copy
copy 0_ 00 rr copy
copy __ __ ll beginindex

;将第二条指针指到开头
beginindex 11 11 *l beginindex
beginindex 10 10 *l beginindex
beginindex 01 01 *l beginindex
beginindex 00 00 *l beginindex
beginindex 1_ 1_ *r find
beginindex 0_ 0_ *r find

;进行辗转相减
;指针一起移动直到一个到0
find 11 11 lr find
;b>a,然后进行删除
find 10 10 rl erase1
;a>b，然后进行删除
find 01 01 rl erase2
;a=b,进行接受前的处理
find 00 00 ** accept_erase

;b=b-a
erase1 11 _1 rl erase1
erase1 __ __ lr recover

;a=a-b
erase2 11 1_ rl erase2
erase2 __ __ lr recover

;将指针调整到原来位置
recover _1 _1 l* recover
recover 1_ 1_ *r recover
recover 11 11 ** find

;将tape1中其余元素清空
accept_erase 00 _0 l* accept_erase
accept_erase 10 _0 l* accept_erase
accept_erase _0 _0 ** halt_accept