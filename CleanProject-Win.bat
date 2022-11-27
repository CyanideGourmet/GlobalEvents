@echo off
PowerShell -NoProfile -ExecutionPolicy Bypass -Command "& {Start-Process PowerShell -ArgumentList '-NoProfile -ExecutionPolicy Bypass -File ""CleanProject-Win.ps1""' -Verb RunAs}"

echo Cleaning Finished
pause