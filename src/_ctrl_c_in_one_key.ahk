#NoEnv  ; Recommended for performance and compatibility with future AutoHotkey releases.
; #Warn  ; Enable warnings to assist with detecting common errors.
SendMode Input  ; Recommended for new scripts due to its superior speed and reliability.
SetWorkingDir %A_ScriptDir%  ; Ensures a consistent starting directory.


copy_now := 0

f1::
Copy_now := !Copy_now
If (Copy_now)
    Send ^c
Else
    Send ^v
Return


::mail::yzhongyuanfff@gmail.com

::wi::what is 
::hc::how can we 
::wk::what kind of 
::ef::explain the following

::qcpt::what is? how is used? the idea? adv. and disadv.? 
::tcalcu::write formulas and calculate this example! 
::tall::imp. and paper and further reading!  
::qalgo::pseudo code? proof? complexity? adv. disadv.? imp. &t 
::qpf::proof this!


