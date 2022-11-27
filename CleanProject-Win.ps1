.{
    gci -Directory | where { $_.Name -in ('Binaries', 'Intermediate', 'Saved', 'DerivedDataCache', 'Script') }
    gci 'Plugins/' -Depth 1 -Directory | where FullName -notlike '*\Plugins\Developer\*' | where {$_.Name -in ('Binaries', 'Intermediate') }
} | Remove-Item -Force -Recurse