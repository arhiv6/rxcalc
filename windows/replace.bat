
:: use: replace.bat input_file.txt old_text new_text > output_file.txt

@echo off
setlocal
if "%CMDEXTVERSION%"=="" (
    cmd /e:on /v:on /c %0 %1 %2 %3
    goto :end
)
set vartest=vartest
if not !vartest!==%vartest% (
    cmd /e:on /v:on /c %0 %1 %2 %3
    goto :end
)
for /f "delims=" %%i in (%1) do (
    set in=%%i
    echo !in:%2=%3!
)
:end
endlocal