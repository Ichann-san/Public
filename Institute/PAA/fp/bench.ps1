$inputs = @('21','A','1','F','0','ABCDEF1234','123456789ABCDEF','FF','100','DEADBEEF')
foreach($i in $inputs) {
    $sw = [System.Diagnostics.Stopwatch]::StartNew()
    echo $i | & '.\try22.exe' | Out-Null
    $sw.Stop()
    $t1 = $sw.Elapsed.TotalMilliseconds

    $sw = [System.Diagnostics.Stopwatch]::StartNew()
    echo $i | & '.\try23.exe' | Out-Null
    $sw.Stop()
    $t2 = $sw.Elapsed.TotalMilliseconds

    Write-Host ('{0,-20} old={1,8:F2}ms  new={2,8:F2}ms  speedup={3:F2}x' -f $i,$t1,$t2,($t1/$t2))
}
