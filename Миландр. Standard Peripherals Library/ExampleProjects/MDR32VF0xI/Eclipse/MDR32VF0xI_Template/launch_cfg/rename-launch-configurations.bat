@echo off
setlocal enabledelayedexpansion

set "CONTENT_PATTERN=MDR32VF0xI_Template"
set "NAME_PATTERN=Template"

echo Script replaces "Template" in .launch configuration names and replaces "MDR32VF0xI_Template" inside .launch configuration files with user-defined value.
echo NOTE: For safety you should backup old .launch files manually before processing.
echo.

:INPUT
set "REPLACE="
set /p "REPLACE=Enter new name (a-z, 0-9, -_, spaces allowed (leading/trailing spaces will be trimmed)): "
if not defined REPLACE goto INPUT

:: Trim leading/trailing spaces.
for /f "delims=" %%T in ('powershell -Command "'%REPLACE%'.Trim()"') do set "TRIMMED=%%T"
if "!TRIMMED!"=="" (
    echo Error: Name cannot be empty or contain only spaces
    goto INPUT
)
set "REPLACE=!TRIMMED!"

:: Validate.
echo !REPLACE!|findstr /r "^[a-zA-Z0-9_\- ][a-zA-Z0-9_\- ]*$" >nul
if %errorlevel% neq 0 (
    echo Invalid characters! Allowed: letters, numbers, hyphen, underscore, spaces
    goto INPUT
)

for /r %%F in (*.launch) do (
    echo Processing: %%~nxF
    set "file=%%~fF"
    
    :: 1. File content replace.
    powershell -Command "$filePath = '%%~fF'; $pattern = '%CONTENT_PATTERN%'; $newText = '%REPLACE%'; $content = Get-Content -LiteralPath $filePath -Raw; $content = $content -replace [regex]::Escape($pattern), $newText; Set-Content -LiteralPath $filePath -Value $content -NoNewline"
    
    :: 2. File rename.
    powershell -Command "$filePath = '%%~fF'; $oldName = [IO.Path]::GetFileName($filePath); $newName = $oldName -replace ('(?i)'+[regex]::Escape('%NAME_PATTERN%')), '!REPLACE!'; if (($newName -ne $oldName) -or ($newName -cne $oldName)) { $tempName = $oldName + '.tmp'; Rename-Item -LiteralPath $filePath -NewName $tempName -Force; Rename-Item -LiteralPath (Join-Path (Split-Path $filePath) $tempName) -NewName $newName -Force }"
)

echo Operation completed. Press any key...
pause